// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class C_ToVReDefense : ModuleRules
{
	public C_ToVReDefense(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils" });

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
			DynamicallyLoadedModuleNames.Add("IOSAdvertising");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
			DynamicallyLoadedModuleNames.Add("AndroidAdvertising");
			// Add UPL to add configrules.txt to our APK
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(PluginPath, "AddAndroidExportedToSplash_UPL.xml"));
		}
	}
}