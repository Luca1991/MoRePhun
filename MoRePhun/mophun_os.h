#pragma once

#include "mophun_vm.h"
#include "api\os_data.h"
#include "video.h"

class MophunOS {

	public:
		MophunOS();
		~MophunOS();
		bool loadRom();
		void emulate();

	private:
		MophunVM* mophunVM = new MophunVM();
		Video* video = new Video();
		OSData osdata;
		void apiHandler(const std::string& api);
		bool status;

		// Debug api
		void DbgPrintf(const std::string& str);
		std::string getStringFromMemory(uint32_t addr);

		// System api
		uint32_t vGetRandom();
		void vTerminateVMGP();

		// Graphics api
		void vClearScreen(uint32_t color);
		void vFlipScreen(uint32_t block);
		void vSetForeColor(uint32_t color);

		// Time/data api
		uint32_t vGetTickCount();
};
