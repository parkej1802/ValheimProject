// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Valheim : ModuleRules
{
	public Valheim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
