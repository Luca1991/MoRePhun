#pragma once

#include "mophun_vm.h"
#include "api/os_data.h"
#include "video.h"
#include "input.h"

class MophunOS {

	public:
		MophunOS();
		~MophunOS();
		bool loadRom();
		void emulate();

	private:
		MophunVM* mophunVM = new MophunVM();
		Video* video = new Video();
		Input* input = new Input();
		OSData osdata;
		void apiHandler(const std::string& api);
		bool status;

		// Debug api
		void DbgPrintf(const std::string& str);
		std::string getStringFromMemory(uint32_t addr);

		// System api
		uint32_t vGetRandom();
		void vTerminateVMGP();

		// String api
		const char* vStrCpy(char* s1, const char* s2);

		// Graphics api
		void vClearScreen(uint32_t color);
		void vFlipScreen(uint32_t block);
		void vSetForeColor(uint32_t color);
		uint32_t vSpriteInit(uint8_t count);
		void vSpriteClear();
		void vSpriteSet(uint8_t slot, SPRITE* sprite, int16_t x, int16_t y);
		void vUpdateSprite();

		// Input api
		uint32_t vGetButtonData();

		// Time/data api
		uint32_t vGetTickCount();
};
