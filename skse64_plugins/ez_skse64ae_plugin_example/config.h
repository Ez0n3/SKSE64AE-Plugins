#pragma once
#include "skse64_common/skse_version.h" // SKSE64AE
#include "IVersionCheck.h" // Common plugin version check, found in ..\plugins_common\
// #include "../plugin_common/common.h" // EG: Common plugin functions for this sdk if needed

// ================================
// Plugin Information
// ================================

// Plugin info
#define PLUGIN_AUTHOR				"Ez0n3"					// Author of the plugin

#define PLUGIN_NAME_SHORT			"ez_skse64ae_plugin_example"	// Plugin name without spaces
#define PLUGIN_NAME_LONG			"Ez SKSE64AE Plugin Example"	// Plugin name with spaces

// Plugin version, Major, Minor, Build. EG: (1.0.0) equals (Major.Minor.Build)
#define PLUGIN_VERSION_MAJOR		1
#define PLUGIN_VERSION_MINOR		0
#define PLUGIN_VERSION_BUILD		0

// ================================
// Nothing below this needs changing between plugins except maybe MINIMUM_RUNTIME_VERSION and/or SUPPORTED_RUNTIME_VERSION_STRICT
// ================================

// Plugin log file
#define PLUGIN_LOG_FILE				"\\My Games\\" GAME_SAVE_FOLDER_NAME("Skyrim Special Edition") "\\SKSE\\" PLUGIN_LOG_FILE_NAME(PLUGIN_NAME_SHORT) // plugin log file location

// Common definitions
#define SDK_VERSION_STRING			VERSION_TO_STRING(SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA)
#define PLUGIN_VERSION_STRING		VERSION_TO_STRING(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)

#define PLUGIN_VERSION_DLL			MAKE_EXE_VERSION(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)
#define PLUGIN_VERSION_INFO			PLUGIN_NAME_SHORT " v%s (0x%08X) (SDK v%s)", PLUGIN_VERSION_STRING, PLUGIN_VERSION_DLL, SDK_VERSION_STRING

// ================================
// Plugin Version Information
// ================================

// The minimum runtime version allowed by the plugin. EG: I need function X, which was added in runtime Y, therefore Y is the minimum runtime version
#define MINIMUM_RUNTIME_VERSION				RUNTIME_VERSION_1_6_317	// The lowest anniversary edition version and special edition versions above RUNTIME_VERSION_1_5_97

// The runtime version the plugin was designed for
// #define SUPPORTED_RUNTIME_VERSION		CURRENT_RELEASE_RUNTIME
#define SUPPORTED_RUNTIME_VERSION			RUNTIME_VERSION // Set in /config/_Plugins.props, controls core and plugin versions - normally latest

// Strict runtime version. If strict=true, runtime and supported versions must match. If strict=false, runtime version must be above the minimum
#define SUPPORTED_RUNTIME_VERSION_STRICT	false

// The compatible runtime version - set automatically
#define COMPATIBLE(runtimeVersion)			(runtimeVersion == SUPPORTED_RUNTIME_VERSION)

// ================================

/*
// From skse_version.h

#define RUNTIME_VERSION_1_1_47	MAKE_EXE_VERSION(1, 1, 47)			// 0x010102F0	initial version released on steam, has edit-and-continue enabled
#define RUNTIME_VERSION_1_1_51	MAKE_EXE_VERSION(1, 1, 51)			// 0x01010330	initial version released on steam, has edit-and-continue enabled
#define RUNTIME_VERSION_1_2_36	MAKE_EXE_VERSION(1, 2, 36)			// 0x01020240	edit-and-continue disabled
#define RUNTIME_VERSION_1_2_39	MAKE_EXE_VERSION(1, 2, 39)			// 0x01020270	edit-and-continue disabled
#define RUNTIME_VERSION_1_3_5	MAKE_EXE_VERSION(1, 3, 5)			// 0x01030050	
#define RUNTIME_VERSION_1_3_9	MAKE_EXE_VERSION(1, 3, 9)			// 0x01030090	
#define RUNTIME_VERSION_1_4_2	MAKE_EXE_VERSION(1, 4, 2)			// 0x01040020	
#define RUNTIME_VERSION_1_5_3	MAKE_EXE_VERSION(1, 5, 3)			// 0x01050030	creation club
#define RUNTIME_VERSION_1_5_16	MAKE_EXE_VERSION(1, 5, 16)			// 0x01050100	creation club cleanup (thanks)
#define RUNTIME_VERSION_1_5_23	MAKE_EXE_VERSION(1, 5, 23)			// 0x01050170	creation club
#define RUNTIME_VERSION_1_5_39	MAKE_EXE_VERSION(1, 5, 39)			// 0x01050270	creation club
#define RUNTIME_VERSION_1_5_50	MAKE_EXE_VERSION(1, 5, 50)			// 0x01050320	creation club
#define RUNTIME_VERSION_1_5_53	MAKE_EXE_VERSION(1, 5, 53)			// 0x01050350	creation club
#define RUNTIME_VERSION_1_5_62	MAKE_EXE_VERSION(1, 5, 62)			// 0x010503E0	creation club
#define RUNTIME_VERSION_1_5_73	MAKE_EXE_VERSION(1, 5, 73)			// 0x01050490	creation club
#define RUNTIME_VERSION_1_5_80	MAKE_EXE_VERSION(1, 5, 80)			// 0x01050500	creation club - no code or data differences
#define RUNTIME_VERSION_1_5_97	MAKE_EXE_VERSION(1, 5, 97)			// 0x01050610	creation club
#define RUNTIME_VERSION_1_6_317	MAKE_EXE_VERSION(1, 6, 317)			// 0x010613D0	anniversary edition
#define RUNTIME_VERSION_1_6_318	MAKE_EXE_VERSION(1, 6, 318)			// 0x010613E0
#define RUNTIME_VERSION_1_6_323	MAKE_EXE_VERSION(1, 6, 323)			// 0x01061430
#define RUNTIME_VERSION_1_6_342	MAKE_EXE_VERSION(1, 6, 342)			// 0x01061560
#define RUNTIME_VERSION_1_6_353	MAKE_EXE_VERSION(1, 6, 353)			// 0x01061610
#define RUNTIME_VERSION_1_6_629	MAKE_EXE_VERSION(1, 6, 629)			// 0x01062750	to be hotfixed
#define RUNTIME_VERSION_1_6_640	MAKE_EXE_VERSION(1, 6, 640)			// 0x01062800	the hotfix
#define RUNTIME_VERSION_1_6_659_GOG	MAKE_EXE_VERSION_EX(1, 6, 659, RUNTIME_TYPE_GOG)
																	// 0x01062931
#define RUNTIME_VERSION_1_6_678_EPIC	MAKE_EXE_VERSION_EX(1, 6, 678, RUNTIME_TYPE_EPIC)
																	// 0x01062A62
#define RUNTIME_VERSION_1_6_1130	MAKE_EXE_VERSION(1, 6, 1130)	// 0x010646A0	creations patch
#define RUNTIME_VERSION_1_6_1170	MAKE_EXE_VERSION(1, 6, 1170)	// 0x01064920
#define RUNTIME_VERSION_1_6_1170_GOG	MAKE_EXE_VERSION_EX(1, 6, 1170, RUNTIME_TYPE_GOG)
																	// 0x01064921	same version number as steam, possible problem													
*/
