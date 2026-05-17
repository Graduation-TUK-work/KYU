#pragma once

#pragma pack(push, 1)

// 플랫폼별 타입 처리
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
    PKT_ACTION = 3,
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

enum EActionType : uint8 {
    ACTION_KILLER_ATTACK = 1,
    ACTION_SURVIVOR_HIT = 2,
    ACTION_SURVIVOR_PICKUP = 3,
    ACTION_GENERATOR_START = 4,
    ACTION_GENERATOR_CANCEL = 5,
    ACTION_GENERATOR_COMPLETE = 6,
    ACTION_SURVIVOR_REVIVE_START = 7,
    ACTION_SURVIVOR_REVIVE_CANCEL = 8,
    ACTION_SURVIVOR_REVIVE_COMPLETE = 9,
    ACTION_BANDAGE_PICKUP = 10,
    ACTION_SELF_REVIVE_START = 11,
    ACTION_SELF_REVIVE_CANCEL = 12,
    ACTION_SELF_REVIVE_COMPLETE = 13,
};

struct FPacketAction {
    uint8 Type;
    uint8 ActionType;
    int32 InstigatorId;
    int32 TargetId;
    float X, Y, Z;
    float RotationYaw;
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
