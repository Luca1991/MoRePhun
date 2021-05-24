#include "../mophun_os.h"

const char* MophunOS::vStrCpy(char* s1, const char* s2)
{
	if (s1 == nullptr)
		return nullptr;

	while (*s2 != '\0')
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return s2;
}