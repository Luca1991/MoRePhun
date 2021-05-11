#include "mophun_vm.h"
#include "registers.h"
#include "opcodes.h"

void MophunVM::emulate()
{
	auto opcode = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
	switch (opcode & 0x000000FF)
	{
	case NOP: // 0x01
		registers[pc] += sizeof(uint32_t);
		break;
	case ADD: // 0x02
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] + registers[(opcode & 0xFF000000) >> 24];
		break;
	case AND: // 0x03
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] & registers[(opcode & 0xFF000000) >> 24];
		break;
	case MUL: // 0x04
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] * registers[(opcode & 0xFF000000) >> 24];
		break;
	case NEG: // 0x0E
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = -(registers[(opcode & 0x00FF0000) >> 16]);
		break;
	case MOV: // 0x11
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16];
		break;
	case SLLi: // 0x1C
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] << ((opcode & 0xFF000000) >> 24);
		break;
	case ADDQ: // 0x1F
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] + static_cast<int8_t>((opcode & 0xFF000000) >> 24);
		break;
	case MULQ: // 0x20
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] * static_cast<int8_t>((opcode & 0xFF000000) >> 24);
		break;
	case ORBi:
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] | static_cast<int8_t>((opcode & 0xFF000000) >> 24);
		break;
	case BGEI: // 0x2E
		if (static_cast<int32_t>(registers[(opcode & 0x0000FF00) >> 8]) >= static_cast<int8_t>(((opcode & 0x00FF0000) >> 16)))
			registers[pc] += ((opcode & 0xFF000000) >> 24) * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case BEQI: // 0x2C
		if (static_cast<int32_t>(registers[(opcode & 0x0000FF00) >> 8]) == static_cast<int8_t>(((opcode & 0x00FF0000) >> 16)))
			registers[pc] += ((opcode & 0xFF000000) >> 24) * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case BGTI: // 0x30
		if (static_cast<int32_t>(registers[(opcode & 0x0000FF00) >> 8]) > static_cast<int8_t>(((opcode & 0x00FF0000) >> 16)))
			registers[pc] += ((opcode & 0xFF000000) >> 24) * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case BLEI: // 0x32 
		if (static_cast<int32_t>(registers[(opcode & 0x0000FF00) >> 8]) <= static_cast<int8_t>(((opcode & 0x00FF0000) >> 16)))
			registers[pc] += ((opcode & 0xFF000000) >> 24)*sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case LDQ: // 0x40
		registers[pc] += sizeof(uint32_t);
		registers[(opcode & 0x0000FF00) >> 8] = static_cast<int16_t>((opcode & 0xFFFF0000) >> 16);
		break;
	case JPr: // 0x41
		registers[pc] = registers[(opcode & 0xFFFFFF00) >> 8];
		break;
	case STORE: // 0x43
	{
		uint32_t regStart = (opcode & 0x0000FF00) >> 8;
		uint32_t regEnd = regStart + ((opcode & 0x00FF0000) >> 16);
		for (uint32_t r = regStart; r < regEnd; r+=sizeof(uint32_t))
		{
			registers[sp] -= sizeof(uint32_t);
			*reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[sp]])) = registers[r];
		}
		registers[pc] += sizeof(uint32_t);
		break;
	}
	case RET: // 0x45
	{
		uint32_t regStart = (opcode & 0x0000FF00) >> 8;
		uint32_t regEnd = regStart - ((opcode & 0x00FF0000) >> 16);
		for (uint32_t r = regStart; r > regEnd; r -= sizeof(uint32_t))
		{
			registers[r] = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[sp]]));
			registers[sp] += sizeof(uint32_t);
		}
		registers[pc] = registers[ra];
		break;
	}
	case ANDi: // 0x4B
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t andType = (val & 0xFF000000) >> 24;
		if (andType == 0x80)
		{ // ANDi immediate 24bit
			registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] & static_cast<int32_t>(val & 0x00FFFFFF);
		}
		else if (andType == 0xFF)
		{ // ANDi immediate 32bit
			registers[(opcode & 0x0000FF00) >> 8] = registers[(opcode & 0x00FF0000) >> 16] & static_cast<int32_t>(val);
		}
		else
		{ // ANDi from pool item
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR ANDi: unhandled case" << std::endl;
		}
		break;
	}
	case STWd: // 0x54
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t stwType = (val & 0xFF000000) >> 24;
		if (stwType == 0x80)
		{	// STW immediate
			*reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[(opcode & 0x00FF0000) >> 16] + (val & 0x00FFFFFF)])) = registers[(opcode & 0x0000FF00) >> 8];
		}
		else
		{ // STW from pool item
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR STWd: unhandled case" << std::endl;
		}
		break;
	}
	case JPl:
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] -= sizeof(uint32_t);
		uint8_t jpType = (val & 0xFF000000) >> 24;
		if (jpType == 0xFF)
		{	// JPl immediate
			registers[pc] += static_cast<int32_t>(val);
		}
		else
		{
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR JPl: unhandled case" << std::endl;
		}
		break;
	}
	case CALLl: // 0x5C
	{
		registers[pc] += sizeof(uint32_t);
		auto decodedPoolItem = poolItemHandler(*reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]])));
		registers[pc] += sizeof(uint32_t);
		
		if (!decodedPoolItem.isSyscall)
		{
			registers[ra] = registers[pc];
			registers[pc] = decodedPoolItem.value;
		}
		else
		{
			std::string api = reinterpret_cast<char*>(std::addressof(memory.ram[decodedPoolItem.value]));
			apiHandler(api);
		}
		break;
	}
	case LDI: // 0x5A
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		uint8_t ldiType = (val & 0xFF000000) >> 24;
		if (ldiType == 0x80)
		{ // LDI immediate 24bit
			registers[(opcode & 0x0000FF00) >> 8] = val & 0x00FFFFFF;
		}
		else if (ldiType == 0xFF)
		{ // LDI immediate 32bit
			registers[(opcode & 0x0000FF00) >> 8] = val;
		}
		else
		{ // LDI from pool item
			auto decodedPoolItem = poolItemHandler(val);
			registers[(opcode & 0x0000FF00) >> 8] = decodedPoolItem.value;
		}
		registers[pc] += sizeof(uint32_t);
		break;
	}
	default:
		std::cout << "unknown opcode: " << std::hex << opcode << " at PC: " << registers[pc] << std::endl;
		registers[pc] += sizeof(uint32_t);
		break;
	}

}