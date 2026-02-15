using UnrealBuildTool;

public class InvasionGameSettings : ModuleRules
{
    public InvasionGameSettings(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core"  });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "UMG" });

    }
}
