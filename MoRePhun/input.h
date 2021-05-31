#pragma once
#include <SDL.h>

#define KEYUP			0
#define KEYDOWN			1
#define KEYLEFT			2
#define KEYRIGHT		3
#define KEYFIRE			4
#define KEYFIRE2		5
#define KEYSELECT		6
#define POINTERDOWN		7
#define POINTERALTDOWN	8


class Input {
public:
	Input();
	~Input();
	uint32_t keys[9];
};