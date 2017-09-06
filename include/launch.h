#pragma once
#include "includes.h"
#include "menu.h"

extern void (*__system_retAddr)(void);

enum
{
	LOADER_SHOW_REBOOT = BIT(0),
	LOADER_NEED_SCAN   = BIT(1),
};

typedef struct
{
	// Mandatory fields
	const char* name;
	u32 flags;
	bool (* init)(void);
	void (* deinit)(void);
	void (* launchFile)(const char* path, argData_s* args, executableMetadata_s* em);

	// Optional fields
	void (* useTitle)(u64 tid, u8 mediatype);
} loaderFuncs_s;

void launchInit(void);
void launchExit(void);
const loaderFuncs_s* launchGetLoader(void);
size_t launchAddArg(argData_s* ad, const char* arg);
void launchAddArgsFromString(argData_s* ad, char* arg);
void launchMenuEntry(menuEntry_s* me);
Handle launchOpenFile(const char* path);
bool launchHomeMenuEnabled(void);
void launchHomeMenu(void);

static inline bool loaderHasFlag(u32 flag)
{
	return (launchGetLoader()->flags & flag) != 0;
}

static inline bool loaderCanUseTitles(void)
{
	return launchGetLoader()->useTitle != NULL;
}
