#pragma once

#include "ManagementUITypes.generated.h"

UENUM(BlueprintType)
enum class EManagementView : uint8
{
	EMV_World			UMETA(DisplayName = "World"),
	EMV_BaseOverview	UMETA(DisplayName = "Base Overview"),
	EMV_Roster			UMETA(DisplayName = "Roster"),
	EMV_Hiring			UMETA(DisplayName = "Hiring"),
	EMV_Character		UMETA(DisplayName = "Character"),
	EMV_Warehouse		UMETA(DisplayName = "Warehouse"),
	EMV_Research		UMETA(DisplayName = "Research"),
	EMV_Engineering		UMETA(DisplayName = "Engineering"),
	
	EMV_MAX				UMETA(DisplayName = "MAX")
};