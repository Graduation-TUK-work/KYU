#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

// 팀 구분을 위한 열거형(Enum)
UENUM(BlueprintType)
enum class ETeamType : uint8
{
    Survivor UMETA(DisplayName = "Survivor"),
    Killer   UMETA(DisplayName = "Killer")
};

UCLASS()
class MYPROJECT_START_API ASpawnPoint : public AActor
{
    GENERATED_BODY()

public:
    // 생성자
    ASpawnPoint();

    // 에디터에서 팀을 선택할 수 있게 노출
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    ETeamType SpawnTeam;

    // 캐릭터가 스폰될 방향을 보여줄 화살표
    UPROPERTY(VisibleAnywhere)
    class UArrowComponent* ArrowComponent;
};