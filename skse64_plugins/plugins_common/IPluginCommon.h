#pragma once

// ================================
// Fallout3 And Oblivion
// ================================

// Fallout3 and Oblivion do not use "RUNTIME_VERSION", defining it here for commonality
// FIXME - i should now be able to remove the RUNTIME_VERSION preproc for this for these 2 games that i added
#ifdef FALLOUT_VERSION
#ifndef RUNTIME_VERSION
#define RUNTIME_VERSION		FALLOUT_VERSION
#endif // RUNTIME_VERSION
#endif // FALLOUT_VERSION

#ifdef OBLIVION_VERSION
#ifndef RUNTIME_VERSION
#define RUNTIME_VERSION		OBLIVION_VERSION
#endif // RUNTIME_VERSION
#endif // OBLIVION_VERSION

/*
// FIXME - do not set this incase it is in the editor?
#ifndef RUNTIME
#define RUNTIME				1
#endif // RUNTIME
*/

// ================================
// Common Macros
// ================================

// Convert to string
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)


// Convert version to string - int and not Uint32
#define VERSION_TO_STRING_EX(major, minor, build, sub)	TO_STRING(major) "." TO_STRING(minor) "." TO_STRING(build) "." TO_STRING(sub)
// #define VERSION_TO_STRING(major, minor, build)			VERSION_TO_STRING_EX(major, minor, build, 0)
#define VERSION_TO_STRING(major, minor, build)			TO_STRING(major) "." TO_STRING(minor) "." TO_STRING(build)


// Some SDK's use different naming conventions for this, defining it here for commonality if need be
#ifndef GET_EXE_VERSION_MAJOR
#define GET_EXE_VERSION_MAJOR(a)	(((a) & 0xFF000000) >> 24)
#endif // GET_EXE_VERSION_MAJOR

#ifndef GET_EXE_VERSION_MINOR
#define GET_EXE_VERSION_MINOR(a)	(((a) & 0x00FF0000) >> 16)
#endif // GET_EXE_VERSION_MINOR

#ifndef GET_EXE_VERSION_BUILD
#define GET_EXE_VERSION_BUILD(a)	(((a) & 0x0000FFF0) >> 4)
#endif // GET_EXE_VERSION_BUILD

#ifndef GET_EXE_VERSION_SUB
#define GET_EXE_VERSION_SUB(a)		(((a) & 0x0000000F) >> 0)
#endif // GET_EXE_VERSION_SUB

#ifndef MAKE_EXE_VERSION_EX
#define MAKE_EXE_VERSION_EX(major, minor, build, sub)	((((major) & 0xFF) << 24) | (((minor) & 0xFF) << 16) | (((build) & 0xFFF) << 4) | ((sub) & 0xF))
#endif // MAKE_EXE_VERSION_EX

#ifndef MAKE_EXE_VERSION
#define MAKE_EXE_VERSION(major, minor, build)			MAKE_EXE_VERSION_EX(major, minor, build, 0)
#endif // MAKE_EXE_VERSION


// Some SDK's don't have this, defining it here for commonality if need be
#ifndef RUNTIME_TYPE_BETHESDA
#define RUNTIME_TYPE_BETHESDA		0
#endif // RUNTIME_TYPE_BETHESDA

#ifndef RUNTIME_TYPE_GOG
#define RUNTIME_TYPE_GOG			1
#endif // RUNTIME_TYPE_GOG

#ifndef RUNTIME_TYPE_EPIC
#define	RUNTIME_TYPE_EPIC			2
#endif // RUNTIME_TYPE_EPIC

#ifndef RUNTIME_TYPE_MSSTORE
#define	RUNTIME_TYPE_MSSTORE		3
#endif // RUNTIME_TYPE_MSSTORE


// ================================
// Plugin Information
// ================================

// Get the save folder name append
// Some games are released by multiple distributors and some distributors append their brand acronym to the save folder name. EG: 
// Bethesda does not: "Fallout4"
// GOG does: "Fallout4 GOG"
// EPIC does: "Fallout4 EPIC"
// Microsoft Store does: "Fallout4 MS"
// If the defines fail to detect the distributor, it will default to append nothing: EG: "Fallout4"
//
#if GET_EXE_VERSION_SUB(RUNTIME_VERSION) == RUNTIME_TYPE_BETHESDA
#define GAME_SAVE_FOLDER_NAME_APPEND "" // append nothing, BethSoft Steam does not use this
#elif GET_EXE_VERSION_SUB(RUNTIME_VERSION) == RUNTIME_TYPE_GOG
// gog
#define GAME_SAVE_FOLDER_NAME_APPEND " GOG"
#elif GET_EXE_VERSION_SUB(RUNTIME_VERSION) == RUNTIME_TYPE_EPIC
// epic
#define GAME_SAVE_FOLDER_NAME_APPEND " EPIC"
#elif GET_EXE_VERSION_SUB(RUNTIME_VERSION) == RUNTIME_TYPE_MSSTORE
// ms store
#define GAME_SAVE_FOLDER_NAME_APPEND " MS"
#else
_MESSAGE("WARNING::SaveFolder: Unknown runtime type, using default save folder name append");
#define GAME_SAVE_FOLDER_NAME_APPEND "" // append nothing if the distributor is not detected
#endif

// Some SDK's don't have this, defining and renaming it here for commonality
#define GAME_SAVE_FOLDER_NAME(game_name)	game_name GAME_SAVE_FOLDER_NAME_APPEND // append distributor acronym if needed


// Get the plugin log file name append
// Some games have a NOGORE preprocessor definition (EG: NVSE). If NOGORE is defined, append "_ng" to the plugin log file
#ifdef NOGORE
#define PLUGIN_LOG_FILE_NAME_APPEND	"_ng" // append "_ng" to the NOGORE log file
#else
#define PLUGIN_LOG_FILE_NAME_APPEND	"" // append nothing if NOGORE is not set
#endif

// Get the plugin log file name
#define PLUGIN_LOG_FILE_NAME(plugin_name)	plugin_name PLUGIN_LOG_FILE_NAME_APPEND ".log" // append nogore if needed
