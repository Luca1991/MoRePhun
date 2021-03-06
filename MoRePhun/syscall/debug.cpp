#include "../mophun_os.h"
#include "../registers.h"
#include <sstream>

void MophunOS::DbgPrintf()
{
	if (mophunVM->readReg(sp) == RAM_SIZE) // FIXME THI IS WRONG!!
		return;
	const std::string& str = reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p0)));
	std::stringstream ss;
	uint32_t stackTmpPnt = mophunVM->readReg(sp);
	for (int i = 0; i < str.size();)
	{
		if (str[i] == '%')
		{
			i++;
			if (i >= str.size())
				break;
			switch (str[i])
			{
			case 's':
				ss << getStringFromMemory(stackTmpPnt);
				stackTmpPnt += sizeof(uint32_t);
				break;
			case '%':
				ss << '%';
				break;
			case 'd':
				ss << *reinterpret_cast<int32_t*>(mophunVM->getRamAddress(stackTmpPnt));
				stackTmpPnt += sizeof(uint32_t);
				break;
			case 'l':
			case 'f':
			{
				ss << (*reinterpret_cast<double*>(mophunVM->getRamAddress(stackTmpPnt)));
				stackTmpPnt += sizeof(uint64_t);
				break;
			}
			default:
				ss << "%" << str[i];
				break;
			}
			i++;
		}
		else
		{
			ss << str[i];
			i++;
		}
	}

	std::cout << ss.str() << std::endl;
}

std::string MophunOS::getStringFromMemory(uint32_t addr)
{
	uint32_t ref = *reinterpret_cast<uint32_t*>(mophunVM->getRamAddress(addr));
	return reinterpret_cast<char*>(mophunVM->getRamAddress(ref));
}