// (c) 2017 Damian Nowakowski

using System;
using System.IO;
using UnrealBuildTool;

public class CrashDump : ModuleRules
{
	public CrashDump(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {"CrashDump/Public"});
		PrivateIncludePaths.AddRange(new string[] {"CrashDump/Private"});		
		PublicDependencyModuleNames.AddRange(new string[]{"Core", "CoreUObject","Engine"});

        if (Target.Platform == UnrealTargetPlatform.Android && 
            Target.Configuration != UnrealTargetConfiguration.Shipping &&
            Target.Configuration != UnrealTargetConfiguration.Test)
        {
            Definitions.Add("WITH_CRASH_DUMP=1");
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "CrashDump_UPL_Android.xml")));

            string ThirdPartyPath = Path.Combine(ModuleDirectory, "..", "ThirdParty");
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "GoogleBreakpad", "include"));
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "GoogleBreakpad", "libbreakpad_client.a"));
        }
        else
        {
            Definitions.Add("WITH_CRASH_DUMP=0");
        }

    }
}
