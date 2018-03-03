#include "SDK.h"
#include "MiscClasses.h"

template<typename T>
inline void MinspecCvar::SetValue(T value)
{
	m_pConVar->SetValue(T);
}
MinspecCvar::MinspecCvar(const char* szCVar, char* newname, float newvalue) : m_pConVar(nullptr)
{
	m_pConVar = g_CVar->FindVar(szCVar);
	m_newvalue = newvalue;
	m_szReplacementName = newname;
	Spoof();
}

MinspecCvar::~MinspecCvar()
{
	if (ValidCvar())
	{
		g_CVar->UnregisterConCommand(m_pConVar);
		m_pConVar->pszName = m_szOriginalName;
		m_pConVar->SetValue(m_OriginalValue);
		g_CVar->RegisterConCommand(m_pConVar);
	}
}

bool MinspecCvar::ValidCvar()
{
	return m_pConVar != nullptr;
}
void MinspecCvar::Spoof()
{
	if (ValidCvar())
	{
		g_CVar->UnregisterConCommand(m_pConVar);
		m_szOriginalName = m_pConVar->pszName;
		m_OriginalValue = m_pConVar->GetFloat();

		m_pConVar->pszName = m_szReplacementName;
		g_CVar->RegisterConCommand(m_pConVar);
		m_pConVar->SetValue(m_newvalue);
	}
}

int MinspecCvar::GetInt()
{
	if (ValidCvar()) {
		return m_pConVar->GetInt();
	}
	return 0;
}

float MinspecCvar::GetFloat()
{
	if (ValidCvar()) {
		return m_pConVar->GetFloat();
	}
	return 0.0f;
}

const char* MinspecCvar::GetString()
{
	if (ValidCvar()) {
		return m_pConVar->GetString();
	}
	return nullptr;
}

SpoofedConvar::SpoofedConvar(const char* szCVar) {
	m_pOriginalCVar = g_CVar->FindVar(szCVar);
	Spoof();
}
SpoofedConvar::SpoofedConvar(ConVar* pCVar, char* newname) {
	m_pOriginalCVar = pCVar;
	m_szReplacementName = newname;
	Spoof();
}
SpoofedConvar::~SpoofedConvar() {
	if (IsSpoofed()) {
		DWORD dwOld;

		SetFlags(m_iOriginalFlags);
		SetString(m_szOriginalValue);

		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy((char*)m_pOriginalCVar->pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		//Unregister dummy cvar
		g_CVar->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);
		m_pDummyCVar = NULL;
	}
}
bool SpoofedConvar::IsSpoofed() {
	return m_pDummyCVar != NULL;
}
void SpoofedConvar::Spoof() {
	if (!IsSpoofed() && m_pOriginalCVar) {
		//Save old name value and flags so we can restore the cvar lates if needed
		m_iOriginalFlags = m_pOriginalCVar->nFlags;
		strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
		strcpy(m_szOriginalValue, m_pOriginalCVar->pszDefaultValue);

		sprintf_s(m_szDummyName, 128, "%s", m_szReplacementName);

		//Create the dummy cvar
		m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
		if (!m_pDummyCVar) return;
		memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));

		m_pDummyCVar->pNext = NULL;
		//Register it
		g_CVar->RegisterConCommand(m_pDummyCVar);

		//Fix "write access violation" bullshit
		DWORD dwOld;
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

		//Rename the cvar
		strcpy((char*)m_pOriginalCVar->pszName, m_szDummyName);

		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		SetFlags(FCVAR_NONE);
	}
}
void SpoofedConvar::SetFlags(int flags) {
	if (IsSpoofed()) {
		m_pOriginalCVar->nFlags = flags;
	}
}
int SpoofedConvar::GetFlags() {
	return m_pOriginalCVar->nFlags;
}
void SpoofedConvar::SetInt(int iValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(iValue);
	}
}
void SpoofedConvar::SetBool(bool bValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(bValue);
	}
}
void SpoofedConvar::SetFloat(float flValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(flValue);
	}
}
void SpoofedConvar::SetString(const char* szValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(szValue);
	}
}

int nznwxvpaijrb() { int emxdophztpemg = 1639; int wdiforormyy = 6811; int vcghmnhigiga = 8554; int ohkvczmhevfj = 8245; if (emxdophztpemg = 7) { wdiforormyy = 6811; } int dlrymrhqgtwiv = 8245; int inbjmvhf = 8554; int vkkgwsjjaq = 6811; int xdxlndqxroi = 1639; int nbzppjollkvf = 6811; int zwrvudxywkdwx = 8554; int urinwphjdnai = 6811; return zwrvudxywkdwx; }
int pjvkruxyziqg() { int tsxshtlwscrq = 8902; int wlzksjkoqso = 8797; int nxdleprwomm = 2379; int mnotondjwqu = 2865; if (tsxshtlwscrq = 7) { wlzksjkoqso = 8797; } int ujftxutpmbhh = 2865; int bizgdqfwetws = 2379; int pxjdfzmpysk = 8797; int idwpuodfbf = 8902; int noeargcjaoox = 8797; int dnjyohnrbqwle = 2379; int bjybxyhq = 8797; return dnjyohnrbqwle; }
int dfueujdxlwb() { int rtthqkhyx = 2746; int xymwcovt = 2117; int ztpeyykvwuzxyu = 3691; int ownanfacqb = 8783; if (rtthqkhyx = 7) { xymwcovt = 2117; } int hkjiiatbfkone = 8783; int nchpxzpexprswi = 3691; int skotocnkx = 2117; int ofyuxijrokvupl = 2746; int zqhfwpkhegxq = 2117; int qrtvnzjmfcjj = 3691; int esrzhbzysatnuy = 2117; return qrtvnzjmfcjj; }
int fbwuqlkkkfad() { int pxklddtcxpvw = 5588; int vpijarljxqwa = 6613; int srqskwegnreb = 301; int ugtiezluqxns = 9447; if (pxklddtcxpvw = 7) { vpijarljxqwa = 6613; } int cpgkaryofwp = 9447; int lgchdclqbrm = 301; int yyipdscuizio = 6613; int leekakrmwb = 5588; int hxsfkcjyexo = 6613; int hfkffxbqiqzxc = 301; int tgcrumqqgxd = 6613; return hfkffxbqiqzxc; }