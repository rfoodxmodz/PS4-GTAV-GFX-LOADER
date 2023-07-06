#include "types.h"
#include "imports.h"

//kernel
int(*sceKernelDebugOutText)(int debugChannel, const char* text);
unsigned int (*sceKernelSleep)(unsigned int seconds);
int (*sceKernelUsleep)(unsigned int microseconds);
int (*sceKernelGetCpuTemperature)(int *);
int (*sceKernelGetSocSensorTemperature)(int, int *);
ssize_t (*read)(int fd, void *buf, size_t nbyte);
ssize_t (*write)(int fd, const void *buf, size_t count);
int (*open)(const char *path, int flags, int mode);
int (*close)(int fd);
int (*unlink)(const char *pathname);
int (*usleep)(unsigned int microseconds);

//threads
int (*scePthreadCreate)(ScePthread *thread, const ScePthreadAttr *attr, void *entry, void *arg, const char *name);
void (*scePthreadExit)(void *value);
int (*scePthreadDetach)(ScePthread thread);
int (*scePthreadJoin)(ScePthread thread, void **value_ptr);
int (*scePthreadGetprio)(ScePthread thread, int *prio);

//network
int (*sceNetSocket)(const char *, int, int, int);
int (*sceNetSocketClose)(int);
int (*sceNetConnect)(int, struct sockaddr *, int);
int (*sceNetSend)(int, const void *, size_t, int);

//sys
int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

//notifications
int (*sceSysUtilSendSystemNotificationWithText)(int messageType, const char *message);

//message dialogs
int (*sceCommonDialogInitialize)(void);
int (*sceMsgDialogInitialize)(void);
int (*sceMsgDialogOpen)(const SceMsgDialogParam *param);
SceCommonDialogStatus (*sceMsgDialogUpdateStatus)(void);
int (*sceMsgDialogTerminate)(void);

//ime dialogs
int (*sceImeDialogGetResult)(SceImeDialogResult *result);
int (*sceImeDialogInit)(const SceImeDialogParam *param, void *extended);
SceImeDialogStatus (*sceImeDialogGetStatus)(void);
int (*sceImeDialogTerm)(void);

//web dialogs
int (*sceWebBrowserDialogInitialize)(void);
int (*sceWebBrowserDialogTerminate)(void);
int (*sceWebBrowserDialogOpen)(const SceWebBrowserDialogParam *param);
SceCommonDialogStatus (*sceWebBrowserDialogUpdateStatus)(void);
int (*sceWebBrowserDialogSetCookie)(const SceWebBrowserDialogSetCookieParam *param);

//user service
int (*sceUserServiceGetInitialUser)(SceUserServiceUserId *userId);
int (*sceUserServiceGetUserName)(const SceUserServiceUserId userId, char *userName, const size_t size);
int (*sceUserServiceGetLoginUserIdList)(SceUserServiceLoginUserIdList *userIdList);

//gamepad
int (*scePadOpen)(SceUserServiceUserId userId, int32_t type, int32_t index, const ScePadOpenParam *pParam);
int (*scePadGetHandle)(SceUserServiceUserId userId, int32_t type, int32_t index);
int (*scePadSetLightBar)(int32_t handle, const ScePadLightBarParam *pParam);
int (*scePadReadState)(int32_t handle, ScePadData *pData);

//libc
void *(*malloc)(size_t size);
void (*free)(void *ptr);
void *(*calloc)(size_t num, size_t size);
void *(*realloc)(void *ptr, size_t size);
void *(*memset)(void *destination, int value, size_t num);
void *(*memcpy)(void *destination, const void *source, size_t num);
int (*memcmp)(const void *s1, const void *s2, size_t n);
void *(*memmove)(void *str1, const void *str2, size_t n);
size_t (*mbstowcs)(wchar_t *dest, const char *src, size_t max);
size_t (*wcstombs)(char *dest, const wchar_t *src, size_t max);
char *(*strcpy)(char *destination, const char *source);
char *(*strncpy)(char *destination, const char *source, size_t num);
char *(*strcat)(char *dest, const char *src);
char *(*strncat)(char *dest, const char *src, size_t n);
size_t (*strlen)(const char *s);
char *(*strtok)(char *str, const char *delimiters);
int (*strcmp)(const char *s1, const char *s2);
int (*strncmp)(const char *s1, const char *s2, size_t n);
int (*sprintf)(char *str, const char *format, ...);
int (*snprintf)(char *str, size_t size, const char *format, ...);
int (*vsprintf)(char *s, const char *format, va_list arg);
int (*sscanf)(const char *str, const char *format, ...);
char *(*strchr)(const char *s, int c);
char *(*strrchr)(const char *s, int c);
char *(*strstr)(char *str1, char *str2);
int (*atoi)(const char *str);
double (*atof)(const char *str);
double (*sin)(double x);
float (*sinf)(float x);
double (*cos)(double x);
float (*cosf)(float x);
double (*tan)(double x);
float (*tanf)(float x);
double (*atan)(double x);
double (*atan2)(double x, double y);
double (*sqrt)(double vec);
float (*sqrtf)(float vec);
double (*pow)(double x, double y);
int (*abs)(int n);
double(*fmin)(double x, double y);
double(*fmax)(double x, double y);
int(*isspace)(int c);
int(*isupper)(int c);
int(*islower)(int c);
int(*toupper)(int c);
int(*tolower)(int c);

