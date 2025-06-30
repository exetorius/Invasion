// CopyrightNotice


#include "GameMode/ManagementGameMode.h"

#include "Controller/ManagementPlayerController.h"

AManagementGameMode::AManagementGameMode()
{
	bUseSeamlessTravel = true;
	PlayerControllerClass = AManagementPlayerController::StaticClass(); // Can be overriden in the BP if required
}
