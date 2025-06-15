// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GridSystemSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class INVASION_API UGridSystemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
};
