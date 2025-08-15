#pragma once
#include "IPluginCommon.h"
#include <cstdint> // Required for uint32_t 

// UInt32 // does not work with all SDK's
// uint32_t // works with all SDK's

namespace IVersionCheck
{ // Start IVersionCheck namespace

// Check for compatible version - See: (x)se_versions.h, EG: f4se_versions.h
// Strict means the runtime and supported versions must match
// Otherwise it's lenient which means, it must be above the minimum
const bool IsCompatibleVersion(const std::uint32_t runtimeVersion, const std::uint32_t minimumRuntimeVersion, const std::uint32_t supportedRuntimeVersion, const bool strict = true)
{
	// get versions to strings for printing
	char runtimeVersionStr[64];
	sprintf_s(runtimeVersionStr, sizeof(runtimeVersionStr), "%d.%d.%d.%d", 
		GET_EXE_VERSION_MAJOR(runtimeVersion), 
		GET_EXE_VERSION_MINOR(runtimeVersion), 
		GET_EXE_VERSION_BUILD(runtimeVersion), 
		GET_EXE_VERSION_SUB(runtimeVersion));
	
	char minimumRuntimeVersionStr[64];
	sprintf_s(minimumRuntimeVersionStr, sizeof(minimumRuntimeVersionStr), "%d.%d.%d.%d", 
		GET_EXE_VERSION_MAJOR(minimumRuntimeVersion), 
		GET_EXE_VERSION_MINOR(minimumRuntimeVersion), 
		GET_EXE_VERSION_BUILD(minimumRuntimeVersion), 
		GET_EXE_VERSION_SUB(minimumRuntimeVersion));
	
	char supportedRuntimeVersionStr[64];
	sprintf_s(supportedRuntimeVersionStr, sizeof(supportedRuntimeVersionStr), "%d.%d.%d.%d", 
		GET_EXE_VERSION_MAJOR(supportedRuntimeVersion), 
		GET_EXE_VERSION_MINOR(supportedRuntimeVersion), 
		GET_EXE_VERSION_BUILD(supportedRuntimeVersion), 
		GET_EXE_VERSION_SUB(supportedRuntimeVersion));
	
	// Strict - the versions must match, runtime and supported
	if (strict) {
		// if the runtime is the Strict supported version, See: config.h in the plugin folder
		if (runtimeVersion == supportedRuntimeVersion) { // supported
			// versions match
			_MESSAGE("IsCompatibleVersion: Runtime Version: %s (0x%08X) | Plugin Supported Runtime Version: %s (0x%08X) | Status: Enabled", 
				runtimeVersionStr, runtimeVersion, supportedRuntimeVersionStr, supportedRuntimeVersion);
		}
		else { // unsupported
			// versions do not match
			_MESSAGE("ERROR::IsCompatibleVersion: Unsupported Runtime Version: %s (0x%08X) | Strict Plugin Supported Runtime Version: %s (0x%08X) | Status: Disabled", 
				runtimeVersionStr, runtimeVersion, supportedRuntimeVersionStr, supportedRuntimeVersion);
			_FATALERROR("ERROR::IsCompatibleVersion: Unsupported Runtime Version: %s (0x%08X) | Strict Plugin Supported Runtime Version: %s (0x%08X) | Status: Disabled", 
				runtimeVersionStr, runtimeVersion, supportedRuntimeVersionStr, supportedRuntimeVersion);
			return false;
		}
	}
	// Lenient - they don't have to match, but it must be above the minimum supported
	else {
		// if the runtime is the supported version, See: config.h in the plugin folder
		if (runtimeVersion == supportedRuntimeVersion) { // supported
			// versions match
			_MESSAGE("IsCompatibleVersion: Runtime Version: %s (0x%08X) | Plugin Supported Runtime Version: %s (0x%08X) | Status: Enabled", 
				runtimeVersionStr, runtimeVersion, supportedRuntimeVersionStr, supportedRuntimeVersion);
		}
		// if the runtime is less than the minimum required, disable
		else if (runtimeVersion < minimumRuntimeVersion) { // smaller than minimum supported
			_MESSAGE("ERROR::IsCompatibleVersion: Unsupported Runtime Version: %s (0x%08X) | Minimum Required Plugin Runtime Version: %s (0x%08X) | Status: Disabled", 
				runtimeVersionStr, runtimeVersion, minimumRuntimeVersionStr, minimumRuntimeVersion);
			_FATALERROR("ERROR::IsCompatibleVersion: Unsupported Runtime Version: %s (0x%08X) | Minimum Required Plugin Runtime Version: %s (0x%08X) | Status: Disabled",
				runtimeVersionStr, runtimeVersion, minimumRuntimeVersionStr, minimumRuntimeVersion);
			return false;
		}
		// if the runtime is less than the currently supported, but greater than the minimum required
		else if (runtimeVersion < supportedRuntimeVersion) { // smaller than supported, but larger than minimum
			// load anyway, but log a warning
			_MESSAGE("WARNING::IsCompatibleVersion: Unsupported Lesser Runtime Version: %s (0x%08X) | Plugin Supported Runtime Version: %s (0x%08X) | Status: Enabled (Caution)", 
				runtimeVersionStr, runtimeVersion, supportedRuntimeVersionStr, supportedRuntimeVersion);
		}
		// if the runtime is greater than the supported version
		else { // larger than supported
			// load anyway, but log a warning
			_MESSAGE("WARNING::IsCompatibleVersion: Unsupported Greater Runtime Version: %s (0x%08X) | Plugin Supported Runtime Version: %s (0x%08X) | Status: Enabled (Caution)", 
				runtimeVersionStr, runtimeVersion, supportedRuntimeVersionStr, supportedRuntimeVersion);
		}
	}
	
	// is compatible
	return true;
}

} // Stop IVersionCheck namespace
