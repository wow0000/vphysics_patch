#include "pch.h"
#include "MemoryTools.h"

size_t	MemoryTools::FindPattern(const std::string &pattern, std::string module_name) {
	MODULEINFO		miModInfo{};
	const char*		pat = pattern.c_str();
	HMODULE			mod = GetModuleHandleA(module_name.c_str());
	size_t			rangeStart;
	size_t			rangeEnd;
	size_t			pat_len;
	unsigned char*	ptr;

	if (mod == 0)
		return 0;
	GetModuleInformation(GetCurrentProcess(), mod, &miModInfo, sizeof(MODULEINFO));
	if (miModInfo.SizeOfImage == 0)
		return 0;
	rangeStart = (size_t)miModInfo.lpBaseOfDll;
	rangeEnd = rangeStart + miModInfo.SizeOfImage;
	pat_len = pattern.length();
	ptr = (unsigned char*)rangeStart;
	for (size_t i = 0; i < (rangeEnd - rangeStart); i++) {
		size_t found = 0;
		size_t increment = 0;
		while (found < pat_len && pat[found])
		{
			if ((ptr + i)[increment] == getByte((pat + found)) || pat[found] == '?')
			{
				if (pat[found] == '?')
					found += 2;
				else
					found += 3;
				increment++;
			}
			else
				break;
		}
		if (found >= pat_len)
			return (size_t)(ptr + i);
	}
	return 0;
}
