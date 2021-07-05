#pragma once

#include "mophun_vm.h"
#include "syscall/os_data.h"
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
		bool status;
		void setupSyscalls();

		std::unordered_map<std::string, std::function<void()>> syscalls;

		// Debug api
		void DbgPrintf();
		std::string getStringFromMemory(uint32_t addr);

		// Graphics api
		void vClearScreen();
		void vFlipScreen();
		void vSetForeColor();
		void vSpriteInit();
		void vSpriteClear();
		void vSpriteSet();
		void vUpdateSprite();
		void vSetActiveFont();
		void vPrint();

		// System api
		void vGetRandom();
		void vTerminateVMGP();

		// Stream IO api
		void vStreamClose();
		void vStreamOpen();
		void vStreamRead();
		void vStreamWrite();

		// String api
		void vStrCpy();

		// Tileamp and Sprite api
		void vSpriteCollision();

		// Input api
		void vGetButtonData();

		// Time/data api
		void vGetTickCount();
};
