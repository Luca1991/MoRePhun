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

typedef std::function<void(const std::string& api)> ApiCallback;

class MophunVM {

	public:
		MophunVM();
		~MophunVM();
		bool loadRom(const std::string& romPath);
		void setApiCallback(const ApiCallback& apiHandler);
		void emulate();
		uint32_t readReg(uint32_t reg);
		void writeReg(uint32_t reg, uint32_t val);
		uint32_t readRam(uint32_t offset);
		uint8_t* getRamAddress(uint32_t offset);
	private:
		VMGPHeader* pRomHeader;
		Memory memory;
		ApiCallback apiHandler;
		std::unordered_map<unsigned char, uint32_t> registers;
		PoolData poolItemHandler(uint32_t index);		
};
