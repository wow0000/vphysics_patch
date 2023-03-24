#include "pch.h"
#include "patch_diff_hash.h"

DWORD WINAPI main_thread(void* arg)
{
	if (DetourIsHelperProcess())
		return TRUE;
	DetourRestoreAfterWith();

	patch_diff_hash::init(true);

	printf("vphysics_patch: loaded\n");
	return (0);
}

BOOL APIENTRY DllMain(HMODULE	hModule,
					  DWORD		ul_reason_for_call,
					  LPVOID	lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, main_thread, NULL, 0, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

GMOD_MODULE_OPEN()
{
	return 0;
}

