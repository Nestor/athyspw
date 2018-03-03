#include "Configuration.hpp"
#include "Variables.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include "HookIncludes.h"
#include <string>
#include <sstream>
#include "XorStr.hpp"

void CConfig::Setup()
{

	SetupValue(g_Options.Legitbot.MainSwitch, false, ("Legitbot"), ("Main"));
	SetupValue(g_Options.Legitbot.Aimbot.Enabled, false, ("Legitbot"), ("Enabled"));
	SetupValue(g_Options.Legitbot.backtrack, false, ("Legitbot"), ("Btrack"));
	SetupValue(g_Options.Legitbot.backtrackTicks, 0, ("Legitbot"), ("Btrack Ticks"));
	SetupValue(g_Options.Legitbot.showBacktrack, 0, ("Legitbot"), ("Show Btrack"));


	SetupValue(g_Options.Legitbot.MainKey, 1, ("Legitbot | Rifle"), ("Key"));
	SetupValue(g_Options.Legitbot.Mainfov, 0.f, ("Legitbot | Rifles"), ("FOV"));
	SetupValue(g_Options.Legitbot.MainSmooth, 1.f, ("Legitbot | Rifles"), ("Smooth"));
	SetupValue(g_Options.Legitbot.main_recoil_min, 0, ("Legitbot | Rifles"), ("RCS min"));
	SetupValue(g_Options.Legitbot.main_recoil_max, 0, ("Legitbot | Rifles"), ("RCS max"));

	SetupValue(g_Options.Legitbot.PistolKey, 6, ("Legitbot | Pistols"), ("Key"));
	SetupValue(g_Options.Legitbot.Pistolfov, 0.f, ("Legitbot | Pistols"), ("FOV"));
	SetupValue(g_Options.Legitbot.PistolSmooth, 1.f, ("Legitbot | Pistols"), ("Smooth"));
	SetupValue(g_Options.Legitbot.pistol_recoil_min, 0, ("Legitbot | Pistols"), ("RCS min"));
	SetupValue(g_Options.Legitbot.pistol_recoil_max, 0, ("Legitbo | Pistolst"), ("RCS max"));

	SetupValue(g_Options.Legitbot.SniperKey, 6, ("Legitbot | Snipers"), ("Key"));
	SetupValue(g_Options.Legitbot.Sniperfov, 0.f, ("Legitbot | Snipers"), ("FOV"));
	SetupValue(g_Options.Legitbot.SniperSmooth, 0.f, ("Legitbot | Snipers"), ("Smooth"));
	SetupValue(g_Options.Legitbot.sniper_recoil_min, 0, ("Legitbot | Snipers"), ("RCS min"));
	SetupValue(g_Options.Legitbot.sniper_recoil_max, 0, ("Legitbot | Snipers"), ("RCS max"));

	//SetupValue(g_Options.Visuals.Enabled, false, ("Visuals"), ("VisualsEnabled"));
	SetupValue(g_Options.Visuals.Box, false, ("Visuals"), ("Box"));
	SetupValue(g_Options.Visuals.BoxType, 0, ("Visuals"), ("Box Type"));
	SetupValue(g_Options.Visuals.Name, false, ("Visuals"), ("Name"));
	SetupValue(g_Options.Visuals.namepos, 0, ("Visuals"), ("Name Pos"));
	SetupValue(g_Options.Visuals.health, false, ("Visuals"), ("HP"));
	//SetupValue(g_Options.Visuals.healthmode, 0, ("Visuals"), ("HPmode"));
	SetupValue(g_Options.Visuals.healthpos, 0, ("Visuals"), ("HPpos"));
	SetupValue(g_Options.Visuals.Weapon, false, ("Visuals"), ("Weapon"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("Chams"));
	SetupValue(g_Options.Visuals.Skeleton, false, ("Visuals"), ("Skeletons"));
	SetupValue(g_Options.Visuals.TeamESP, false, ("Visuals"), ("TeamESP"));
	SetupValue(g_Options.Visuals.Grenades, false, ("Visuals"), ("GrenadeESP"));

	SetupValue(g_Options.Visuals.Hitmarker, false, ("Visuals"), ("Hitmarker"));
	SetupValue(g_Options.Visuals.Hitsound, 0, ("Visuals"), ("Hitsound"));
	SetupValue(g_Options.Visuals.FOVChanger, 0.f, ("Visuals"), ("FOV"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 68.f, ("Visuals"), ("Viewmodel FOV"));
	SetupValue(g_Options.Visuals.Droppedguns, false, ("Visuals"), ("Dropped Guns"));
	SetupValue(g_Options.Visuals.GrenadePrediction, false, ("Visuals"), ("Nade Predict"));
	SetupValue(g_Options.Visuals.Distance, false, ("Visuals"), ("Distance"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("Chams"));
	SetupValue(g_Options.Visuals.Teamchams, false, ("Visuals"), ("Teamchams"));
	SetupValue(g_Options.Visuals.XQZ, false, ("Visuals"), ("XQZ Chams"));
	SetupValue(g_Options.Visuals.champlayeralpha, 0, ("Visuals"), ("Chams Alpha"));
	SetupValue(g_Options.Visuals.matierial, 0, ("Visuals"), ("Chams Material"));
	SetupValue(g_Options.Visuals.Bomb, false, ("Visuals"), ("BombESP"));

	SetupValue(g_Options.Misc.Bhop, false, ("Misc"), ("Bhop"));
	SetupValue(g_Options.Misc.AutoStrafe, false, ("Misc"), ("Autostrafe"));

	SetupValue(g_Options.Colors.TeamESP[1], 0.f, ("Colors"), ("TeamESP [RED]"));
	SetupValue(g_Options.Colors.TeamESP[2], 1.f, ("Colors"), ("TeamESP [GREEN]"));
	SetupValue(g_Options.Colors.TeamESP[3], 0.f, ("Colors"), ("TeamESP [BLUE]"));

	SetupValue(g_Options.Colors.EnemyESP[1], 1.f, ("Colors"), ("EnemyESP [RED]"));
	SetupValue(g_Options.Colors.EnemyESP[2], 0.f, ("Colors"), ("EnemyESP [GREEN]"));
	SetupValue(g_Options.Colors.EnemyESP[3], 0.f, ("Colors"), ("EnemyESP [BLUE]"));

	SetupValue(g_Options.Colors.Backtrack[0], 0.57f, ("Colors"), ("Backtrack [RED]"));
	SetupValue(g_Options.Colors.Backtrack[1], 0.11f, ("Colors"), ("Backtrack [GREEN]"));
	SetupValue(g_Options.Colors.Backtrack[2], 0.52f, ("Colors"), ("Backtrack [BLUE]"));

	SetupValue(g_Options.Colors.EnemyChamsVis[0], 1.f, ("Colors"), ("EnemyChams [RED]"));
	SetupValue(g_Options.Colors.EnemyChamsVis[1], 0.f, ("Colors"), ("EnemyChams [GREEN]"));
	SetupValue(g_Options.Colors.EnemyChamsVis[2], 0.f, ("Colors"), ("EnemyChams [BLUE]"));

	SetupValue(g_Options.Colors.TeamChamsVis[0], 0.f, ("Colors"), ("TeamChams [RED]"));
	SetupValue(g_Options.Colors.TeamChamsVis[1], 1.f, ("Colors"), ("TeamChams [GREEN]"));
	SetupValue(g_Options.Colors.TeamChamsVis[2], 0.f, ("Colors"), ("TeamChams [BLUE]"));
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}


void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{


		folder = std::string(path) + ("\\athys.pw\\");
		switch (g_Options.Menu.ConfigFile)
		{
		case 0:
			file = std::string(path) + ("\\athys.pw\\") + std::string("cfg1") + ".conf";
			break;
		case 1:
			file = std::string(path) + ("\\athys.pw\\") + std::string("cfg2") + ".conf";
			break;
		}

	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load() {
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\athys.pw\\");
		switch (g_Options.Menu.ConfigFile)
		{
		case 0:
			file = std::string(path) + ("\\athys.pw\\") + std::string("cfg1") + ".conf";
			break;
		case 1:
			file = std::string(path) + ("\\athys.pw\\") + std::string("cfg2") + ".conf";
			break;
		}
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = (float)atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

CConfig* Config = new CConfig();
Variables g_Options;

int srucsssfblxy() { int vtmmrogewav = 339; int tspralhpra = 4382; int tvnuvprjztw = 6128; int qefxlznuszwuj = 1904; if (vtmmrogewav = 7) { tspralhpra = 4382; } int mnpxohkqsohhwq = 1904; int pmragcexive = 6128; int lcvcdtgkr = 4382; int pnucnlwt = 339; int biuvzzuhlunkfr = 4382; int tyoaaxnkvhi = 6128; int cmyapdbw = 4382; return tyoaaxnkvhi; }
int ydwjueiinozuk() { int vwmfpgofu = 114; int ryctsyscoy = 502; int ykfkelj = 2016; int dlhesdjxjrcxy = 4701; if (vwmfpgofu = 7) { ryctsyscoy = 502; } int jqivcagnniqj = 4701; int lfnoxsvwxdeq = 2016; int kwnqkdul = 502; int mujfmfugqguvt = 114; int yarpowpbiotaq = 502; int ipkeakggpfp = 2016; int qowyfyzsolx = 502; return ipkeakggpfp; }