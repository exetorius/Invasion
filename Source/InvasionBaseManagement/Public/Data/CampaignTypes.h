#pragma once

#include "CoreMinimal.h"
#include "CampaignTypes.generated.h"

UENUM(BlueprintType)
enum class ENation : uint8
{
	EN_None			UMETA(DisplayName = "Not Selected"),
	EN_UK			UMETA(DisplayName = "United Kingdom"),
	EN_US			UMETA(DisplayName = "United States"),
	EN_AUS			UMETA(DisplayName = "Australia"),
	EN_CHN			UMETA(DisplayName = "China"),
	EN_FRA			UMETA(DisplayName = "France"),
	
	EN_MAX			UMETA(Hidden)
};

// Helper function
INVASIONBASEMANAGEMENT_API FName GetRegionNameFromNation(ENation Nation);
INVASIONBASEMANAGEMENT_API TArray<FName> GetAllUniqueRegions();
