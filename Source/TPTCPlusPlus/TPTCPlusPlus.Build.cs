// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPTCPlusPlus : ModuleRules
{
	public TPTCPlusPlus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
