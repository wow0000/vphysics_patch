#include "pch.h"
#include "patch_diff_hash.h"

static inline int calc_hash_index(IVP_MM_CMP_Key* o) {
	int x = (int)o->ledge[0] ^ (int(o->ledge[1]) * 75);
	return x + 1023 * (x >> 8);
}

static void* element_at(IVP_U_Vector_Base* vec, int index) {
	if (index > vec->n_elems || index < 0)
		return 0;
	return vec->elems[index];
}

static int are_equal(IVP_Collision* c, IVP_MM_CMP_Key* search) {
	if (0 == search->ledge[0] && 0 == search->ledge[1])
		return 1;
	return 0;
}

void* __fastcall H_check_element(IVP_Diff_Hash* _this, DWORD edx, DWORD* a2, DWORD* a3) {
	int buffersize_minus_one = _this->buffersize_minus_one;
	short* hash_to_vector_index = _this->hash_to_vector_index;
	IVP_U_Vector_Base* base = _this->base_vector;
	for (int i = calc_hash_index((IVP_MM_CMP_Key*)a2);; i++)
	{
		i &= buffersize_minus_one;
		int vector_index = hash_to_vector_index[i];
		if (vector_index == -1)
			return NULL;

		IVP_Collision* base_elem = (IVP_Collision*)element_at(base, vector_index);
		if (!base_elem)
			return NULL;
		int equal = are_equal(base_elem, (IVP_MM_CMP_Key*)a2);
		if (equal == 1)
			break;
	}
	return O_check_element(_this, a2, a3);
}

bool patch_diff_hash::init(bool patch_after_init) {
	O_check_element = (T_check_element)MemoryTools::FindPattern(SIG_check_element, "vphysics.dll");
	if (!O_check_element) {
		fprintf(stderr, "Could not find pattern %s for check_element %p.\n", SIG_check_element, O_check_element);
		return false;
	}
	if (patch_after_init)
		return patch();
	return true;
}

bool patch_diff_hash::patch() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)O_check_element, (PVOID)H_check_element);
	if (DetourTransactionCommit() != NO_ERROR)
		return false;
	printf("vphysics_patch: diff_hash patch applied\n");
	return true;
}
