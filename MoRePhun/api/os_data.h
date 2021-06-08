#pragma once
#include <cstdint>
#include <vector>
#include "graphics.h"

struct OSData {
	uint8_t currentFgColor[3];
	int64_t timer;
	std::vector<SpriteSlot> spriteSlots;
	VMGPFONT* currentFont;
	VMGPFONT* previousFont;
};