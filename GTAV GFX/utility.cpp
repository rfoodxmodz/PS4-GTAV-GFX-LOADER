#include "utility.h"
#include "imports.h"
#include "kernel.h"

void Sleep(unsigned int milliseconds) {
	sceKernelUsleep(milliseconds * 1000);
}

void WriteJump(uint64_t address, uint64_t destination) {
	*(uint8_t *)(address) = 0xFF;
	*(uint8_t *)(address + 1) = 0x25;
	*(uint8_t *)(address + 2) = 0x00;
	*(uint8_t *)(address + 3) = 0x00;
	*(uint8_t *)(address + 4) = 0x00;
	*(uint8_t *)(address + 5) = 0x00;
	*(uint64_t *)(address + 6) = destination;
}

void ReadMemory(uint64_t address, void *buffer, int length) {
	memcpy(buffer, (void *)address, length);
}

void WriteMemory(uint64_t address, void *buffer, int length) {
	memcpy((void *)address, buffer, length);
}

void NOP(uint64_t address, size_t length) {
	unsigned char *nop_buffer = new unsigned char[length];
	memset(nop_buffer, 0x90, length);

	WriteMemory(address, nop_buffer, length);

	delete[] nop_buffer;
}

void uartprintf(const char *fmt, ...) {
	char buffer[512];
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	sceKernelDebugOutText(DGB_CHANNEL_TTYL, buffer);
}

void Notify(const char *fmt, ...) {
	char buffer[512];

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	sceSysUtilSendSystemNotificationWithText(222, buffer);
}

void CreateThread(void *entry, const char *name) {
	ScePthread thread;
	scePthreadCreate(&thread, NULL, (void *)entry, NULL, name);
}
