// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InvasionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INVASIONCORE_API AInvasionPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
