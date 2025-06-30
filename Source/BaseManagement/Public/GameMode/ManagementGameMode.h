// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ManagementGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BASEMANAGEMENT_API AManagementGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AManagementGameMode();

private:
	TObjectPtr<class AInvasionPlayerState> PlayerState;
};
