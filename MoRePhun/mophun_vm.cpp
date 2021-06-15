#include "mophun_vm.h"
#include "registers.h"


MophunVM::MophunVM()
{
	memory.ram.resize(RAM_SIZE);
	registers = { {zero, 0}, {sp, memory.ram.size()-1}, {ra, 0}, {fp, 0},
	{s0, 0}, {s1, 0}, {s2, 0}, {s3, 0}, {s4, 0},{s5, 0},{s6, 0}, {s7, 0},
	{p0, 0}, {p1, 0}, {p2, 0}, {p3, 0},
	{g0, 0}, {g1, 0}, {g2, 0}, {g3, 0}, {g4, 0}, {g5, 0}, {g6, 0},
	{g7, 0}, {g8, 0}, {g9, 0}, {g10, 0}, {g11, 0}, {g12, 0}, {g13, 0},
	{r0, 0}, {r1, 0},
	{pc, sizeof(VMGPHeader)} };
}

MophunVM::~MophunVM()
{

}

uint32_t MophunVM::readReg(uint32_t reg)
{
	return registers[reg];
}

void MophunVM::writeReg(uint32_t reg, uint32_t val)
{
	registers[reg] = val;
}

uint8_t MophunVM::readRam(uint32_t offset)
{
	return memory.ram[offset];
}

uint8_t* MophunVM::getRamAddress(uint32_t offset)
{
	return std::addressof(memory.ram[offset]);
}

std::vector<PoolData>* MophunVM::getPoolEntries()
{
	return std::addressof(poolDataList);
}