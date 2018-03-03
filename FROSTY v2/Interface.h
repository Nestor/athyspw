#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Themes.h"
#include <cctype>
#include "Logging.h"
#include "Listener.h"
#include "Renderer.h"

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define BUILDSTAMP ( __DATE__ )
typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void FullUpdate()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(U::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}

//--------------------------------------------
//Weapon CFG stuff

bool m_bIsDown;
bool m_bIsClicked;

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";

	default:
		return "";
	}
}


bool IsUtility(ItemDefinitionIndexx index)
{
	switch (index)
	{
	case ItemDefinitionIndexx::ITEM_NONE:
	case ItemDefinitionIndexx::WEAPON_C4:
	case ItemDefinitionIndexx::WEAPON_FLASH:
	case ItemDefinitionIndexx::WEAPON_HE:
	case ItemDefinitionIndexx::WEAPON_INC:
	case ItemDefinitionIndexx::WEAPON_MOLOTOV:
	case ItemDefinitionIndexx::WEAPON_SMOKE:
	case ItemDefinitionIndexx::WEAPON_DECOY:
	case ItemDefinitionIndexx::WEAPON_KNIFE_T:
	case ItemDefinitionIndexx::WEAPON_KNIFE_CT:
	case ItemDefinitionIndexx::GLOVE_T_SIDE:
	case ItemDefinitionIndexx::GLOVE_CT_SIDE:
	case ItemDefinitionIndexx::GLOVE_SPORTY:
	case ItemDefinitionIndexx::GLOVE_SLICK:
	case ItemDefinitionIndexx::GLOVE_LEATHER_WRAP:
	case ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND:
	case ItemDefinitionIndexx::GLOVE_MOTORCYCLE:
	case ItemDefinitionIndexx::GLOVE_SPECIALIST:
		return true;
	default:
		return false;
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);

	return str;
}
//--------------------------------------------
bool defaultk;
bool bayonet;
bool flip;
bool gut;
bool karambit;
bool m9bayonet;
bool huntsman;
bool falchion;
bool bowie;
bool butterfly;
bool daggers;

void doknives(bool* disknife)
{
	defaultk = false;
	bayonet = false;
	flip = false;
	gut = false;
	karambit = false;
	m9bayonet = false;
	huntsman = false;
	falchion = false;
	bowie = false;
	butterfly = false;
	daggers = false;

	*disknife = true;
}

const char* HitmarkSound[] =
{
	"Disabled",
	"Default",
	"Roblox",
	"Trump",
	"Skeet",
	"Minecraft"
};

bool CheckToggle(bool vecPressedKeys[256])
{
	if (vecPressedKeys[VK_F11] || vecPressedKeys[VK_INSERT])
	{
		m_bIsClicked = false;
		m_bIsDown = true;
	}
	else if (!vecPressedKeys[VK_F11] && !vecPressedKeys[VK_INSERT] && m_bIsDown)
	{
		m_bIsClicked = true;
		m_bIsDown = false;

		g_Options.Menu.Opened = !g_Options.Menu.Opened;
		static auto cl_mouseenable = g_CVar->FindVar(XorStr("cl_mouseenable"));
		cl_mouseenable->SetValue(!g_Options.Menu.Opened);
	}
	else
	{
		m_bIsClicked = false;
		m_bIsDown = false;
	}
	return m_bIsClicked;
}

