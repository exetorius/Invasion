// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Invasion : ModuleRules
{
	public Invasion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
	}
}
