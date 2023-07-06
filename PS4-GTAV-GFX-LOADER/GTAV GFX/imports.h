#pragma once

#include <stdint.h>
#include <stdarg.h>

#include "types.h"
#include "syscall.h"

#define AF_INET 0x0002

#define IN_ADDR_ANY 0

#define SOCK_STREAM 1
#define SOCK_DGRAM 2

#define SOL_SOCKET 0xFFFF
#define SO_NBIO 0x1200

#define MSG_DONTWAIT 0x80
#define MSG_WAITALL 0x40

#define IPPROTO_TCP 6
#define TCP_NODELAY 1

#define SCE_USER_SERVICE_USER_ID_EVERYONE 254

enum {
	SCE_NET_IPPROTO_IP = 0,
	SCE_NET_IPPROTO_ICMP = 1,
	SCE_NET_IPPROTO_IGMP = 2,
	SCE_NET_IPPROTO_TCP = 6,
	SCE_NET_IPPROTO_UDP = 17,
	SCE_NET_SOL_SOCKET = 0xFFFF
};

enum {
	SCE_NET_SO_REUSEADDR = 0x00000004,
};

enum {
	SCE_NET_ERROR_EINTR = 0x80410104,
};

enum {
	SCE_NET_SOCKET_ABORT_FLAG_RCV_PRESERVATION = 0x00000001,
	SCE_NET_SOCKET_ABORT_FLAG_SND_PRESERVATION = 0x00000002
};

struct in_addr {
	unsigned int s_addr;
};

struct sockaddr_in {
	unsigned char sin_len;
	unsigned char sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	unsigned short sin_vport;
	char sin_zero[6];
};

struct sockaddr {
	unsigned char sin_len;
	unsigned char sa_family;
	char sa_data[14];
};

typedef unsigned int socklen;
typedef void *ScePthread;
typedef void *ScePthreadAttr;

typedef int SceUserServiceUserId;

//kernel
#define DGB_CHANNEL_TTYL 0

extern int(*sceKernelDebugOutText)(int debugChannel, const char* text);
extern unsigned int (*sceKernelSleep)(unsigned int seconds);
extern int (*sceKernelUsleep)(unsigned int microseconds);
extern int (*sceKernelGetCpuTemperature)(int *);
extern int (*sceKernelGetSocSensorTemperature)(int, int *);
extern ssize_t (*read)(int fd, void *buf, size_t nbyte);
extern ssize_t (*write)(int fd, const void *buf, size_t count);
extern int (*open)(const char *path, int flags, int mode);
extern int (*close)(int fd);
extern int (*unlink)(const char *pathname);
extern int (*usleep)(unsigned int microseconds);

//threads
extern int (*scePthreadCreate)(ScePthread *thread, const ScePthreadAttr *attr, void *entry, void *arg, const char *name);
extern void (*scePthreadExit)(void *value);
extern int (*scePthreadDetach)(ScePthread thread);
extern int (*scePthreadJoin)(ScePthread thread, void **value_ptr);
extern int (*scePthreadGetprio)(ScePthread thread, int *prio);

//network
extern int (*sceNetSocket)(const char *, int, int, int);
extern int (*sceNetSocketClose)(int);
extern int (*sceNetConnect)(int, struct sockaddr *, int);
extern int (*sceNetSend)(int, const void *, size_t, int);

//sys
extern int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

//notifications
extern int (*sceSysUtilSendSystemNotificationWithText)(int messageType, const char *message);

//message dialogs
#define SCE_COMMON_DIALOG_MAGIC_NUMBER 0xC0D1A109

enum SceCommonDialogStatus {
	SCE_COMMON_DIALOG_STATUS_NONE = 0,
	SCE_COMMON_DIALOG_STATUS_INITIALIZED = 1,
	SCE_COMMON_DIALOG_STATUS_RUNNING = 2,
	SCE_COMMON_DIALOG_STATUS_FINISHED = 3
};

enum SceCommonDialogResult {
	SCE_COMMON_DIALOG_RESULT_OK = 0,
	SCE_COMMON_DIALOG_RESULT_USER_CANCELED = 1,
};

