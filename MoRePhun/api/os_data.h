#pragma once
#include <cstdint>
#include <vector>
#include "graphics.h"

struct OSData {
	uint32_t currentFgColor;
	int64_t timer;
	std::vector<SpriteSlot> spriteSlots;
};