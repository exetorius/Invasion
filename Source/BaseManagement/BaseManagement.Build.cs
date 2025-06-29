// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BaseManagement : ModuleRules
{
	public BaseManagement(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

	}
}
