#include "hooks.h"


#include "global.h"
#include "imports.h"
#include "structs.h"
#include "utility.h"

NAMESPACE(Hooks)

gfxLoader_t gfxLoader_Stub;

uint64_t gfxLoader_hook(long long a1, const char *path, long long a3, unsigned int a4, unsigned int a5) {
	if(strstr(path, "font_lib_efigs")) {
		sceSysUtilSendSystemNotificationWithText(222, "font_lib_efigs_ps4.gfx Loaded.");
		return gfxLoader_Stub(a1, "/data/font_lib_efigs_ps4.gfx", a3, a4, a5);
	}
	return gfxLoader_Stub(a1, path, a3, a4, a5);
}
END
