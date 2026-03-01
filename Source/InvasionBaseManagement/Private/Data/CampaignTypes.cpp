#include "Data/CampaignTypes.h"

FName GetRegionNameFromNation(ENation Nation)
{
	switch (Nation)
	{
		case ENation::EN_UK:	return FName("Europe");
		case ENation::EN_FRA:	return FName("Europe");
		case ENation::EN_US:	return FName("North America");
		case ENation::EN_AUS:	return FName("Oceania");
		case ENation::EN_CHN:	return FName("Asia");
		default:				return FName("None");
	}
}

TArray<FName> GetAllUniqueRegions()
{
	TArray<FName> UniqueRegions;
	for (uint8 i = static_cast<uint8>(ENation::EN_UK); i < static_cast<uint8>(ENation::EN_MAX); i++)
	{
		UniqueRegions.AddUnique(GetRegionNameFromNation(static_cast<ENation>(i)));
	}
	return UniqueRegions;
}
