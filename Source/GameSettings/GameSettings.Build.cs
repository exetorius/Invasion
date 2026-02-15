using UnrealBuildTool;

public class GameSettings : ModuleRules
{
    public GameSettings(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core"  });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "UMG" });
        
    }
}