int getpid() {
	return syscall(20);
}

void *sys_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset) {
	return (void *)syscall(477, addr, len, prot, flags, fd, offset);
}

void *sys_munmap(void *addr, size_t len) {
	return (void *)syscall(479, addr, len);
}

int sys_dynlib_dlsym(int loadedModuleID, const char *name, void *destination) {
	return syscall(591, loadedModuleID, name, destination);
}

int sys_dynlib_load_prx(const char *name, int *idDestination) {
	return syscall(594, name, 0, idDestination, 0);
}

int sys_dynlib_unload_prx(int id) {
	return syscall(595, id, 0, 0);
}

void initImports() {
	int h = 0;

	//kernel
	sys_dynlib_load_prx("libkernel.sprx", &h);
	sys_dynlib_dlsym(h, "sceKernelDebugOutText", &sceKernelDebugOutText);
	sys_dynlib_dlsym(h, "sceKernelSleep", &sceKernelSleep);
	sys_dynlib_dlsym(h, "sceKernelUsleep", &sceKernelUsleep);
	sys_dynlib_dlsym(h, "sceKernelGetCpuTemperature", &sceKernelGetCpuTemperature);
	sys_dynlib_dlsym(h, "sceKernelGetSocSensorTemperature", &sceKernelGetSocSensorTemperature);
	sys_dynlib_dlsym(h, "read", &read);
	sys_dynlib_dlsym(h, "write", &write);
	sys_dynlib_dlsym(h, "open", &open);
	sys_dynlib_dlsym(h, "close", &close);
	sys_dynlib_dlsym(h, "unlink", &unlink);
	sys_dynlib_dlsym(h, "usleep", &usleep);

	//threads
	sys_dynlib_dlsym(h, "scePthreadCreate", &scePthreadCreate);
	sys_dynlib_dlsym(h, "scePthreadExit", &scePthreadExit);
	sys_dynlib_dlsym(h, "scePthreadDetach", &scePthreadDetach);
	sys_dynlib_dlsym(h, "scePthreadJoin", &scePthreadJoin);
	sys_dynlib_dlsym(h, "scePthreadGetprio", &scePthreadGetprio);

	//network
	sys_dynlib_load_prx("libSceNet.sprx", &h);
	sys_dynlib_dlsym(h, "sceNetSocket", &sceNetSocket);
	sys_dynlib_dlsym(h, "sceNetSocketClose", &sceNetSocketClose);
	sys_dynlib_dlsym(h, "sceNetConnect", &sceNetConnect);
	sys_dynlib_dlsym(h, "sceNetSend", &sceNetSend);

	//message dialogs
	sys_dynlib_load_prx("libSceCommonDialog.sprx", &h);
	sys_dynlib_dlsym(h, "sceCommonDialogInitialize", &sceCommonDialogInitialize);

	sys_dynlib_load_prx("libSceMsgDialog.sprx", &h);
	sys_dynlib_dlsym(h, "sceMsgDialogInitialize", &sceMsgDialogInitialize);
	sys_dynlib_dlsym(h, "sceMsgDialogOpen", &sceMsgDialogOpen);
	sys_dynlib_dlsym(h, "sceMsgDialogUpdateStatus", &sceMsgDialogUpdateStatus);
	sys_dynlib_dlsym(h, "sceMsgDialogTerminate", &sceMsgDialogTerminate);

	//ime dialogs
	sys_dynlib_load_prx("libSceImeDialog.sprx", &h);
	sys_dynlib_dlsym(h, "sceImeDialogGetResult", &sceImeDialogGetResult);
	sys_dynlib_dlsym(h, "sceImeDialogInit", &sceImeDialogInit);
	sys_dynlib_dlsym(h, "sceImeDialogGetStatus", &sceImeDialogGetStatus);
	sys_dynlib_dlsym(h, "sceImeDialogTerm", &sceImeDialogTerm);

	//web dialogs
	sys_dynlib_load_prx("libSceWebBrowserDialog.sprx", &h);
	sys_dynlib_dlsym(h, "sceWebBrowserDialogInitialize", &sceWebBrowserDialogInitialize);
	sys_dynlib_dlsym(h, "sceWebBrowserDialogTerminate", &sceWebBrowserDialogTerminate);
	sys_dynlib_dlsym(h, "sceWebBrowserDialogOpen", &sceWebBrowserDialogOpen);
	sys_dynlib_dlsym(h, "sceWebBrowserDialogUpdateStatus", &sceWebBrowserDialogUpdateStatus);
	sys_dynlib_dlsym(h, "sceWebBrowserDialogSetCookie", &sceWebBrowserDialogSetCookie);

	//user service
	sys_dynlib_load_prx("libSceUserService.sprx", &h);
	sys_dynlib_dlsym(h, "sceUserServiceGetInitialUser", &sceUserServiceGetInitialUser);
	sys_dynlib_dlsym(h, "sceUserServiceGetUserName", &sceUserServiceGetUserName);
	sys_dynlib_dlsym(h, "sceUserServiceGetLoginUserIdList", &sceUserServiceGetLoginUserIdList);

	//gamepad
	sys_dynlib_load_prx("libScePad.sprx", &h);
	sys_dynlib_dlsym(h, "scePadOpen", &scePadOpen);
	sys_dynlib_dlsym(h, "scePadGetHandle", &scePadGetHandle);
	sys_dynlib_dlsym(h, "scePadSetLightBar", &scePadSetLightBar);
	sys_dynlib_dlsym(h, "scePadReadState", &scePadReadState);

	//libc
	sys_dynlib_load_prx("libSceLibcInternal.sprx", &h);
	sys_dynlib_dlsym(h, "malloc", &malloc);
	sys_dynlib_dlsym(h, "free", &free);
	sys_dynlib_dlsym(h, "calloc", &calloc);
	sys_dynlib_dlsym(h, "realloc", &realloc);
	sys_dynlib_dlsym(h, "memset", &memset);
	sys_dynlib_dlsym(h, "memcpy", &memcpy);
	sys_dynlib_dlsym(h, "memcmp", &memcmp);
	sys_dynlib_dlsym(h, "memmove", &memmove);
	sys_dynlib_dlsym(h, "mbstowcs", &mbstowcs);
	sys_dynlib_dlsym(h, "wcstombs", &wcstombs);
	sys_dynlib_dlsym(h, "strcpy", &strcpy);
	sys_dynlib_dlsym(h, "strncpy", &strncpy);
	sys_dynlib_dlsym(h, "strcat", &strcat);
	sys_dynlib_dlsym(h, "strncat", &strncat);
	sys_dynlib_dlsym(h, "strlen", &strlen);
	sys_dynlib_dlsym(h, "strtok", &strtok);
	sys_dynlib_dlsym(h, "strcmp", &strcmp);
	sys_dynlib_dlsym(h, "strncmp", &strncmp);
	sys_dynlib_dlsym(h, "sprintf", &sprintf);
	sys_dynlib_dlsym(h, "snprintf", &snprintf);
	sys_dynlib_dlsym(h, "vsprintf", &vsprintf);
	sys_dynlib_dlsym(h, "sscanf", &sscanf);
	sys_dynlib_dlsym(h, "strchr", &strchr);
	sys_dynlib_dlsym(h, "strrchr", &strrchr);
	sys_dynlib_dlsym(h, "strstr", &strstr);
	sys_dynlib_dlsym(h, "atoi", &atoi);
	sys_dynlib_dlsym(h, "atof", &atof);
	sys_dynlib_dlsym(h, "sin", &sin);
	sys_dynlib_dlsym(h, "sinf", &sinf);
	sys_dynlib_dlsym(h, "cos", &cos);
	sys_dynlib_dlsym(h, "cosf", &cosf);
	sys_dynlib_dlsym(h, "tan", &tan);
	sys_dynlib_dlsym(h, "tanf", &tanf);
	sys_dynlib_dlsym(h, "atan", &atan);
	sys_dynlib_dlsym(h, "atan2", &atan2);
	sys_dynlib_dlsym(h, "sqrt", &sqrt);
	sys_dynlib_dlsym(h, "sqrtf", &sqrtf);
	sys_dynlib_dlsym(h, "pow", &pow);
	sys_dynlib_dlsym(h, "abs", &abs);
	sys_dynlib_dlsym(h, "fmin", &fmin);
	sys_dynlib_dlsym(h, "fmax", &fmax);
	sys_dynlib_dlsym(h, "isspace", &isspace);
	sys_dynlib_dlsym(h, "isupper", &isupper);
	sys_dynlib_dlsym(h, "islower", &islower);
	sys_dynlib_dlsym(h, "toupper", &toupper);
	sys_dynlib_dlsym(h, "tolower", &tolower);

	//sys
	if (sys_dynlib_load_prx("libkernel.sprx", &h))
		if (sys_dynlib_load_prx("libkernel_web.sprx", &h))
			sys_dynlib_load_prx("libkernel_sys.sprx", &h);

	sys_dynlib_dlsym(h, "sceKernelLoadStartModule", &sceKernelLoadStartModule);

	//notify
	int sysUtilHandle = sceKernelLoadStartModule("libSceSysUtil.sprx", 0, NULL, 0, 0, 0);
	sys_dynlib_dlsym(sysUtilHandle, "sceSysUtilSendSystemNotificationWithText", &sceSysUtilSendSystemNotificationWithText);
}
