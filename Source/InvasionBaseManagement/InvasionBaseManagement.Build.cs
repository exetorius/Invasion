// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InvasionBaseManagement : ModuleRules
{
	public InvasionBaseManagement(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core"  });

		PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "UMG", "SlateCore" });

	}
}
