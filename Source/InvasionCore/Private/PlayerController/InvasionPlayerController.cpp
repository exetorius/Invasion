// CopyrightNotice


#include "PlayerController/InvasionPlayerController.h"

void AInvasionPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	const FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	SetShowMouseCursor(true);
}
