#include "SpawnPoint.h"
#include "Components/ArrowComponent.h"

ASpawnPoint::ASpawnPoint()
{
    // 매 프레임 틱을 돌 필요가 없으므로 false로 꺼둠 (최적화)
    PrimaryActorTick.bCanEverTick = false;

    // 화살표 컴포넌트 생성 및 루트로 설정
    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    RootComponent = ArrowComponent;
}