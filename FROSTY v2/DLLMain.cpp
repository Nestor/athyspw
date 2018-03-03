#include "Interfaces.h"
#include "Hooks.h"
#include "Render.h"
#include "SDK.h"

#include "recvproxy.h"
#include "Misc.h"

bool unload;

bool on_dll_attach(void* base)
{
	InitialiseInterfaces();
	g_Netvars->GetNetvars();
	g_Render->SetupFonts();
	hooks::initialize();
	NetvarHook();

	while (unload == false)
	{
		Sleep(1000);
	}


	UnloadProxy();
	hooks::cleanup();

	Sleep(2000);
	FreeLibraryAndExitThread((HMODULE)base, 0);
}

bool on_dll_detach()
{
	U::CloseConsole();
	UnloadProxy();
	hooks::cleanup();
	return 1;
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_	LPVOID    lpvReserved
)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		MessageBox(0, "Successfully injected! Have fun.", "Athys.pw", MB_OK);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)on_dll_attach, hinstDll, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return on_dll_detach();
	}
	return TRUE;
}

int rygzhilodfgnjsn() { int bcbvzvars = 9660; int coyywybvwh = 2791; int yhjejnkftvhv = 2015; int zphpyvkabbmia = 345; if (bcbvzvars = 7) { coyywybvwh = 2791; } int fsvdilhwbue = 345; int anavzjxvhhl = 2015; int lvjvqqabmxx = 2791; int qkiafqgrfl = 9660; int qinthqsambmy = 2791; int qwjhfgkeg = 2015; int mhrxhabvgjbcjr = 2791; return qwjhfgkeg; }
int fvbnyhuakoqve() { int kerzhcwgvpfj = 5844; int zfhklgiloh = 5277; int kfzhzccihpdj = 5523; int zjjkicwhhfbpeo = 401; if (kerzhcwgvpfj = 7) { zfhklgiloh = 5277; } int nvrwxnzfc = 401; int necwhofxhiyvd = 5523; int zkyriangdsnulfa = 5277; int jeubdbuqijuym = 5844; int bsnjrgttxosaneq = 5277; int keoyqvdyp = 5523; int vtfnlonukgyw = 5277; return keoyqvdyp; }
int dqabwwulhoavj() { int eucbnrpseq = 1261; int jqkctliqibh = 5874; int ijvdpxlvnyscf = 7268; int cwkmhmzvbooeul = 1763; if (eucbnrpseq = 7) { jqkctliqibh = 5874; } int zjrlknsidpich = 1763; int ioaafejrpp = 7268; int anagzjxalfwjw = 5874; int kyjdxtki = 1261; int crgzyxlzlyny = 5874; int ywuatlnrocbe = 7268; int ylthuxdajdkb = 5874; return ywuatlnrocbe; }