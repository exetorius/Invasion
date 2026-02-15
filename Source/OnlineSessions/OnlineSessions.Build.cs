using UnrealBuildTool;

public class OnlineSessions : ModuleRules
{
    public OnlineSessions(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "AdvancedSessions" });
    }
}