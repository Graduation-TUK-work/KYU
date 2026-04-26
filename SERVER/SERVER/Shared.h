#pragma once

#pragma pack(push, 1)

// ÇÃ·§Æûº° Å¸ÀÔ Ã³¸®
#ifdef _WIN32
#include <cstdint>
typedef uint8_t uint8;
typedef int32_t int32;
#else
#include "CoreMinimal.h"
#endif



enum EPacketType : uint8 {
    PKT_JOIN = 1,
    PKT_MOVE = 2,
};

enum ECharacterType : uint8 {
    CHARACTER_SURVIVOR = 1,
    CHARACTER_KILLER = 2,
};

enum EPlayerRole : uint8 {
    ROLE_NONE = 0,
    ROLE_KILLER = 1,
    ROLE_SURVIVOR = 2
};



struct FPlayerData {
    int32 PlayerId;
    uint8 CharacterType;
    float X, Y, Z;
    float RotationYaw;
    float ForwardValue;
    float RightValue;
    bool bIsSprinting;
};

struct FPacketJoin {
    uint8 Type;
    int32 MyId;
};

struct FPacketMove {
    uint8 Type;
    FPlayerData Data;
};

#pragma pack(pop)