// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGridCharacter.generated.h"

UCLASS()
class INVASION_API ABaseGridCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseGridCharacter();
	void MoveToGridCell(FIntPoint TargetCell) const;
	void StartTurn();


};
