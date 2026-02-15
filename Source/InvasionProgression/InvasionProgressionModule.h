#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FInvasionProgressionModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