void RenderInterface() {


	auto& style = ImGui::GetStyle();
	bool is_renderer_active = renderer->IsActive();

	if (is_renderer_active)
	{
		if (style.Alpha > 1.f)
			style.Alpha = 1.f;
		else if (style.Alpha != 1.f)
			style.Alpha += 0.01f;
	}
	else
	{
		if (style.Alpha < 0.f)
			style.Alpha = 0.f;
		else if (style.Alpha != 0.f)
			style.Alpha -= 0.01f;
	}

	if (is_renderer_active)
	{
		if (g_Options.Menu.iTab == 0) {

			ImGui::Begin("Athys.pw", &g_Options.Menu.Opened, ImVec2(620, 370), 0.9f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			{
				ImGui::TextColored(ImVec4(0.9f, 0.55f, 0.4f, 1.0f), "Athys.pw");
				ImGui::Text("Current Tab: Aimbot");

				if (ImGui::Button(XorStr("Aimbot"), ImVec2(123, 25))) g_Options.Menu.iTab = 0;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Trigger"), ImVec2(123, 25))) g_Options.Menu.iTab = 1;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Visuals"), ImVec2(123, 25))) g_Options.Menu.iTab = 2;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Misc"), ImVec2(123, 25))) g_Options.Menu.iTab = 3;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Skins"), ImVec2(121, 25))) g_Options.Menu.iTab = 4;

				ImGui::Checkbox(XorStr("Enabled"), &g_Options.Legitbot.MainSwitch);
				ImGui::SameLine();
				ImGui::Checkbox(XorStr("Friendly Fire"), &g_Options.Legitbot.FriendlyFire);

				ImGui::BeginChild("rifles", ImVec2(200, 167), true);
				{
					ImGui::Text("Rifles");
					ImGui::PushItemWidth(180);
					ImGui::Text("Key");
					ImGui::Hotkey(XorStr("##0"), &g_Options.Legitbot.MainKey);
					ImGui::SliderFloat(XorStr("Smooth##0"), &g_Options.Legitbot.MainSmooth, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("FOV##0"), &g_Options.Legitbot.Mainfov, 0.00f, 30.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Min RCS##0"), &g_Options.Legitbot.main_recoil_min, 0.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Max RCS##0"), &g_Options.Legitbot.main_recoil_max, 0.00f, 100.00f, "%.2f");
					ImGui::PopItemWidth();
				}ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("pistols", ImVec2(200, 167), true);
				{
					ImGui::Text("Pistols");
					ImGui::PushItemWidth(180);
					ImGui::Text("Key");
					ImGui::Hotkey(XorStr("##1"), &g_Options.Legitbot.PistolKey);
					ImGui::SliderFloat(XorStr("Smooth##1"), &g_Options.Legitbot.PistolSmooth, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("FOV##1"), &g_Options.Legitbot.Pistolfov, 0.00f, 30.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Min RCS##1"), &g_Options.Legitbot.pistol_recoil_min, 0.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Max RCS##1"), &g_Options.Legitbot.pistol_recoil_max, 0.00f, 100.00f, "%.2f");
				}ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("third child", ImVec2(200, 167), true);
				{
					ImGui::Text("Snipers");
					ImGui::PushItemWidth(180);
					ImGui::Text("Key");
					ImGui::Hotkey(XorStr("##2"), &g_Options.Legitbot.SniperKey);
					ImGui::SliderFloat(XorStr("Smooth##2"), &g_Options.Legitbot.SniperSmooth, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("FOV##2"), &g_Options.Legitbot.Sniperfov, 0.00f, 30.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Min RCS##2"), &g_Options.Legitbot.sniper_recoil_min, 0.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Max RCS##2"), &g_Options.Legitbot.sniper_recoil_max, 0.00f, 100.00f, "%.2f");
				}ImGui::EndChild();

				ImGui::BeginChild("backtrack", ImVec2(200, 100), true);
				{
					ImGui::PushItemWidth(180);
					ImGui::Text("Backtracking");
					ImGui::Checkbox(XorStr("Enabled"), &g_Options.Legitbot.backtrack);
					ImGui::SliderFloat(XorStr("Ticks: "), &g_Options.Legitbot.backtrackTicks, 0, 12, "%1.f");
					ImGui::Checkbox(XorStr("Show Backtrack"), &g_Options.Legitbot.showBacktrack);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##Backtrack", g_Options.Colors.Backtrack, 1 << 7);
				}ImGui::EndChild();
			}
			ImGui::End();
		}
		else if (g_Options.Menu.iTab == 1) {
			ImGui::Begin("Athys.pw", &g_Options.Menu.Opened, ImVec2(620, 370), 0.9f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			{
				ImGui::TextColored(ImVec4(0.9f, 0.55f, 0.4f, 1.0f), "Athys.pw");
				ImGui::Text("Current Tab: Trigger");

				if (ImGui::Button(XorStr("Aimbot"), ImVec2(123, 25))) g_Options.Menu.iTab = 0;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Trigger"), ImVec2(123, 25))) g_Options.Menu.iTab = 1;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Visuals"), ImVec2(123, 25))) g_Options.Menu.iTab = 2;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Misc"), ImVec2(123, 25))) g_Options.Menu.iTab = 3;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Skins"), ImVec2(121, 25))) g_Options.Menu.iTab = 4;

				ImGui::BeginChild("trigger", ImVec2(196, 180), true, ImGuiWindowFlags_ChildWindowAutoFitY);
				{
					ImGui::PushItemWidth(180);
					ImGui::Checkbox(XorStr("Enabled"), &g_Options.Triggerbot.Enabled);
					ImGui::Checkbox(XorStr("Always active"), &g_Options.Triggerbot.AlwaysActive);
					ImGui::Checkbox(XorStr("Sniper scoped only"), &g_Options.Triggerbot.SniperScopedOnly);
					ImGui::Text("Key");
					ImGui::Combo(XorStr("##"), &g_Options.Triggerbot.Key, g_Options.Keys, IM_ARRAYSIZE(g_Options.Keys));
				}ImGui::EndChild();
			}
			ImGui::End();
		}
		else if (g_Options.Menu.iTab == 2) {
			ImGui::Begin("Athys.pw", &g_Options.Menu.Opened, ImVec2(620, 370), 0.9f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			{
				ImGui::TextColored(ImVec4(0.9f, 0.55f, 0.4f, 1.0f), "Athys.pw");
				ImGui::Text("Current Tab: Visual");

				if (ImGui::Button(XorStr("Aimbot"), ImVec2(123, 25))) g_Options.Menu.iTab = 0;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Trigger"), ImVec2(123, 25))) g_Options.Menu.iTab = 1;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Visuals"), ImVec2(123, 25))) g_Options.Menu.iTab = 2;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Misc"), ImVec2(123, 25))) g_Options.Menu.iTab = 3;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Skins"), ImVec2(121, 25))) g_Options.Menu.iTab = 4;

				ImGui::BeginChild("first child", ImVec2(200, 237), true);
				{
					ImGui::Checkbox(XorStr("Box"), &g_Options.Visuals.Box);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##EdddSP", g_Options.Colors.EnemyESP, 1 << 7);
					ImGui::Checkbox(XorStr("Team ESP"), &g_Options.Visuals.TeamESP);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##ESP", g_Options.Colors.TeamESP, 1 << 7);
					ImGui::Checkbox(XorStr("Skeleton"), &g_Options.Visuals.Skeleton);
					ImGui::Checkbox(XorStr("Name"), &g_Options.Visuals.Name);
					ImGui::Checkbox(XorStr("Weapon"), &g_Options.Visuals.Weapon);
					ImGui::Checkbox(XorStr("Nade Predict"), &g_Options.Visuals.GrenadePrediction);
					ImGui::Checkbox(XorStr("Bomb ESP"), &g_Options.Visuals.Bomb);
					ImGui::Checkbox(XorStr("Grenades"), &g_Options.Visuals.Grenades);
					ImGui::Checkbox(XorStr("Dropped Weapons"), &g_Options.Visuals.Droppedguns);
				}ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("second child", ImVec2(200, 237), true);
				{
					ImGui::Text("Chams");
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Chams Players"), &g_Options.Visuals.Chams);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##45ESP", g_Options.Colors.EnemyChamsVis, 1 << 7);
					ImGui::Checkbox(XorStr("Chams Team"), &g_Options.Visuals.Teamchams);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##E772SP", g_Options.Colors.TeamChamsVis, 1 << 7);
					ImGui::PushItemWidth(184);
					ImGui::SliderInt(XorStr(" ##pca"), &g_Options.Visuals.champlayeralpha, 0, 100);
					ImGui::Combo("##sdgl", &g_Options.Visuals.matierial, "Normal\0\rFlat\0\rWireframe\0\0", -1);
					ImGui::Separator();
					ImGui::Text("FOV");
					ImGui::PushItemWidth(184);
					ImGui::SliderFloat(XorStr("FOV"), &g_Options.Visuals.FOVChanger, 0, 60, "%.0f");
					ImGui::SliderFloat(XorStr("Viewmodel FOV"), &g_Options.Visuals.viewmodelChanger, 0, 130, "%.0f");
				}ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("third child", ImVec2(200, 237), true);
				{
					ImGui::Text("Settings");
					ImGui::Text("Box Type");
					ImGui::Combo("##boxkek", &g_Options.Visuals.BoxType, "Full\0\rCorners\0\r3D\0\0", -1);
					ImGui::Text("Name Position");
					ImGui::Combo("##namekek", &g_Options.Visuals.namepos, "Top\0\Right\0\Bottom\0\0", -1);
					ImGui::Text("Health");
					//ImGui::Combo("Mode", &g_Options.Visuals.healthmode, "Number\0\Bar\0\0", -1);
					ImGui::Combo("Number", &g_Options.Visuals.healthpos, "Top\0\Right\0\Bottom\0\0", -1);
				}ImGui::EndChild();
			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 3) {
			ImGui::Begin("Athys.pw", &g_Options.Menu.Opened, ImVec2(620, 370), 0.9f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			{
				ImGui::TextColored(ImVec4(0.9f, 0.55f, 0.4f, 1.0f), "Athys.pw");
				ImGui::Text("Current Tab: Misc");

				if (ImGui::Button(XorStr("Aimbot"), ImVec2(123, 25))) g_Options.Menu.iTab = 0;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Trigger"), ImVec2(123, 25))) g_Options.Menu.iTab = 1;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Visuals"), ImVec2(123, 25))) g_Options.Menu.iTab = 2;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Misc"), ImVec2(123, 25))) g_Options.Menu.iTab = 3;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Skins"), ImVec2(121, 25))) g_Options.Menu.iTab = 4;

				ImGui::BeginChild("first child", ImVec2(200, 197), true);
				{
					ImGui::Text("Misc");
					ImGui::Separator();
					ImGui::Text("Automation");
					ImGui::Checkbox(XorStr("Bhop"), &g_Options.Misc.Bhop);
					ImGui::Checkbox(XorStr("AutoStrafe"), &g_Options.Misc.AutoStrafe);
					ImGui::Text("Hitmarkers");
					ImGui::Checkbox(XorStr("Enable"), &g_Options.Visuals.Hitmarker);
					ImGui::Text(XorStr("Sound:"));
					ImGui::Combo(XorStr("##asad4asds"), &g_Options.Visuals.Hitsound, HitmarkSound, ARRAYSIZE(HitmarkSound));
				}ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("second child", ImVec2(200, 197), true);
				{
					ImGui::Text("Config");
					ImGui::Combo(("File"), &g_Options.Menu.ConfigFile, configFiles, ARRAYSIZE(configFiles));
					if (ImGui::Button("Save Config")) Config->Save();
					if (ImGui::Button("Load Config")) Config->Load();
					if (ImGui::Button(XorStr("Unload")))
					{
						g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
						unload = true;
					}
				}ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("third child", ImVec2(200, 197), true);
				{
					ImGui::Text("Themes");
					ImGui::Combo("##themekek", &g_Options.Menu.Theme, "Default\0\Red\0\Green\0\0", -1);
				}ImGui::EndChild();
			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 4) {
			static char filterWeapons[32];
			static char filterSkins[32];
			ImGui::Begin("Athys.pw", &g_Options.Menu.Opened, ImVec2(620, 370), 0.9f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			{
				ImGui::TextColored(ImVec4(0.9f, 0.55f, 0.4f, 1.0f), "Athys.pw");
				ImGui::Text("Current Tab: Skins");

				if (ImGui::Button(XorStr("Aimbot"), ImVec2(123, 25))) g_Options.Menu.iTab = 0;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Trigger"), ImVec2(123, 25))) g_Options.Menu.iTab = 1;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Visuals"), ImVec2(123, 25))) g_Options.Menu.iTab = 2;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Misc"), ImVec2(123, 25))) g_Options.Menu.iTab = 3;
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::Button(XorStr("Skins"), ImVec2(121, 25))) g_Options.Menu.iTab = 4;
				ImGui::Checkbox(XorStr("Enable"), &g_Options.Skinchanger.Enabled);
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Apply"), ImVec2(130, 20))) FullUpdate();
				ImGui::BeginChild("first child", ImVec2(200, 230), true);
				{
					ImGui::Text("Guns");
					ImGui::PushItemWidth(-1);
					ImGui::InputText(XorStr("##FILTERWEAPONS"), filterWeapons, IM_ARRAYSIZE(filterWeapons));
					ImGui::PopItemWidth();
					ImGui::ListBoxHeader(XorStr("##GUNS"), ImVec2(-1, -1));
					for (auto it : ItemDefinitionIndexMap)
					{
						bool isDefault = (int)it.first < 0;
						if (!isDefault && !Contains(ToLower(std::string(filterWeapons)), ToLower(ItemDefinitionIndexMap.at(it.first).entityName)))
							continue;

						if (IsUtility(it.first))
							continue;

						const bool item_selected = ((int)it.first == (int)g_Options.Menu.currentWeapon);
						//ImGui::PushID((int)it.first);
						std::string formattedName;

						formattedName = ItemDefinitionIndexMap.at(it.first).changerName;
						if (ImGui::Selectable(formattedName.c_str(), item_selected))
						{
							g_Options.Menu.currentWeapon = (int)it.first;
						}
					}
					ImGui::ListBoxFooter();
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("second child", ImVec2(200, 230), true);
				{
						ImGui::Text("Skins");
						std::string skinName = weaponnames(g_Options.Menu.currentWeapon);
						{
							ImGui::PushItemWidth(-1);
							ImGui::InputText(XorStr("##FILTERSKINS"), filterSkins, IM_ARRAYSIZE(filterSkins));
							ImGui::PopItemWidth();
							ImGui::ListBoxHeader(XorStr("##SKINS"), ImVec2(-1, -1));
							std::string skinStr = "";
							int curItem = -1;
							int s = 0;
							for (auto skin : g_Options.Skinchanger.weaponSkins[skinName])
							{
								int pk = g_Options.Skinchanger.skinMap[skin].paintkit;
								if (pk == g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin)
									curItem = s;
								bool selected = g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin == pk;

								skinStr = g_Options.Skinchanger.skinNames[g_Options.Skinchanger.skinMap[skin].tagName].c_str();
								if (!Contains(ToLower(std::string(filterSkins)), ToLower(skinStr)))
									continue;
								if (ImGui::Selectable(skinStr.c_str(), selected))
								{
									pk = g_Options.Skinchanger.skinMap[skin].paintkit;
									g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin = pk;
									FullUpdate();
									break;
								}
								s++;
							}

							ImGui::ListBoxFooter();
						}
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("third child", ImVec2(200, 230), true);
				{
					    ImGui::Text("Custom Names");
						ImGui::Checkbox(XorStr("Enable"), &g_Options.Skinchanger.customName);
						ImGui::Text("Knives");
						ImGui::ListBoxHeader("##KNIVES", ImVec2(-1, -1));
						{
							if (ImGui::RadioButton(XorStr("Default"), &g_Options.Skinchanger.knifemodel, 0))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Bayonet"), &g_Options.Skinchanger.knifemodel, 1))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Flip Knife"), &g_Options.Skinchanger.knifemodel, 2))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Gut Knife"), &g_Options.Skinchanger.knifemodel, 3))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Karambit"), &g_Options.Skinchanger.knifemodel, 4))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("M9 Bayonet"), &g_Options.Skinchanger.knifemodel, 5))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Huntsman"), &g_Options.Skinchanger.knifemodel, 6))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Falchion"), &g_Options.Skinchanger.knifemodel, 7))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Bowie"), &g_Options.Skinchanger.knifemodel, 8))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Butterfly Knife"), &g_Options.Skinchanger.knifemodel, 9))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Shadow Daggers"), &g_Options.Skinchanger.knifemodel, 10)) {
								FullUpdate();
							}
						}
						ImGui::ListBoxFooter();
						ImGui::Text("Glovetype");
						ImGui::ListBoxHeader("##GLOVES", ImVec2(-1, -1));
						{
							if (ImGui::RadioButton(XorStr("Bloodhound"), &g_Options.Skinchanger.glove, 1))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Sport"), &g_Options.Skinchanger.glove, 2))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Driver"), &g_Options.Skinchanger.glove, 3))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Hand Wraps"), &g_Options.Skinchanger.glove, 4))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Motorcycle"), &g_Options.Skinchanger.glove, 5))
							{
								FullUpdate();
							}
							if (ImGui::RadioButton(XorStr("Specialst"), &g_Options.Skinchanger.glove, 6))
							{
								FullUpdate();
							}
						} ImGui::ListBoxFooter();

						ImGui::Text("Gloveskin");
						const char* gstr;
						if (g_Options.Skinchanger.glove == 1)
						{
							gstr = "Charred\0\rSnakebite\0\rBronzed\0\rGuerilla\0\0";
						}
						else if (g_Options.Skinchanger.glove == 2)
						{
							gstr = "Hedge Maze\0\rPandoras Box\0\rSuperconductor\0\rArid\0\0";
						}
						else if (g_Options.Skinchanger.glove == 3)
						{
							gstr = "Lunar Weave\0\rConvoy\0\rCrimson Weave\0\rDiamondback\0\0";
						}
						else if (g_Options.Skinchanger.glove == 4)
						{
							gstr = "Leather\0\rSpruce DDPAT\0\rSlaughter\0\rBadlands\0\0";
						}
						else if (g_Options.Skinchanger.glove == 5)
						{
							gstr = "Eclipse\0\rSpearmint\0\rBoom!\0\rCool Mint\0\0";
						}
						else if (g_Options.Skinchanger.glove == 6)
						{
							gstr = "Forest DDPAT\0\rCrimson Kimono\0\rEmerald Web\0\rFoundation\0\0";
						}
						else
						{
							gstr = "";
						}
						ImGui::PushItemWidth(-1);
						if (ImGui::Combo(XorStr("##2"), &g_Options.Skinchanger.gloveskin, gstr, -1))
							FullUpdate();
						ImGui::PopItemWidth();
					}ImGui::EndChild();
				}ImGui::End();
		}
	}
}