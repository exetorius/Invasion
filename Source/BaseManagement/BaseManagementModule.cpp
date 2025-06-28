// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseManagementModule.h"
#include "Modules/ModuleManager.h"


void FBaseManagementModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FBaseManagementModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

IMPLEMENT_GAME_MODULE(FBaseManagementModule, BaseManagement);