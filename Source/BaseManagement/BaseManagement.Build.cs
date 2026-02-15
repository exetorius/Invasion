// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BaseManagement : ModuleRules
{
	public BaseManagement(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core"  });

		PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "UMG" });

	}
}
