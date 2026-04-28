#include "Generator.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject_Start/MyGameModeBase.h"

AGenerator::AGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
    bIsRepaired = false;
    bIsBeingRepaired = false;
    RepairProgress = 0.0f;
    RepairDuration = 5.0f;
    CurrentInteractor = nullptr; // 초기화
}

void AGenerator::BeginPlay()
{
    Super::BeginPlay();

    // 초기화 확인용 로그 (선택 사항)
    UE_LOG(LogTemp, Warning, TEXT("Generator Spawned and Ready."));
}

void AGenerator::StartInteract_Implementation(ACharacter* Interactor)
{
    if (bIsRepaired) return;

    bIsBeingRepaired = true;
    CurrentInteractor = Interactor; // 누가 수리 시작했는지 기억
}

void AGenerator::UpdateInteract_Implementation(float DeltaTime)
{
    // 이미 완료되었거나 수리 중이 아니면 실행 안 함
    if (!bIsBeingRepaired || bIsRepaired) return;

    RepairProgress += DeltaTime / RepairDuration;
    RepairProgress = FMath::Clamp(RepairProgress, 0.f, 1.f);

    if (RepairProgress >= 1.f)
    {
        CompleteInteract_Implementation();
        return;
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, DeltaTime, FColor::Cyan,
            FString::Printf(TEXT("Repair Progress: %.2f %%"), RepairProgress * 100.f));
    }
}

void AGenerator::CompleteInteract_Implementation()
{
    if (bIsRepaired) return;

    bIsBeingRepaired = false;
    bIsRepaired = true;

    UE_LOG(LogTemp, Warning, TEXT("Generator repaired!"));

    // [핵심 추가] 수리하던 캐릭터가 있다면 강제로 상호작용 중단시키기
    if (CurrentInteractor)
    {
        // 캐릭터가 상호작용 인터페이스를 가지고 있다면 상호작용 종료 함수 호출
        // 보통 캐릭터의 상호작용 상태를 Reset 해주는 로직이 필요합니다.
        // 회원님의 캐릭터 클래스에 상호작용 중단 함수가 있다면 여기서 호출하세요.
        // 예: Cast<ITutorialInterface>(CurrentInteractor)->StopInteraction();

        CurrentInteractor = nullptr;
    }

    // 게임 모드 보고
    AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->OnGeneratorRepaired();
    }
}

void AGenerator::CancelInteract_Implementation()
{
    if (bIsRepaired) return;

    bIsBeingRepaired = false;
    CurrentInteractor = nullptr; // 손 뗌
    UE_LOG(LogTemp, Warning, TEXT("Generator repair cancelled. Progress: %.2f"), RepairProgress);
}

float AGenerator::GetInteractDuration_Implementation() const
{
    return RepairDuration;
}