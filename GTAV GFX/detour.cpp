#include "detour.h"
#include "imports.h"
#include "utility.h"

void LockJump(uint64_t address) {
	*(uint8_t*)(address) = 0xE9;
	*(uint8_t*)(address + 1) = 0xFB;
	*(uint8_t*)(address + 2) = 0xFF;
	*(uint8_t*)(address + 3) = 0xFF;
	*(uint8_t*)(address + 4) = 0xFF;
}

void PatchInJump(uint64_t address, void* destination) {
	if (!address || !destination)
		return;

	*(uint8_t*)(address) = 0xFF;
	*(uint8_t*)(address + 1) = 0x25;
	*(uint8_t*)(address + 2) = 0x00;
	*(uint8_t*)(address + 3) = 0x00;
	*(uint8_t*)(address + 4) = 0x00;
	*(uint8_t*)(address + 5) = 0x00;
	*(uint64_t*)(address + 6) = (uint64_t)destination;
}

void* DetourFunction(uint64_t address, void* destination, int length) {
	if (!address || !destination)
		return 0;

	if (length < HOOK_LENGTH)
		return 0;

	int stubLength = length + HOOK_LENGTH;
	void* stubAddress = (void*)sys_mmap(0, stubLength, 1 | 2 | 4, 0x1000 | 0x2, -1, 0);

	ReadMemory((uint64_t)address, stubAddress, length);
	PatchInJump((uint64_t)stubAddress + length, (void*)(address + length));
	PatchInJump(address, destination);

	return stubAddress;
}