typedef struct SceCommonDialogBaseParam {
	size_t size;
	uint8_t reserved[36];
	uint32_t magic;
} SceCommonDialogBaseParam __attribute__((__aligned__(8)));

enum SceMsgDialogMode {
	SCE_MSG_DIALOG_MODE_USER_MSG = 1,
	SCE_MSG_DIALOG_MODE_PROGRESS_BAR = 2,
	SCE_MSG_DIALOG_MODE_SYSTEM_MSG = 3,
};

enum SceMsgDialogButtonType {
	SCE_MSG_DIALOG_BUTTON_TYPE_OK = 0,
	SCE_MSG_DIALOG_BUTTON_TYPE_YESNO = 1,
	SCE_MSG_DIALOG_BUTTON_TYPE_NONE = 2,
	SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL = 3,
	SCE_MSG_DIALOG_BUTTON_TYPE_WAIT = 5,
	SCE_MSG_DIALOG_BUTTON_TYPE_WAIT_CANCEL = 6,
	SCE_MSG_DIALOG_BUTTON_TYPE_YESNO_FOCUS_NO = 7,
	SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL_FOCUS_CANCEL = 8,
	SCE_MSG_DIALOG_BUTTON_TYPE_2BUTTONS = 9,
};

enum SceMsgDialogProgressBarType {
	SCE_MSG_DIALOG_PROGRESSBAR_TYPE_PERCENTAGE = 0,
	SCE_MSG_DIALOG_PROGRESSBAR_TYPE_PERCENTAGE_CANCEL = 1,
};

enum SceMsgDialogSystemMessageType {
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_EMPTY_STORE = 0,
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_PSN_CHAT_RESTRICTION = 1,
	SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_PSN_UGC_RESTRICTION = 2,
	SCE_MSG_DIALOG_SYSMSG_TYPE_CAMERA_NOT_CONNECTED = 4,
	SCE_MSG_DIALOG_SYSMSG_TYPE_WARNING_PROFILE_PICTURE_AND_NAME_NOT_SHARED = 5,
};

struct SceMsgDialogButtonsParam {
	const char *msg1;
	const char *msg2;
	char reserved[32];
};

struct SceMsgDialogUserMessageParam {
	SceMsgDialogButtonType buttonType;
	int : 32;
	const char *msg;
	SceMsgDialogButtonsParam *buttonsParam;
	char reserved[24];
};

struct SceMsgDialogProgressBarParam {
	SceMsgDialogProgressBarType barType;
	int : 32;
	const char *msg;
	char reserved[64];
};

struct SceMsgDialogSystemMessageParam {
	SceMsgDialogSystemMessageType sysMsgType;
	char reserved[32];
};

struct SceMsgDialogParam {
	SceCommonDialogBaseParam baseParam;
	size_t size;
	SceMsgDialogMode mode;
	int : 32;
	SceMsgDialogUserMessageParam *userMsgParam;
	SceMsgDialogProgressBarParam *progBarParam;
	SceMsgDialogSystemMessageParam *sysMsgParam;
	SceUserServiceUserId userId;
	char reserved[40];
	int : 32;
};

extern int (*sceCommonDialogInitialize)(void);
extern int (*sceMsgDialogInitialize)(void);
extern int (*sceMsgDialogOpen)(const SceMsgDialogParam *param);
extern SceCommonDialogStatus (*sceMsgDialogUpdateStatus)(void);
extern int (*sceMsgDialogTerminate)(void);

//ime dialogs
enum SceImeType {
	SCE_IME_TYPE_DEFAULT = 0,
	SCE_IME_TYPE_BASIC_LATIN = 1,
	SCE_IME_TYPE_URL = 2,
	SCE_IME_TYPE_MAIL = 3,
	SCE_IME_TYPE_NUMBER = 4,
};

enum SceImeEnterLabel {
	SCE_IME_ENTER_LABEL_DEFAULT = 0,
	SCE_IME_ENTER_LABEL_SEND = 1,
	SCE_IME_ENTER_LABEL_SEARCH = 2,
	SCE_IME_ENTER_LABEL_GO = 3,
};

