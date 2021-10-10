// Copyright Danny Kay 2021

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterRogueLiteTarget : TargetRules
{
	public ShooterRogueLiteTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShooterRogueLite" } );
	}
}
