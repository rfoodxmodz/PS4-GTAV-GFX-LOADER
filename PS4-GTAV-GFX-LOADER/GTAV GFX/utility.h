#pragma once

#include "types.h"

typedef int (*_printf_t)(const char *fmt, ...);

void Sleep(unsigned int milliseconds);
void WriteJump(uint64_t address, uint64_t destination);
void ReadMemory(uint64_t address, void *buffer, int length);
void WriteMemory(uint64_t address, void *buffer, int length);
void NOP(uint64_t address, size_t length);
void uartprintf(const char *fmt, ...);
void Notify(const char *fmt, ...);
void CreateThread(void *entry, const char *name);