enum SceImeInputMethod {
	SCE_IME_INPUT_METHOD_DEFAULT = 0,
};

typedef int (*SceImeTextFilter)(wchar_t *outText, uint32_t *outTextLength, const wchar_t *srcText, uint32_t srcTextLength);

enum SceImeVerticalAlignment {
	SCE_IME_VALIGN_TOP = 0,
	SCE_IME_VALIGN_CENTER = 1,
	SCE_IME_VALIGN_BOTTOM = 2,
};

enum SceImeHorizontalAlignment {
	SCE_IME_HALIGN_LEFT = 0,
	SCE_IME_HALIGN_CENTER = 1,
	SCE_IME_HALIGN_RIGHT = 2,
};

enum SceImeDialogStatus {
	SCE_IME_DIALOG_STATUS_NONE = 0,
	SCE_IME_DIALOG_STATUS_RUNNING = 1,
	SCE_IME_DIALOG_STATUS_FINISHED = 2,
};

enum SceImeDialogEndStatus {
	SCE_IME_DIALOG_END_STATUS_OK = 0,
	SCE_IME_DIALOG_END_STATUS_USER_CANCELED = 1,
	SCE_IME_DIALOG_END_STATUS_ABORTED = 2,
};

struct SceImeDialogResult {
	SceImeDialogEndStatus endstatus;
	int8_t reserved[12];
};

struct SceImeDialogParam {
	SceUserServiceUserId userId;
	SceImeType type;
	uint64_t supportedLanguages;
	SceImeEnterLabel enterLabel;
	SceImeInputMethod inputMethod;
	SceImeTextFilter filter;
	uint32_t option;
	uint32_t maxTextLength;
	wchar_t *inputTextBuffer;
	float posx;
	float posy;
	SceImeHorizontalAlignment horizontalAlignment;
	SceImeVerticalAlignment verticalAlignment;
	const wchar_t *placeholder;
	const wchar_t *title;
	int8_t reserved[16];
};

extern int (*sceImeDialogGetResult)(SceImeDialogResult *result);
extern int (*sceImeDialogInit)(const SceImeDialogParam *param, void *extended);
extern SceImeDialogStatus (*sceImeDialogGetStatus)(void);
extern int (*sceImeDialogTerm)(void);

//web dialogs
#define SCE_WEB_BROWSER_DIALOG_COOKIE_URL_SIZE (2048)
#define SCE_WEB_BROWSER_DIALOG_COOKIE_DATA_SIZE (4096)

struct SceWebBrowserDialogSetCookieParam {
	size_t size;
	const char *url;
	const char *cookie;
	char reserved[256];
};

enum SceWebBrowserDialogMode {
	SCE_WEB_BROWSER_DIALOG_MODE_DEFAULT = 1,
	SCE_WEB_BROWSER_DIALOG_MODE_CUSTOM = 2,
};

struct SceWebBrowserDialogWebViewParam {
	size_t size;
	uint32_t option;
	char reserved[256];
	int : 32;
};

typedef int SceWebBrowserCallbackParamType;
struct SceWebBrowserDialogCallbackInitParam {
	size_t size;
	SceWebBrowserCallbackParamType type;
	int : 32;
	const char *data;
	char reserved[32];
};

struct SceWebBrowserDialogImeParam {
	size_t size;
	uint32_t option;
	char reserved[256];
	int : 32;
};

struct SceWebBrowserDialogParam {
	SceCommonDialogBaseParam baseParam;
	size_t size;
	SceWebBrowserDialogMode mode;
	SceUserServiceUserId userId;
	const char *url;
	SceWebBrowserDialogCallbackInitParam *callbackInitParam;
	uint16_t width;
	uint16_t height;
	uint16_t positionX;
	uint16_t positionY;
	uint32_t parts;
	uint16_t headerWidth;
	uint16_t headerPositionX;
	uint16_t headerPositionY;
	short : 16;
	uint32_t control;
	SceWebBrowserDialogImeParam *imeParam;
	SceWebBrowserDialogWebViewParam *webviewParam;
	uint32_t animation;
	char reserved[202];
	short : 16;
};

