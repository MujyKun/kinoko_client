#pragma once

#define CONFIG_WINDOW_NAME      "Kinoko"
#define CONFIG_DLL_NAME         "Kinoko.dll"
#define CONFIG_LOG_FILE         "log.txt"

#define CONFIG_REGISTRY_KEY     "SOFTWARE\\Kinoko"
#define CONFIG_VERSION_STRING   "Ver. 95.1"
// #define CONFIG_IMAGE_LOADING    // comment out to disable image loading

#define CONFIG_SERVER_ADDRESS   "127.0.0.1"
#define CONFIG_NEXON_SEARCH     "63.251.217."

extern char* g_sServerAddress;
extern int g_nServerPort;