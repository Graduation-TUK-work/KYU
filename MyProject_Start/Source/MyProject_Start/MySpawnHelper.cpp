#include "MySpawnHelper.h"
#include "Kismet/GameplayStatics.h"

FTransform UMySpawnHelper::GetTeamedSpawnTransform(const UObject* WorldContextObject, ETeamType Team)
{
	if (!WorldContextObject) return FTransform::Identity;

	TArray<AActor*> FoundPoints;
	// 맵에 배치된 모든 ASpawnPoint 액터를 찾습니다.
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ASpawnPoint::StaticClass(), FoundPoints);

	for (AActor* Point : FoundPoints)
	{
		ASpawnPoint* SP = Cast<ASpawnPoint>(Point);
		// 우리가 찾는 팀과 일치하는 스폰 포인트를 발견하면 즉시 그 위치(Transform)를 반환합니다.
		if (SP && SP->SpawnTeam == Team)
		{
			return SP->GetActorTransform();
		}
	}

	// 찾지 못했을 경우 기본 위치를 반환합니다.
	return FTransform::Identity;
}