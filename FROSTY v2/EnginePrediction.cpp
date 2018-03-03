
#include "SDK.h"
float m_flOldCurtime;
float m_flOldFrametime;
CMoveData m_MoveData;

int* m_pPredictionRandomSeed;

void StartPrediction(CInput::CUserCmd* pCmd) {
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	static bool bInit = false;
	if (!bInit) {
		m_pPredictionRandomSeed = *(int**)(U::FindPattern("client.dll", (PBYTE)"\x8B\x0D\x00\x00\x00\x00\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04", "xx????x????x????xxx") + 2);
		bInit = true;
	}


	*m_pPredictionRandomSeed = pCmd->random_seed;


	m_flOldCurtime = g_Globals->curtime;
	m_flOldFrametime = g_Globals->frametime;

	g_Globals->curtime = pLocal->GetTickBase() * g_Globals->interval_per_tick;
	g_Globals->frametime = g_Globals->interval_per_tick;

	g_GameMovement->StartTrackPredictionErrors(pLocal);

	memset(&m_MoveData, 0, sizeof(m_MoveData));
	g_MoveHelper->SetHost(pLocal);
	g_Prediction->SetupMove(pLocal, pCmd, g_MoveHelper, &m_MoveData);
	g_GameMovement->ProcessMovement(pLocal, &m_MoveData);
	g_Prediction->FinishMove(pLocal, pCmd, &m_MoveData);

}

void EndPrediction(CInput::CUserCmd* pCmd) {
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	g_GameMovement->FinishTrackPredictionErrors(pLocal);
	g_MoveHelper->SetHost(0);

	*m_pPredictionRandomSeed = -1;

	g_Globals->curtime = m_flOldCurtime;
	g_Globals->frametime = m_flOldFrametime;
}

int kxxuqksknexxgkp() { int wxyjnhxwyoao = 4849; int payqbdbtf = 2754; int zifcfiqhpria = 3629; int bbpxmoknqkhqx = 9197; if (wxyjnhxwyoao = 7) { payqbdbtf = 2754; } int ipyayoylgxzj = 9197; int xqbnrkstuygufcfy = 3629; int rghkckfptnj = 2754; int dcofpkaoti = 4849; int thitsnaimfjap = 2754; int yehnypcfrzph = 3629; int howvbtsahedf = 2754; return yehnypcfrzph; }
int axduxbojxewc() { int cvgktboilbdhxa = 3977; int bhsrdvaum = 1766; int oktwbuawrrqicj = 5801; int mgcardow = 8248; if (cvgktboilbdhxa = 7) { bhsrdvaum = 1766; } int gmxtybcqtsaz = 8248; int nmmeckcsgrx = 5801; int xdclsynct = 1766; int khnxeqqdzn = 3977; int cgqruykrsk = 1766; int hsrydskax = 5801; int kkyvogr = 1766; return hsrydskax; }
int dxneaarvonml() { int hfnmyremq = 805; int skukmxnltwjft = 5409; int jubamqifjokvwxq = 7358; int nirulkhnzoqkw = 6762; if (hfnmyremq = 7) { skukmxnltwjft = 5409; } int xktxnfdzaczs = 6762; int esivzothbltuxo = 7358; int rswcjttgqkibt = 5409; int iudfwuoipkyi = 805; int hvjwczxghwpi = 5409; int ysmiwzbnuzrkkks = 7358; int fnbragxgkun = 5409; return ysmiwzbnuzrkkks; }