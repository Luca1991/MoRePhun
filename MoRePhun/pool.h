#pragma once

#pragma pack(push, 1)
struct PoolItem {
	unsigned segment_1 : 4;
	unsigned segment_0 : 4;
	unsigned segmentoffset : 24;
	uint32_t extra;	
};
#pragma pack(pop)
static_assert(sizeof(PoolItem) == 8, "Abnormal PoolItem element");

struct PoolData {
	bool isSyscall = false;
	uint32_t value;
	std::function<void()> fun;
};