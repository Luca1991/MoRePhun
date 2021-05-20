#pragma once
#include <cstdint>

struct GenericFormat {
    unsigned opcode: 8, dest: 8, source: 8, extra: 8;
};

struct WordFormat {
    unsigned opcode : 8, dest : 8, word : 16;
};

union PIPInstruction {
    GenericFormat gen;
    WordFormat word;
};

static_assert(sizeof(uint32_t) == sizeof(PIPInstruction), "Invalid instruction lenght");

inline int decodeImmediate(uint32_t val) { return (val & 0x7fffffff) | ((val << 1) & 0x80000000); }