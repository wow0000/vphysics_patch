#pragma once

#include "MemoryTools.h"
#include <detours.h>

#define SIG_check_element "55 8B EC 83 EC 0C 53 56 8B F1 8B 4D 08 8B 41 0C 6B C0 4B 33 41 08 57 8B F8 C1 FF 08 69 FF ? ? ? ? 03 F8 23 7E 04 8B 06 0F BF 1C 78 83 FB FF 74 39 8B 4E 0C 8B 51 04 8B 0C 9A 8B 01 8B 40 08 8D 55 F4 52 89 4D FC FF D0 8B 4D F4 8B 45 08 3B 48 08 75 08 8B 55 F8 3B 50 0C 74 1A"

typedef void*			(__thiscall* T_check_element)(void* _this, void* a2, void* a3);
static T_check_element	O_check_element = 0;

class IVP_MM_CMP_Key {
public:
	const void*	object[2];
	const void*	ledge[2];
};

class IVP_U_Vector_Base
{
public:
	unsigned short	memsize;
	unsigned short	n_elems;
	void**			elems;
};

class IVP_Diff_Hash {
public:
	short*				hash_to_vector_index;
	int					buffersize_minus_one;
	bool				private_buffer;
	IVP_U_Vector_Base*	base_vector;
	int					n_found_objects;
};

class IVP_Time_Event {
public:
	int index;
};

class IVP_Collision : public IVP_Time_Event {
public:
	void*	delegator;
	int		fvector_index[2];
};


namespace patch_diff_hash
{
	bool init(bool patch_after_init);
	bool patch();
};
