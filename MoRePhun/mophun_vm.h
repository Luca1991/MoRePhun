#pragma once

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <thread>
#include "vmgp_header.h"
#include "memory.h"
#include "pool.h"


class MophunVM {

	public:
		MophunVM();
		~MophunVM();
		bool loadRom(const std::string& romPath);
		void emulate();
		uint32_t readReg(uint32_t reg);
		void writeReg(uint32_t reg, uint32_t val);
		uint8_t readRam(uint32_t offset);
		uint8_t* getRamAddress(uint32_t offset);
		std::vector<PoolData>* getPoolEntries();
	private:
		VMGPHeader* pRomHeader;
		Memory memory;
		std::unordered_map<unsigned char, uint32_t> registers;
		std::vector<PoolData> poolDataList;
		void poolParser();
		PoolData decodePoolItem(uint32_t index);
};
