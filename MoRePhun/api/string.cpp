#include "../mophun_os.h"
#include "../registers.h"

void MophunOS::vStrCpy()
{
	char* str1 = reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p0)));
	const char* str2 = reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p1)));

	if (str1 == nullptr)
		return;

	while (*str2 != '\0')
	{
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
	// FIXME return str2 in r0
}