#pragma once
#include <cstdint>
#include <vector>
#include "graphics.h"
#include "stream_io.h"

struct OSData {
	uint8_t currentFgColor[3];
	int64_t timer;
	std::vector<SpriteSlot> spriteSlots;
	VMGPFONT* currentFont;
	VMGPFONT* previousFont;
	std::unordered_map<uint32_t, StreamSlot> streamSlots;
	uint32_t streamCounter;
};