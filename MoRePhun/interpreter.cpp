#include "interpreter.h"
#include "mophun_vm.h"
#include "registers.h"
#include "opcodes.h"


void MophunVM::emulate()
{
	auto instruction = *reinterpret_cast<PIPInstruction*>(std::addressof(memory.ram[registers[pc]]));

	switch (instruction.gen.opcode)
	{
	case NOP: // 0x01
		registers[pc] += sizeof(uint32_t);
		break;
	case ADD: // 0x02
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] + registers[instruction.gen.extra];
		break;
	case AND: // 0x03
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] & registers[instruction.gen.extra];
		break;
	case MUL: // 0x04
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] * registers[instruction.gen.extra];
		break;
	case NEG: // 0x0E
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = -(registers[instruction.gen.source]);
		break;
	case MOV: // 0x11
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source];
		break;
	case SLLi: // 0x1C
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] << instruction.gen.extra;
		break;
	case SRAi: // 0x1D
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = static_cast<int32_t>(registers[instruction.gen.source]) >> instruction.gen.extra;
		break;
	case SRLi: // 0x1E 
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] >> instruction.gen.extra;
		break;
	case ADDQ: // 0x1F
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] + static_cast<int8_t>(instruction.gen.extra);
		break;
	case MULQ: // 0x20
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] * static_cast<int8_t>(instruction.gen.extra);
		break;
	case ORBi: // 0x23
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = registers[instruction.gen.source] | static_cast<int8_t>(instruction.gen.extra);
		break;
	case BGEI: // 0x2E
		if (static_cast<int32_t>(registers[instruction.gen.dest]) >= static_cast<int8_t>((instruction.gen.source)))
			registers[pc] += instruction.gen.extra * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case BEQI: // 0x2C
		if (static_cast<int32_t>(registers[instruction.gen.dest]) == static_cast<int8_t>((instruction.gen.source)))
			registers[pc] += instruction.gen.extra * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case BGTI: // 0x30
		if (static_cast<int32_t>(registers[instruction.gen.dest]) > static_cast<int8_t>((instruction.gen.source)))
			registers[pc] += instruction.gen.extra * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case BLEI: // 0x32 
		if (static_cast<int32_t>(registers[instruction.gen.dest]) <= static_cast<int8_t>((instruction.gen.source)))
			registers[pc] += instruction.gen.extra * sizeof(uint32_t);
		else
			registers[pc] += sizeof(uint32_t);
		break;
	case LDQ: // 0x40
		registers[pc] += sizeof(uint32_t);
		registers[instruction.gen.dest] = static_cast<int16_t>(instruction.word.word);
		break;
	case JPr: // 0x41
		registers[pc] = registers[instruction.gen.dest];
		break;
	case STORE: // 0x43
	{
		uint32_t regStart = instruction.gen.dest;
		uint32_t regEnd = regStart + (instruction.gen.source);
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
		uint32_t regStart = instruction.gen.dest;
		uint32_t regEnd = regStart - (instruction.gen.source);
		for (uint32_t r = regStart; r > regEnd; r -= sizeof(uint32_t))
		{
			registers[r] = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[sp]]));
			registers[sp] += sizeof(uint32_t);
		}
		registers[pc] = registers[ra];
		break;
	}
	case SLEEP: // 0x47
		registers[pc] += sizeof(uint32_t);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		break;
	case ANDi: // 0x4B
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t andType = (val & 0xFF000000) >> 24;
		if (andType != 0x00)
		{ // ANDi immediate 32bit
			registers[instruction.gen.dest] = registers[instruction.gen.source] & static_cast<int32_t>(decodeImmediate(val));
		}
		else
		{ // ANDi from pool item
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR ANDi: unhandled case" << std::endl;
		}
		break;
	}
	case MULi: // 0x4C
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t mulType = (val & 0xFF000000) >> 24;
		if (mulType != 0x00)
		{
			registers[instruction.gen.dest] = registers[instruction.gen.source] * static_cast<int32_t>(decodeImmediate(val));
		}
		else
		{
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR MULi: unhandled case" << std::endl;
		}
		break;
	}
	case DIVi: // 0x4D
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t divType = (val & 0xFF000000) >> 24;
		if (divType != 0x00)
		{
			registers[instruction.gen.dest] = static_cast<int32_t>(registers[instruction.gen.source]) / static_cast<int32_t>(decodeImmediate(val));
		}
		else {
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR DIVi: unhandled case" << std::endl;
		}
		break;
	}
	case STWd: // 0x54
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t stwType = (val & 0xFF000000) >> 24;
		if (stwType != 0x00)
		{	// STW immediate
			*reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[instruction.gen.source] + decodeImmediate(val)])) = registers[instruction.gen.dest];
		}
		else
		{ // STW from pool item
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR STWd: unhandled case" << std::endl;
		}
		break;
	}
	case LDWd: // 0x57
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] += sizeof(uint32_t);
		uint8_t ldwType = (val & 0xFF000000) >> 24;
		if (ldwType != 0x00)
		{	// LDW immediate
			registers[instruction.gen.dest] = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[instruction.gen.source] + decodeImmediate(val)]));
		}
		else
		{ // LDW from pool item
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR LDWd: unhandled case" << std::endl;
		}
		break;
	}
	case JPl: // 0x5B
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		registers[pc] -= sizeof(uint32_t);
		uint8_t jpType = (val & 0xFF000000) >> 24;
		if (jpType != 0x00)
		{	// JPl immediate
			registers[pc] += static_cast<int32_t>(decodeImmediate(val));
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
		if (ldiType != 0x00)
		{ // LDI immediate 32bit
			registers[instruction.gen.dest] = decodeImmediate(val);
		}
		else
		{ // LDI from pool item
			auto decodedPoolItem = poolItemHandler(val);
			registers[instruction.gen.dest] = decodedPoolItem.value;
		}
		registers[pc] += sizeof(uint32_t);
		break;
	}
	case BGTU: // 0x62
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		uint8_t bgtuType = (val & 0xFF000000) >> 24;
		if (bgtuType != 0x00)
		{
			if (registers[instruction.gen.dest] > registers[instruction.gen.source]) {
				registers[pc] += decodeImmediate(val) - sizeof(uint32_t);
			}
			else
			{
				registers[pc] += sizeof(uint32_t);
			}
		}
		else
		{
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR BGTU: unhandled case" << std::endl;
			registers[pc] += sizeof(uint32_t);
		}
		break;
	}
	case BLTU: // 0x66
	{
		registers[pc] += sizeof(uint32_t);
		auto val = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[registers[pc]]));
		uint8_t bltuType = (val & 0xFF000000) >> 24;
		if (bltuType != 0x00)
		{
			if (registers[instruction.gen.dest] < registers[instruction.gen.source])
			{
				registers[pc] += decodeImmediate(val) - sizeof(uint32_t);
			}
			else
			{
				registers[pc] += sizeof(uint32_t);
			}
		}
		else
		{
			// FIXME TODO -> check if this is possile
			std::cout << "ERROR BLTU: unhandled case" << std::endl;
			registers[pc] += sizeof(uint32_t);
		}
		break;
	}
	default:
		std::cout << "unknown opcode: " << std::hex << instruction.gen.opcode << " at PC: " << registers[pc] << std::endl;
		registers[pc] += sizeof(uint32_t);
		break;
	}
}