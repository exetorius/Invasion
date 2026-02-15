// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InvasionCore : ModuleRules
{
	public InvasionCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"AdvancedSessions"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
