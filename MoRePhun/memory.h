#pragma once

#include <vector>
#include <cstdint>

#define RAM_SIZE 16 * 1024 * 1024  // 16MB of memory

struct Memory {
	uint32_t codeSegStartAddr;
	uint32_t dataSegStartAddr;
	uint32_t bssSegStartAddr;
	uint32_t resSegStartAddr;
	uint32_t poolSegStartAddr;
	uint32_t stringSegStartAddr;
	uint32_t heapStartAddr;
	uint32_t stackStartAddr;
	std::vector<uint8_t> ram;
};