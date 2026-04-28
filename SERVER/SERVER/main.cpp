#include <winsock2.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <mutex>
#include "Shared.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

// 전역 카운터 및 데이터베이스
int g_idCounter = 0;
mutex g_idLock;

enum class IO_TYPE { READ, WRITE };

struct Session {
    SOCKET socket;
};

struct OverlappedContext {
    WSAOVERLAPPED overlapped;
    WSABUF wsaBuf;
    char buffer[1024];
    IO_TYPE ioType;
};

struct PlayerInfo {
    int32 PlayerId;
    float X, Y, Z;
    float RotationYaw;
    uint8 CharacterType; // 1: 생존자, 2: 살인마

    // --- 추가된 부분 ---
    float ForwardValue;
    float RightValue;
    bool bIsSprinting;
};

map<int32, PlayerInfo> g_playerDataMap;
mutex g_dataLock;

list<Session*> g_sessions;
mutex g_sessionLock;

// 브로드캐스트: 모든 클라이언트에게 패킷 전송
void Broadcast(char* buf, int len, Session* exceptSession = nullptr) {
    lock_guard<mutex> lock(g_sessionLock);
    for (Session* s : g_sessions) {
        if (s == exceptSession) continue;
        send(s->socket, buf, len, 0);
    }
}

// 워커 스레드: 패킷 수신 및 처리
DWORD WINAPI WorkerThread(LPVOID lpParam) {
    HANDLE hIOCP = (HANDLE)lpParam;
    DWORD bytesTransferred = 0;
    Session* pSession = nullptr;
    OverlappedContext* pContext = nullptr;

    while (true) {
        BOOL result = GetQueuedCompletionStatus(
            hIOCP, &bytesTransferred, (PULONG_PTR)&pSession, (LPOVERLAPPED*)&pContext, INFINITE
        );

        if (result == FALSE || bytesTransferred == 0) {
            cout << "[알림] 클라이언트 접속 종료" << endl;
            lock_guard<mutex> lock(g_sessionLock);
            g_sessions.remove(pSession);
            closesocket(pSession->socket);

            // 데이터베이스에서도 제거 (필요 시)
            // { lock_guard<mutex> lock(g_dataLock); g_playerDataMap.erase(pSessionID); }

            delete pSession;
            delete pContext;
            continue;
        }

        if (pContext->ioType == IO_TYPE::READ) {
            unsigned char packetType = (unsigned char)pContext->buffer[0];

            switch (packetType) {
            case PKT_MOVE: {
                FPacketMove* movePkt = (FPacketMove*)pContext->buffer;
                {
                    lock_guard<mutex> lock(g_dataLock);
                    int id = movePkt->Data.PlayerId;

                    // 최신 데이터 업데이트
                    g_playerDataMap[id].X = movePkt->Data.X;
                    g_playerDataMap[id].Y = movePkt->Data.Y;
                    g_playerDataMap[id].Z = movePkt->Data.Z;
                    g_playerDataMap[id].RotationYaw = movePkt->Data.RotationYaw;
                    g_playerDataMap[id].CharacterType = movePkt->Data.CharacterType;

                    // --- 추가된 부분 ---
                    g_playerDataMap[id].ForwardValue = movePkt->Data.ForwardValue;
                    g_playerDataMap[id].RightValue = movePkt->Data.RightValue;
                    g_playerDataMap[id].bIsSprinting = movePkt->Data.bIsSprinting;
                }
                // 다른 모든 클라이언트에게 위치 전송 (이건 원래 잘 작동하고 있었습니다)
                Broadcast(pContext->buffer, sizeof(FPacketMove), pSession);
            }
                         break;
            break;
            case PKT_ACTION:
            {
                // 2. 액션 패킷으로 캐스팅
                FPacketAction* actionPkt = (FPacketAction*)pContext->buffer;

                // 서버 콘솔에 로그 출력 (확인용)
                cout << "[Action] ID " << actionPkt->InstigatorId
                    << " performed Action: " << (int)actionPkt->ActionType << endl;

                // 3. 모든 클라이언트에게 액션 중계 (Broadcast)
                Broadcast((char*)actionPkt, sizeof(FPacketAction), pSession);
            }
            break;
            }

            // 재수신 예약
            DWORD flags = 0;
            DWORD recvBytes = 0;
            memset(&pContext->overlapped, 0, sizeof(OVERLAPPED));
            WSARecv(pSession->socket, &pContext->wsaBuf, 1, &recvBytes, &flags, &pContext->overlapped, NULL);
        }
    }
    return 0;
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    HANDLE hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors * 2;
    for (int i = 0; i < threadCount; ++i) {
        CreateThread(NULL, 0, WorkerThread, hIOCP, 0, NULL);
    }

    SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    SOCKADDR_IN serverAddr = { 0 };
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(7777);

    bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(listenSocket, SOMAXCONN);

    cout << "======= Unreal IOCP Server Running (Port 7777) =======" << endl;

    while (true) {
        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr,  &addrLen);

        if (clientSocket != INVALID_SOCKET) {
            cout << "[접속] 새로운 언리얼 클라이언트 연결!" << endl;

            Session* newSession = new Session{ clientSocket };
            {
                lock_guard<mutex> lock(g_sessionLock);
                g_sessions.push_back(newSession);
            }

            // 1. ID 할당 및 역할 결정
            FPacketJoin joinPkt;
            joinPkt.Type = PKT_JOIN;
            {
                lock_guard<mutex> lock(g_idLock);
                joinPkt.MyId = g_idCounter++;
            }

            // 0번은 살인마(2), 나머지는 생존자(1)
            uint8 assignedType = (joinPkt.MyId == 0) ? 2 : 1;

            // 2. [수정사항] 데이터베이스에 즉시 등록
            {
                lock_guard<mutex> lock(g_dataLock);
                PlayerInfo info;
                info.PlayerId = joinPkt.MyId;
                info.CharacterType = assignedType;
                info.X = 0.0f;
                info.Y = 0.0f;
                info.Z = 100.0f; // 스폰 시 바닥에 묻히지 않게 살짝 띄움
                info.RotationYaw = 0.0f;
                g_playerDataMap[joinPkt.MyId] = info;
            }

            CreateIoCompletionPort((HANDLE)clientSocket, hIOCP, (ULONG_PTR)newSession, 0);

            // 3. 본인에게 ID 부여 패킷 전송
            send(clientSocket, (char*)&joinPkt, sizeof(joinPkt), 0);

            // 4. [수정사항] 기존 플레이어 정보 전송 (본인 제외)
            {
                lock_guard<mutex> lock(g_dataLock);
                for (auto it = g_playerDataMap.begin(); it != g_playerDataMap.end(); ++it)
                {
                    if (it->first == joinPkt.MyId) continue;

                    FPacketMove oldPlayerPkt;
                    memset(&oldPlayerPkt, 0, sizeof(oldPlayerPkt));
                    oldPlayerPkt.Type = PKT_MOVE;
                    oldPlayerPkt.Data.PlayerId = it->second.PlayerId;
                    oldPlayerPkt.Data.CharacterType = it->second.CharacterType;
                    oldPlayerPkt.Data.X = it->second.X;
                    oldPlayerPkt.Data.Y = it->second.Y;
                    oldPlayerPkt.Data.Z = it->second.Z;
                    oldPlayerPkt.Data.RotationYaw = it->second.RotationYaw;

                    // --- 추가된 부분 ---
                    oldPlayerPkt.Data.ForwardValue = it->second.ForwardValue;
                    oldPlayerPkt.Data.RightValue = it->second.RightValue;
                    oldPlayerPkt.Data.bIsSprinting = it->second.bIsSprinting;

                    send(clientSocket, (char*)&oldPlayerPkt, sizeof(oldPlayerPkt), 0);
                }
            }

            cout << "[할당] ID " << joinPkt.MyId << " (Type: " << (int)assignedType << ") 부여 완료!" << endl;

            // 5. 최초 수신 예약
            OverlappedContext* recvContext = new OverlappedContext();
            memset(recvContext, 0, sizeof(OverlappedContext));
            recvContext->ioType = IO_TYPE::READ;
            recvContext->wsaBuf.buf = recvContext->buffer;
            recvContext->wsaBuf.len = sizeof(recvContext->buffer);

            DWORD flags = 0;
            DWORD recvBytes = 0;
            WSARecv(clientSocket, &recvContext->wsaBuf, 1, &recvBytes, &flags, &recvContext->overlapped, NULL);
        }
    }

    WSACleanup();
    return 0;
}