extern int (*sceWebBrowserDialogInitialize)(void);
extern int (*sceWebBrowserDialogTerminate)(void);
extern int (*sceWebBrowserDialogOpen)(const SceWebBrowserDialogParam *param);
extern SceCommonDialogStatus (*sceWebBrowserDialogUpdateStatus)(void);
extern int (*sceWebBrowserDialogSetCookie)(const SceWebBrowserDialogSetCookieParam *param);

//user service
struct SceUserServiceLoginUserIdList {
	SceUserServiceUserId userId[4];
};

extern int (*sceUserServiceGetInitialUser)(SceUserServiceUserId *userId);
extern int (*sceUserServiceGetUserName)(const SceUserServiceUserId userId, char *userName, const size_t size);
extern int (*sceUserServiceGetLoginUserIdList)(SceUserServiceLoginUserIdList *userIdList);

//gamepad
#define SCE_PAD_MAX_TOUCH_NUM 2
#define SCE_PAD_MAX_DEVICE_UNIQUE_DATA_SIZE 12

#define SCE_PAD_MAX_X_COORDINATE 1919
#define SCE_PAD_MAX_Y_COORDINATE 941

typedef enum ScePadButtonDataOffset {
	SCE_PAD_BUTTON_L3 = 0x00000002,
	SCE_PAD_BUTTON_R3 = 0x00000004,
	SCE_PAD_BUTTON_OPTIONS = 0x00000008,
	SCE_PAD_BUTTON_UP = 0x00000010,
	SCE_PAD_BUTTON_RIGHT = 0x00000020,
	SCE_PAD_BUTTON_DOWN = 0x00000040,
	SCE_PAD_BUTTON_LEFT = 0x00000080,
	SCE_PAD_BUTTON_L2 = 0x00000100,
	SCE_PAD_BUTTON_R2 = 0x00000200,
	SCE_PAD_BUTTON_L1 = 0x00000400,
	SCE_PAD_BUTTON_R1 = 0x00000800,
	SCE_PAD_BUTTON_TRIANGLE = 0x00001000,
	SCE_PAD_BUTTON_CIRCLE = 0x00002000,
	SCE_PAD_BUTTON_CROSS = 0x00004000,
	SCE_PAD_BUTTON_SQUARE = 0x00008000,
	SCE_PAD_BUTTON_TOUCH_PAD = 0x00100000,
	SCE_PAD_BUTTON_INTERCEPTED = 0x80000000,
};

struct ScePadAnalogStick {
	uint8_t x;
	uint8_t y;
};

struct ScePadAnalogButtons {
	uint8_t l2;
	uint8_t r2;
	uint8_t padding[2];
};

struct SceFQuaternion {
	float x, y, z, w;
};

struct SceFVector3 {
	float x, y, z;
};

struct ScePadTouch {
	uint16_t x;
	uint16_t y;
	uint8_t id;
	uint8_t reserve[3];
};

struct ScePadTouchData {
	uint8_t touchNum;
	uint8_t reserve[3];
	uint32_t reserve1; //was uint8_t
	ScePadTouch touch[SCE_PAD_MAX_TOUCH_NUM];
};

struct ScePadExtensionUnitData {
	uint32_t extensionUnitId;
	uint8_t reserve[1];
	uint8_t dataLength;
	uint8_t data[10];
};

struct ScePadData {
	uint32_t buttons;
	ScePadAnalogStick leftStick;
	ScePadAnalogStick rightStick;
	ScePadAnalogButtons analogButtons;
	SceFQuaternion orientation;
	SceFVector3 acceleration;
	SceFVector3 angularVelocity;
	ScePadTouchData touchData;
	bool connected;
	uint64_t timestamp;
	ScePadExtensionUnitData extensionUnitData;
	uint8_t connectedCount;
	uint8_t reserve[2];
	uint8_t deviceUniqueDataLen;
	uint8_t deviceUniqueData[SCE_PAD_MAX_DEVICE_UNIQUE_DATA_SIZE];
};

