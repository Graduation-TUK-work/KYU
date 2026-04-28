#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
// 파일 이름이 MyGameModeBase.h 이므로 반드시 아래와 같이 적어야 합니다.
#include "MyGameModeBase.generated.h"

UCLASS()
class MYPROJECT_START_API AMyGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    // 생성자에서 기본값 세팅 (선택 사항)
    AMyGameModeBase();

    virtual void BeginPlay() override;

    // 발전기가 호출할 함수
    void OnGeneratorRepaired();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameLogic")
    int32 TotalGenerators = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameLogic")
    int32 RepairedGenerators = 0;

    // 문이 열리는 이벤트
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameLogic")
    void OpenEscapeDoor();
};