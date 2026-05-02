#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpawnPoint.h" // 우리가 만든 스폰 포인트 헤더 필수
#include "MySpawnHelper.generated.h"

UCLASS()
class MYPROJECT_START_API UMySpawnHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** 팀 타입에 맞는 스폰 포인트의 Transform을 반환하는 정적 함수 */
	UFUNCTION(BlueprintCallable, Category = "SpawnSystem", meta = (WorldContext = "WorldContextObject"))
	static FTransform GetTeamedSpawnTransform(const UObject* WorldContextObject, ETeamType Team);
};