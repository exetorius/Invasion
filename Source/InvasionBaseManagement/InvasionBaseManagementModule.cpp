// Copyright Epic Games, Inc. All Rights Reserved.

#include "InvasionBaseManagementModule.h"
#include "Modules/ModuleManager.h"


void FInvasionBaseManagementModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FInvasionBaseManagementModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

IMPLEMENT_GAME_MODULE(FInvasionBaseManagementModule, InvasionBaseManagement);
