#include "mophun_vm.h"
#include <string>

PoolData MophunVM::poolItemHandler(uint32_t index)
{
	const auto& poolItem = reinterpret_cast<PoolItem*>(memory.ram.data() + memory.poolSegStartAddr)[index - 1];
	PoolData poolData;
	switch (poolItem.segment_0)
	{
	case 0:		// string segment
		poolData.isSyscall = true;
		poolData.isPointer = true;
		poolData.value = memory.stringSegStartAddr + poolItem.segmentoffset;
		break;
	case 1:		// code segment
		poolData.value = memory.codeSegStartAddr + poolItem.extra;
		break;
	case 2:		// data segment
		poolData.isPointer = true;
		poolData.value = memory.dataSegStartAddr + poolItem.extra;
		break;
	case 4:
		poolData.isPointer = true;
		poolData.value = memory.bssSegStartAddr + poolItem.extra;
		break;
	case 6:		// immediate float
		poolData.value = poolItem.extra;
		break;
	default:
		throw std::runtime_error("!!! Pool handler error: " + std::to_string(poolItem.segment_0));
		break;
	}
	return poolData;
}