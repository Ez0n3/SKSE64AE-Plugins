// User Defines
#include "config.h"
// SKSE64AE
#include "skse64/GameAPI.h"
#include "skse64/PluginAPI.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64_common/SafeWrite.h"
// Windows
#include <shlobj.h>	// CSIDL_MYCODUMENTS

// ================================
// Handles
// ================================

// Handle for the plugin
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

// Handle for the papyrus interface
static SKSEPapyrusInterface* g_papyrus = NULL;

// Handle for other things...

/* // Uncomment to use messaging
// Handle for the messaging interface
static SKSEMessagingInterface* g_messaging = NULL;
*/

// ================================
// User Code
// ================================

// Example namespace and test bool function to print Hello World!
namespace Plugin_Example_Functions
{
	bool Test(StaticFunctionTag *base)
	{
		_MESSAGE("Hello World!"); // print to the plugin log
		Console_Print("Hello Console!"); // print to the in-game console
		return true;
	}
}

// Register the function(s) in the Plugin_Example_Functions namespace
bool RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		// EzSkse64aeTestClass is defined in .\Data\Scripts\Source\EzSkse64aeTestClass.psc
		new NativeFunction0 <StaticFunctionTag, bool>("Test", "EzSkse64aeTestClass", Plugin_Example_Functions::Test, registry));
	
	return true; // return false if something goes wrong, EG: if doing other stuff
}

// ================================
// Plugin Listener
// ================================

/* // Uncomment to use messaging
// Listener for the plugin
static void PluginListener(SKSEMessagingInterface::Message* msg) noexcept
{
	switch (msg->type) {
		// case SKSEMessagingInterface::kMessage_PostLoad:
		case SKSEMessagingInterface::kMessage_PostPostLoad:
		{
			_MESSAGE("PluginListener: kMessage_PostPostLoad");
			break;
		}
		// case SKSEMessagingInterface::kMessage_PreLoadGame:
		// case SKSEMessagingInterface::kMessage_PostLoadGame:
		// case SKSEMessagingInterface::kMessage_SaveGame:
		// case SKSEMessagingInterface::kMessage_DeleteGame:
		// case SKSEMessagingInterface::kMessage_InputLoaded:
		// case SKSEMessagingInterface::kMessage_NewGame:
		case SKSEMessagingInterface::kMessage_DataLoaded:
		{
			_MESSAGE("PluginListener: kMessage_DataLoaded");
			break;
		}
	}
}
*/

// ================================
// Plugin Compatibility Check
// ================================

// Check that the runtime and plugin versions are compatible
const bool IsCompatible(const SKSEInterface* skse)
{
	// disable the plugin if it's in the editor
	if (skse->isEditor) {
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with the editor, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with the editor, disabling");
		return false;
	}
	// check for compatible version. if strict=true, runtime and supported versions must match. if strict=false, runtime version must be above the minimum
	else if (!IVersionCheck::IsCompatibleVersion(skse->runtimeVersion, MINIMUM_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION_STRICT)) { // not strict
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		
		// not compatible
		return false;
	}
	
	// compatible
	return true;
}

// ================================
// Plugin Export, Query and Load - Start Extern-C
// ================================

extern "C" { // Start: extern "C"

// ================================
// Plugin Version Data - Not Used In All SE SDK's
// ================================

// Export the plugin version data to skse64ae, without this the plugin will fail to load. See: PluginAPI.h
__declspec(dllexport) SKSEPluginVersionData SKSEPlugin_Version =
{
	SKSEPluginVersionData::kVersion, // skse64ae expects plugin version info to follow this structure
	
	PLUGIN_VERSION_DLL,		// set in config.h
	PLUGIN_NAME_LONG, 		// set in config.h
	PLUGIN_AUTHOR, 			// set in config.h
	"support@example.com", // FIXME - only in skse64ae??? YES!

	0,	// not version independent (extended field)
	0,	// not version independent
	
	// { RUNTIME_VERSION_1_6_318, 0 },	// compatible with 1.6.318
	{ SUPPORTED_RUNTIME_VERSION, 0 },	// set in config.h
	
	0,	// works with any version of the script extender. you probably do not need to put anything here
};

// ================================
// Plugin Query - Not Used In All SE SDK's
// ================================

// SKSE Plugin Query - Called when the plugin is queried
bool SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);
	
	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Query: Querying");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		PLUGIN_NAME_LONG;		// set in config.h
	info->version =		PLUGIN_VERSION_DLL;		// set in config.h
	
	// check for compatible versions
	if (!IsCompatible(skse)) {
		_MESSAGE("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// ######################################################
	// Note: Nothing should be assigned below this point
	// Get the necessary info about the plugin and return
	// ######################################################
	
	_MESSAGE("Plugin_Query: Queried Successfully"); // log the successful query

	// supported runtime version
	return true;
}

// ================================
// Plugin Preload - Not Used In All SE SDK's
// ================================

/*
// SKSE64AE does not use this
bool SKSEPlugin_Preload(const SKSEInterface* skse)
{
}
*/

// ================================
// Plugin Load - Used In All SE SDK's
// ================================

// SKSE Plugin Load - Called when the plugin loads everytime
bool SKSEPlugin_Load(const SKSEInterface* skse)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);

	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Load: Loading");
	
	// check for compatible versions
	if (!IsCompatible(skse)) {
		_MESSAGE("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// store plugin handle for later
	g_pluginHandle = skse->GetPluginHandle();
	
	// try to get the papyrus interface or disable if it's unable
	g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);
	if (!g_papyrus) {
		_MESSAGE("ERROR::Plugin_Load: Could not get the papyrus interface, disabling");
		_FATALERROR("ERROR::Plugin_Load: Could not get the papyrus interface, disabling");
		return false;
	}
	
	// register the new functions
	if (g_papyrus->Register(RegisterFuncs)) {
		_MESSAGE("Plugin_Load: Functions Registered");
	}
	
	/* // Uncomment to use messaging
	// register the listener
	g_messaging = (SKSEMessagingInterface*)skse->QueryInterface(kInterface_Messaging);
	if (g_messaging) {
		if (g_messaging->RegisterListener(g_pluginHandle, "SKSE", PluginListener)) {
			_MESSAGE("Plugin_Load: Listener Registered");
		}
	}
	*/
	
	_MESSAGE("Plugin_Load: Loaded Successfully"); // log the successful load

	// initialized
	return true;
}

}; // Stop: extern "C"

// ================================
