#pragma once

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include "vmgp_header.h"
#include "memory.h"
#include "video.h"
#include "pool.h"

class MophunVM {

	public:
		MophunVM();
		bool loadRom(std::string romPath);
		void emulate();
		bool status;
	private:
		VMGPHeader* pRomHeader;
		Memory memory;
		Video* video = new Video();
		std::unordered_map<unsigned char, uint32_t> registers;
		PoolData poolItemHandler(uint32_t index);		
		void apiHandler(const std::string& api);


		void mPrint(const std::string& str); // this function need to be moved from MophunVM class
		std::string getStringFromMemory(uint32_t addr); // this function need to be moved from MophunVM class
};
