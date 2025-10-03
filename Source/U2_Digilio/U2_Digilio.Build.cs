// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U2_Digilio : ModuleRules
{
	public U2_Digilio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"U2_Digilio",
			"U2_Digilio/Variant_Platforming",
			"U2_Digilio/Variant_Platforming/Animation",
			"U2_Digilio/Variant_Combat",
			"U2_Digilio/Variant_Combat/AI",
			"U2_Digilio/Variant_Combat/Animation",
			"U2_Digilio/Variant_Combat/Gameplay",
			"U2_Digilio/Variant_Combat/Interfaces",
			"U2_Digilio/Variant_Combat/UI",
			"U2_Digilio/Variant_SideScrolling",
			"U2_Digilio/Variant_SideScrolling/AI",
			"U2_Digilio/Variant_SideScrolling/Gameplay",
			"U2_Digilio/Variant_SideScrolling/Interfaces",
			"U2_Digilio/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
