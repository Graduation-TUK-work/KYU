#pragma once
#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Shared.h" // 아까 만든 헤더 포함

class FNetworkWorker : public FRunnable
{
public:
    FNetworkWorker(FString IP, int32 Port);
    virtual ~FNetworkWorker();

    // FRunnable 인터페이스 구현
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    FSocket* GetSocket() { return Socket; }
    void SetOwnerCharacter(class ATutorialCharacter* InCharacter) { OwnerCharacter = InCharacter; }

private:
    FSocket* Socket;
    FString ServerIP;
    int32 ServerPort;
    bool bRunning;
    class ATutorialCharacter* OwnerCharacter;
    int32 CachedMyPlayerId = -1;

    // 수신한 데이터를 안전하게 보관할 큐 (메인 스레드에서 꺼내갈 용도)
    // 실제로는 TQueue 등을 사용하지만, 일단 동작 확인을 위해 간단히 구성합니다.
};