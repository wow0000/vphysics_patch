#pragma once

#include <string>

#define INRANGE(x, a, b)	(x >= a && x <= b)
#define getBits(x)			(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte(x)			(getBits(x[0]) << 4 | getBits(x[1]))

namespace MemoryTools
{
	size_t FindPattern(const std::string& pattern, std::string module_name);
}
