using UnrealBuildTool;
using System.Collections.Generic;

public class U2_DigilioTarget : TargetRules
{
    public U2_DigilioTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.Add("U2_Digilio");
    }
}