#include <stdint.h>
#include <stdarg.h>
#include "detour.h"
#include "global.h"
#include "hooks.h"
#include "imports.h"
#include "library_functions.h"
#include "types.h"
#include "utility.h"

long APP_BASE = 0x400000;

void setupHook() {
	memcpy((void *)(0x20D0F80 + APP_BASE), "\x55\x48\x89\xE5\x41\x57\x41\x56\x53\x50\x49\x89\xD7\x49\x89\xF6", 16);//sub_20D0F80 1.46
	Hooks::gfxLoader_Stub = (Hooks::gfxLoader_t)DetourFunction((0x20D0F80 + APP_BASE), (void *)Hooks::gfxLoader_hook, 16);
}

extern "C" void _main(void) {
	char userName[20];
	char welcomeMessage[100];
	initImports();
	Sleep(100);

	SceUserServiceLoginUserIdList userIdList;
	sceUserServiceGetLoginUserIdList(&userIdList);

	for (int i = 0; i < 4; i++) {
		if (userIdList.userId[i] != -1) {
			userId = userIdList.userId[i];
			break;
		}
	}
	sceUserServiceGetUserName(userId, userName, 20);
	snprintf(welcomeMessage, sizeof(welcomeMessage), "Welcome %s!\n[GTAV 1.46] - GFX Loader.", userName);
	sceSysUtilSendSystemNotificationWithText(222, welcomeMessage);
	setupHook();
}