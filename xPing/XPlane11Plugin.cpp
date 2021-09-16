// Basic XPL skeleton

#include <XPLMProcessing.h>

#if IBM
	#include <Windows.h>
#endif // IBM

/**********************************************
	REQUIRED CALLBACKS
**********************************************/

// Called by XPlane when DLL is loaded - Returns 1 when successfully loaded
PLUGIN_API int XPluginStart(char *name, char *signature, char *description) {
	return 1;
}

// Called before the DLL is unloaded
PLUGIN_API void XPluginStop(void) {}

// Called before the plugin is enabled - Returns 1 when successfully starts
PLUGIN_API int XPluginEnable(void) {
	return 1;
}

// Called before the plugin is disabled
PLUGIN_API void XPluginDisable(void) {}

//Called by Plugin Manager when message is sent to us
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID from, int message, void *param) {}