typedef struct ScePadOpenParam {
	uint8_t reserve[8];
};

typedef struct ScePadLightBarParam {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t reserve[1];
};

extern int (*scePadOpen)(SceUserServiceUserId userId, int32_t type, int32_t index, const ScePadOpenParam *pParam);
extern int (*scePadGetHandle)(SceUserServiceUserId userId, int32_t type, int32_t index);
extern int (*scePadSetLightBar)(int32_t handle, const ScePadLightBarParam *pParam);
extern int (*scePadReadState)(int32_t handle, ScePadData *pData);

//libc
extern void *(*malloc)(size_t size);
extern void (*free)(void *ptr);
extern void *(*calloc)(size_t num, size_t size);
extern void *(*realloc)(void *ptr, size_t size);
extern void *(*memset)(void *destination, int value, size_t num);
extern void *(*memcpy)(void *destination, const void *source, size_t num);
extern int (*memcmp)(const void *s1, const void *s2, size_t n);
extern void *(*memmove)(void *str1, const void *str2, size_t n);
extern size_t (*mbstowcs)(wchar_t *dest, const char *src, size_t max);
extern size_t (*wcstombs)(char *dest, const wchar_t *src, size_t max);
extern char *(*strcpy)(char *destination, const char *source);
extern char *(*strncpy)(char *destination, const char *source, size_t num);
extern char *(*strcat)(char *dest, const char *src);
extern char *(*strncat)(char *dest, const char *src, size_t n);
extern size_t (*strlen)(const char *s);
extern char *(*strtok)(char *str, const char *delimiters);
extern int (*strcmp)(const char *s1, const char *s2);
extern int (*strncmp)(const char *s1, const char *s2, size_t n);
extern int (*sprintf)(char *str, const char *format, ...);
extern int (*snprintf)(char *str, size_t size, const char *format, ...);
extern int (*vsprintf)(char *s, const char *format, va_list arg);
extern int (*sscanf)(const char *str, const char *format, ...);
extern char *(*strchr)(const char *s, int c);
extern char *(*strrchr)(const char *s, int c);
extern char *(*strstr)(char *str1, char *str2);
extern int (*atoi)(const char *str);
extern double (*atof)(const char *str);
extern double (*sin)(double x);
extern float (*sinf)(float x);
extern double (*cos)(double x);
extern float (*cosf)(float x);
extern double (*tan)(double x);
extern float (*tanf)(float x);
extern double (*atan)(double x);
extern double (*atan2)(double x, double y);
extern double (*sqrt)(double vec);
extern float (*sqrtf)(float vec);
extern double (*pow)(double x, double y);
extern int (*abs)(int n);
extern double (*fmin)(double x, double y);
extern double (*fmax)(double x, double y);
extern int(*isspace)(int c);
extern int(*isupper)(int c);
extern int(*islower)(int c);
extern int(*toupper)(int c);
extern int(*tolower)(int c);

#define O_RDONLY	0x0000
#define O_WRONLY	0x0001
#define O_RDWR		0x0002
#define O_ACCMODE	0x0003
#define O_NONBLOCK	0x0004	// no delay
#define O_APPEND	0x0008	// set append mode
#define O_CREAT		0x0200	// create if nonexistent
#define O_TRUNC		0x0400	// truncate to zero length
#define O_EXCL		0x0800	// error if already exists

int getpid();
void *sys_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
void *sys_munmap(void *addr, size_t len);
int sys_dynlib_dlsym(int loadedModuleID, const char *name, void *destination);
int sys_dynlib_load_prx(const char *name, int *idDestination);
int sys_dynlib_unload_prx(int id);

void initImports();

inline void *operator new(size_t size) { return malloc(size); }
inline void *operator new[](size_t size) { return malloc(size); }
inline void operator delete(void *ptr) { free(ptr); }
inline void operator delete[](void *ptr) { free(ptr); }
