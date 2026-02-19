#pragma once

#include "ManagementUITypes.generated.h"

UENUM(BlueprintType)
enum class EManagementView : uint8
{
	EMV_World		UMETA(DisplayName = "World"),
	EMV_Base		UMETA(DisplayName = "Base"),
	EMV_Roster		UMETA(DisplayName = "Roster"),
	EMV_Hiring		UMETA(DisplayName = "Hiring"),
	EMV_Character	UMETA(DisplayName = "Character"),
	EMV_Warehouse	UMETA(DisplayName = "Warehouse"),
	EMV_Research	UMETA(DisplayName = "Research"),
	EMV_Engineering UMETA(DisplayName = "Engineering"),
	EMV_ButtonBar	UMETA(DisplayName = "Button Bar"), // TODO: Remove this - its not a screen, currently using to bind the navigation event 
	
	EMV_MAX UMETA(DisplayName = "MAX")
};