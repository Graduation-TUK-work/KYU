#include "MyGameModeBase.h"
#include "Generator.h"
#include "EscapeDoor.h"
#include "Kismet/GameplayStatics.h"

AMyGameModeBase::AMyGameModeBase()
{
    // 기본값 초기화
    TotalGenerators = 0;
    RepairedGenerators = 0;
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // 맵의 모든 발전기 찾기
    TArray<AActor*> FoundGenerators;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenerator::StaticClass(), FoundGenerators);

    TotalGenerators = FoundGenerators.Num();
    RepairedGenerators = 0;

    UE_LOG(LogTemp, Warning, TEXT("Map Loaded. Total Generators: %d"), TotalGenerators);
}

void AMyGameModeBase::OnGeneratorRepaired()
{
    RepairedGenerators++;
    UE_LOG(LogTemp, Warning, TEXT("Generator Repaired! Progress: %d / %d"), RepairedGenerators, TotalGenerators);

    // [수정] 정확히 개수가 일치할 때 '딱 한 번'만 문을 열도록 합니다.
    if (RepairedGenerators == TotalGenerators)
    {
        OpenEscapeDoor();
    }
}

void AMyGameModeBase::OpenEscapeDoor_Implementation()
{
    TArray<AActor*> FoundDoors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEscapeDoor::StaticClass(), FoundDoors);

    // 로그 1: 맵에서 문을 몇 개나 찾았는지 확인
    UE_LOG(LogTemp, Warning, TEXT("GameMode: Found %d Escape Doors in map."), FoundDoors.Num());

    for (AActor* DoorActor : FoundDoors)
    {
        AEscapeDoor* Door = Cast<AEscapeDoor>(DoorActor);
        if (Door)
        {
            // 로그 2: 문을 찾았고 함수를 실행시키기 직전
            UE_LOG(LogTemp, Warning, TEXT("GameMode: Calling OpenDoor on %s"), *Door->GetName());
            Door->OpenDoor();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("GameMode: Found actor but failed to cast to AEscapeDoor!"));
        }
    }
}