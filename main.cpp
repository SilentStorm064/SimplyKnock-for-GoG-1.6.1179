#include "skse64/PluginAPI.h"		// super
#include "skse64_common/skse_version.h"	// What version of SKSE is running?
#include <shlobj.h>				// CSIDL_MYCODUMENTS

#include "SimplyKnock.h"

static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface         * g_papyrus = NULL;

extern "C"	{

	__declspec(dllexport) SKSEPluginVersionData SKSEPlugin_Version =
	{

		SKSEPluginVersionData::kVersion,

		2,
		"SimplyKnock",

		"Chesko, anonymousthing, SilentStorm064",
		"",

		0,
		SKSEPluginVersionData::kVersionIndependent_StructsPost629,
		{ RUNTIME_VERSION_1_6_1179_GOG, 0 },

		0,	// works with any version of the script extender. you probably do not need to put anything here
	};

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)	{	// Called by SKSE to learn about this plugin and check that it's safe to load it
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition GOG\\SKSE\\SimplyKnock.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("SimplyKnockSKSE");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		"SimplyKnock";
		info->version =		1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = skse->GetPluginHandle();

		if(skse->isEditor)
		{
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}

		// ### do not do anything else in this callback
		// ### only fill out PluginInfo and return true/false

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)	{	// Called by SKSE to load this plugin
		_MESSAGE("SimplyKnock loaded");

		g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(SimplyKnockNamespace::RegisterFuncs);

		if (btest) {
			_MESSAGE("Register Succeeded");
		}

		return true;
	}

};
