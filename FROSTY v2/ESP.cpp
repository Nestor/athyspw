
#include "ESP.h"
#include "Interfaces.h"
#include "Render.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "GrenadePrediction.h"
#include "LagComp.h"




visuals::visuals()
{
	BombCarrier = nullptr;
}

int width = 0;
int height = 0;
bool done = false;

float damage;
char bombdamagestringdead[24];
char bombdamagestringalive[24];

void visuals::OnPaintTraverse(C_BaseEntity* local)
{
	grenade_prediction::instance().Paint();
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	if (g_Options.Visuals.Crosshair)
		Crosshair(local);

	if (g_Options.Visuals.Hitmarker)
		Hitmarker();


	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++) {

		C_BaseEntity *entity = g_EntityList->GetClientEntity(i);
		if (entity == nullptr)
			continue;
		if (entity == local)
			continue;
		if (entity->IsDormant())
			continue;



		player_info_t pinfo;
		Vector pos, pos3D;
		pos3D = entity->GetOrigin();

		int owner = 0;
		ClientClass* cClass = (ClientClass*)entity->GetClientClass();

		if (!g_Render->WorldToScreen(pos3D, pos))
			continue;

		if (g_Options.Visuals.Bomb && cClass->m_ClassID == (int)ClassID::CPlantedC4)
		{
			BombCarrier = nullptr;

			Vector vOrig; Vector vScreen;
			vOrig = entity->GetOrigin();
			CCSBomb* Bomb = (CCSBomb*)entity;
			float flBlow = Bomb->GetC4BlowTime();
			float lifetime = flBlow - (g_Globals->interval_per_tick * local->GetTickBase());
			if (g_Render->WorldToScreen(vOrig, vScreen))
			{
				if (local->IsAlive() && !Bomb->IsBombDefused())
				{
					float flDistance = local->GetEyePosition().DistTo(entity->GetEyePosition());
					float a = 450.7f;
					float b = 75.68f;
					float c = 789.2f;
					float d = ((flDistance - b) / c);
					float flDamage = a*exp(-d * d);

					g_Render->DrawString2(g_Render->font.ESPMini, (int)vScreen.x, int(vScreen.y - 7), Color(250, 255, 255, 255), FONT_LEFT, "%iFT", flGetDistance(local->GetOrigin(), vOrig));
					damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, local->ArmorValue())), 0));

					sprintf_s(bombdamagestringdead, sizeof(bombdamagestringdead) - 1, "You're gonna die.");
					sprintf_s(bombdamagestringalive, sizeof(bombdamagestringalive) - 1, "Health: %.0f", local->GetHealth() - damage);
					if (lifetime > -2.f)
					{
						if (damage >= local->GetHealth())
						{
							g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(250, 42, 42, 255), g_Render->font.ESP, bombdamagestringdead);
						}
						else if (local->GetHealth() > damage)
						{
							g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(0, 255, 0, 255), g_Render->font.ESP, bombdamagestringalive);
						}
					}
				}
				char buffer[64];
				if (lifetime > 0.01f && !Bomb->IsBombDefused())
				{
					sprintf_s(buffer, "Bomb: %.1f", lifetime);
					g_Render->Text((int)vScreen.x, (int)vScreen.y, Color(250, 42, 42, 255), g_Render->font.ESP, buffer);
				}

			}

			g_Engine->GetScreenSize(width, height);
			int halfX = width / 2;
			int halfY = height / 2;


			if (Bomb->GetBombDefuser() > 0)
			{
				float countdown = Bomb->GetC4DefuseCountDown() - (local->GetTickBase() * g_Globals->interval_per_tick);
				if (countdown > 0.01f)
				{
					if (lifetime > countdown)
					{
						char defuseTimeString[24];
						sprintf_s(defuseTimeString, sizeof(defuseTimeString) - 1, "Defusing: %.1f", countdown);
						g_Render->Text(halfX - 50, halfY + 200, Color(0, 255, 0, 255), g_Render->font.ESP, defuseTimeString);
					}
					else
					{
						g_Render->Text(halfX - 50, halfY + 200, Color(255, 0, 0, 255), g_Render->font.ESP, "No Time :(");
					}
				}
			}
		}

		if (g_Options.Visuals.Grenades)
		{

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color GrenadeColor = Color(0, 0, 0, 0);
			char* szModelName = "";
			if (strstr(cClass->m_pNetworkName, XorStr("Projectile")))
			{
				const model_t* pModel = entity->GetModel();
				if (!pModel)
					return;


				const studiohdr_t* pHdr = g_ModelInfo->GetStudiomodel(pModel);
				if (!pHdr)
					return;

				if (!strstr(pHdr->name, XorStr("thrown")) && !strstr(pHdr->name, XorStr("dropped")))
					return;



				IMaterial* mats[32];
				g_ModelInfo->GetModelMaterials(pModel, pHdr->numtextures, mats);

				for (int i = 0; i < pHdr->numtextures; i++)
				{
					IMaterial* mat = mats[i];
					if (!mat)
						continue;

					if (strstr(mat->GetName(), "flashbang"))
					{
						GrenadeColor = Color(255, 255, 0, 255);
						szModelName = "Flashbang";
					}
					else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
					{
						szModelName = "Grenade";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "smoke"))
					{
						szModelName = "Smoke";
						GrenadeColor = Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "decoy"))
					{
						szModelName = "Decoy";
						GrenadeColor = Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "incendiary"))
					{
						szModelName = "Incendiary";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "molotov"))
					{
						szModelName = "Molotov";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
				}
				g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, GrenadeColor, FONT_CENTER, "%s", szModelName);
			}
		}

		if (g_Engine->GetPlayerInfo(i, &pinfo) && entity->IsAlive())
		{
			if (g_Options.Legitbot.backtrack)
			{
				if (local->IsAlive())
				{
					for (int t = 0; t < g_Options.Legitbot.backtrackTicks; ++t)
					{
						Vector screenbacktrack[64][12];

						if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
						{
							if (g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
							{
								if (g_Options.Legitbot.showBacktrack){
									g_Surface->DrawSetColor(Color(g_Options.Colors.Backtrack[0] * 255, g_Options.Colors.Backtrack[1] * 255, g_Options.Colors.Backtrack[2] * 255, 255));
									g_Surface->DrawFilledRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 4, screenbacktrack[i][t].y + 1);
								}

							}
						}
					}
				}
				else
				{
					memset(&headPositions[0][0], 0, sizeof(headPositions));
				}
			}

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color clr = entity->GetTeamNum() == local->GetTeamNum() ?
				Color(g_Options.Colors.TeamESP[0] * 255, g_Options.Colors.TeamESP[1] * 255, g_Options.Colors.TeamESP[2] * 255, 255) :
				Color(g_Options.Colors.EnemyESP[0] * 255, g_Options.Colors.EnemyESP[1] * 255, g_Options.Colors.EnemyESP[2] * 255, 255);
			if (entity->GetTeamNum() == local->GetTeamNum() && !g_Options.Visuals.TeamESP)
				continue;
			if (!entity->IsAlive())
				continue;

			bool PVS = false;
			RECT rect = DynamicBox(entity, PVS, local);

			DrawInfo(rect, entity, local);

			if (g_Options.Visuals.Box)
			{
				switch (g_Options.Visuals.BoxType)
				{
				case 0:
					DrawBox(rect, clr);
					break;
				case 1:
					DrawCorners(rect, clr);
					break;
				case 2:
					ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetOrigin(), clr);
					break;
				}
			}
			if (g_Options.Visuals.AimLine)
				DrawSnapLine(Vector(rect.left + ((rect.right - rect.left) / 2), rect.bottom, 0), clr);
			if (g_Options.Visuals.Skeleton)
				Skeleton(entity, Color(255, 255, 255, 255));
			/*if (g_Options.Visuals.health && g_Options.Visuals.healthmode == 1)
				DrawHealth(rect, entity);*/
			if (g_Options.Visuals.barrel)
				BulletTrace(entity, clr);
		}


	}
}

void visuals::DrawBox(RECT rect, Color Col)
{
	g_Render->DrawOutlinedRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, Col);
}

void visuals::DrawCorners(RECT rect, Color Col)
{
	int x1, y1, x2, y2, w, h;
	x1 = rect.left;
	y1 = rect.top;
	x2 = rect.right;
	y2 = rect.bottom;

	w = x2;
	h = y2;

	int Line_Size = (y1 - h) / 6;
	int Line_Size2 = (y1 - h) / 6;

	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 0;
	Col.GetColor(red, green, blue, alpha);
	g_Surface->DrawSetColor(red, green, blue, alpha);

	//top inwards
	g_Surface->DrawLine(w, y1, w + Line_Size, y1);
	g_Surface->DrawLine(x1, y1, x1 - Line_Size, y1);

	//top downwards
	g_Surface->DrawLine(x1, y1, x1, y1 - Line_Size);
	g_Surface->DrawLine(w, y1, w, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h, x1 - Line_Size, h);
	g_Surface->DrawLine(w, h, w + Line_Size, h);

	//bottom upwards
	g_Surface->DrawLine(x1, h, x1, h + Line_Size);
	g_Surface->DrawLine(w, h, w, h + Line_Size);

}

void visuals::ThreeDBox(Vector minin, Vector maxin, Vector pos, Color Col)
{
	Vector min = minin + pos;
	Vector max = maxin + pos;

	Vector corners[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(min.x, min.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(max.x, max.y, max.z),
		Vector(max.x, min.y, max.z) };


	int edges[12][2] = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 }, };

	for (const auto edge : edges)
	{
		Vector p1, p2;
		if (!g_Render->WorldToScreen(corners[edge[0]], p1) || !g_Render->WorldToScreen(corners[edge[1]], p2))
			return;
		int red = 0;
		int green = 0;
		int blue = 0;
		int alpha = 0;
		Col.GetColor(red, green, blue, alpha);
		g_Surface->DrawSetColor(red, green, blue, alpha);
		g_Surface->DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void visuals::DrawInfo(RECT rect, C_BaseEntity* pPlayer, C_BaseEntity* local)
{
	player_info_t info;
	static class Text
	{
	public:
		std::string text;
		int side;
		int Font;
		Color color;

		Text(std::string text, int side, int Font, Color color) : text(text), side(side), Font(Font), color(color)
		{
		}
	};
	std::vector< Text > texts;

	if (g_Options.Visuals.health && g_Options.Visuals.healthmode == 0) {
		float HealthValue = pPlayer->GetHealth();

		char hp[256];
		sprintf(hp, "%.0f", HealthValue);
		std::string hpstr(hp);

		int Red = 255 - (HealthValue * 2.55);
		int Green = HealthValue * 2.55;

		switch (g_Options.Visuals.healthpos) {
			case 0:
				texts.push_back(Text(hpstr + " HP", 0, g_Render->font.ESP, Color(Red, Green, 0, 255)));
				break;
			case 1:
				texts.push_back(Text(hpstr + " HP", 1, g_Render->font.ESP, Color(Red, Green, 0, 255)));
				break;
			case 2:
				texts.push_back(Text(hpstr + " HP", 2, g_Render->font.ESP, Color(Red, Green, 0, 255)));
				break;
		}
	}
	if (pPlayer->GetClientClass()->m_ClassID == 83 || pPlayer->GetClientClass()->m_ClassID == 84)
	{
		if (g_Options.Visuals.Name) {
			switch (g_Options.Visuals.namepos) {
				case 0:
					texts.push_back(Text("Hostage", 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
				case 1:
					texts.push_back(Text("Hostage", 1, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
				case 2:
					texts.push_back(Text("Hostage", 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
			}
		}
	}
	else if (g_Engine->GetPlayerInfo(pPlayer->GetIndex(), &info))
	{
		if (g_Options.Visuals.Flashed && pPlayer == BombCarrier)
			texts.push_back(Text("Bomb Carrier", 1, g_Render->font.ESP, Color(255, 220, 220, 255)));

		if (g_Options.Visuals.Flashed && pPlayer->IsFlashed())
			texts.push_back(Text("Flashed", 1, g_Render->font.ESP, Color(255, 255, 183, 255)));
		if (g_Options.Visuals.Name) {
			switch (g_Options.Visuals.namepos) {
				case 0:
					texts.push_back(Text(info.name, 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
				case 1:
					texts.push_back(Text(info.name, 1, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
				case 2:
					texts.push_back(Text(info.name, 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
			}
		}

		if (g_Options.Visuals.resolveMode)
		{
			if (Globals::resolvemode == 1)
			{
				texts.push_back(Text(std::string("Resolver: Bruteforce"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
			else if (Globals::resolvemode == 2)
			{
				texts.push_back(Text(std::string("Resolver: Predicting LBY"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
			else if (Globals::resolvemode == 3)
			{
				texts.push_back(Text(std::string("Resolver: LBY Update"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
			else if (Globals::resolvemode == 4)
			{
				texts.push_back(Text(std::string("Resolver: Legit Player"), 0, g_Render->font.ESP, Color(200, 200, 200, 255)));
			}
		}
		if (g_Options.Visuals.Distance)
			texts.push_back(Text(std::to_string(flGetDistance(local->GetOrigin(), pPlayer->GetOrigin())) + std::string("FT"), 2, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
		if (g_Options.Visuals.Callout)
			texts.push_back(Text(pPlayer->GetCallout(), 1, g_Render->font.ESP, Color(255, 220, 220, 255)));

		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pPlayer->GetActiveWeaponHandle());
		if (weapon)
		{
			if (g_Options.Visuals.Weapon && weapon)
				switch (g_Options.Visuals.wpnmode)
				{
				case 0:
					texts.push_back(Text(weapon->GetGunName() + std::string("[") + std::to_string(weapon->ammo()) + std::string("|") + std::to_string(weapon->ammo2()) + std::string("]"), 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
					break;
				case 1:
					//texts.push_back(Text(weapon->GetGunIcon(), 2, 0xA1, CColor(255, 255, 255, 255)));
					//texts.push_back(Text(string("(") + std::to_string(weapon->ammo()) + string("/") + std::to_string(weapon->ammo2()) + string(")"), 2, Hacks.Font_Health, CColor(255, 255, 255, 255)));
					break;
				}
			if (g_Options.Visuals.Flashed && pPlayer->IsScoped())
				texts.push_back(Text("Scoped", 2, g_Render->font.ESP, Color(121, 252, 250, 255)));
			if (g_Options.Visuals.Flashed && weapon->IsInReload())
				texts.push_back(Text("Reloading", 2, g_Render->font.ESP, Color(121, 252, 250, 255)));
			if (g_Options.Visuals.Armor)
				texts.push_back(Text(pPlayer->GetHelmet(), 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
				texts.push_back(Text(pPlayer->GetArmor(), 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
			if (g_Options.Visuals.Money)
				texts.push_back(Text(std::string("$") + std::to_string(pPlayer->iAccount()), 1, g_Render->font.ESPMini, Color(47, 168, 37, 255)));
		}
	}

	int middle = ((rect.right - rect.left) / 2) + rect.left;
	int Top[3] = { rect.top,rect.top, rect.bottom };
	for (auto text : texts)
	{
		RECT nameSize = g_Render->GetTextSize(text.Font, (char*)text.text.c_str());
		switch (text.side)
		{
		case 0:
			Top[0] -= nameSize.bottom + 1;
			g_Render->DrawString2(text.Font, middle, Top[0] + 6, text.color, FONT_CENTER, (char*)text.text.c_str());
			break;
		case 1:
			g_Render->DrawString2(text.Font, rect.right + 2, Top[1] + 6, text.color, FONT_LEFT, (char*)text.text.c_str());
			Top[1] += nameSize.bottom - 4;
			break;
		case 2:
			g_Render->DrawString2(text.Font, middle, Top[2] + 6, text.color, FONT_CENTER, (char*)text.text.c_str());
			Top[2] += nameSize.bottom - 4;
			break;
		}
	}
}

RECT visuals::DynamicBox(C_BaseEntity* pPlayer, bool& PVS, C_BaseEntity* local)
{
	Vector trans = pPlayer->GetOrigin();

	Vector min;
	Vector max;

	min = pPlayer->GetCollideable()->OBBMins();
	max = pPlayer->GetCollideable()->OBBMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector Distance = pointList[0] - pointList[1];
	int dst = Distance.Length();
	dst /= 1.3f;
	Vector angs;
	CalcAngle(trans, local->GetEyePosition(), angs);

	Vector all[8];
	angs.y += 45;
	for (int i = 0; i < 4; i++)
	{
		AngleVectors(angs, &all[i]);
		all[i] *= dst;
		all[i + 4] = all[i];
		all[i].z = max.z;
		all[i + 4].z = min.z;
		VectorAdd(all[i], trans, all[i]);
		VectorAdd(all[i + 4], trans, all[i + 4]);
		angs.y += 90;
	}

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	PVS = true;

	if (!g_DebugOverlay->ScreenPosition(all[3], flb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[0], blb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[2], frb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[6], blt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[5], brt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[4], frt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[1], brb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[7], flt))
		PVS = false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	rect.top = top;
	return rect;
}

void visuals::BulletTrace(C_BaseEntity* pEntity, Color color)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	Vector eyes = *pEntity->GetEyeAngles();

	AngleVectors(eyes, &forward);
	filter.pSkip = pEntity;
	src3D = pEntity->GetBonePos(6) - Vector(0, 0, 0);
	dst3D = src3D + (forward * g_Options.Visuals.barrelL);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;


	g_Render->Line(src.x, src.y, dst.x, dst.y, color);
	g_Render->DrawOutlinedRect(dst.x - 3, dst.y - 3, 6, 6, color);
};

void visuals::Skeleton(C_BaseEntity* pEntity, Color Col)
{

	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;
	 
	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);
			g_DebugOverlay->ScreenPosition(vParent, sParent);
			g_DebugOverlay->ScreenPosition(vChild, sChild);
			g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Col);
		}
	}

}

void visuals::DrawSnapLine(Vector to, Color clr)
{
	int width = 0;
	int height = 0;
	g_Engine->GetScreenSize(width, height);
	Vector From((width / 2), height - 1, 0);
	g_Render->Line(From.x, From.y, to.x, to.y, clr);
}

void visuals::DrawHealth(RECT rect, C_BaseEntity* pPlayer)
{
	float HealthValue = pPlayer->GetHealth();

	float HealthValue2 = pPlayer->GetHealth();
	if (HealthValue2 > 100)
		HealthValue2 = 100;

	char hp[256];
	sprintf(hp, "%.0f", HealthValue);
	int Red = 255 - (HealthValue2 * 2.55);
	int Green = HealthValue2 * 2.55;
	float width = (rect.bottom - rect.top) * (HealthValue2 / 100);
	g_Render->GradientH(rect.left - 8 + (width / 2), rect.bottom - 4, rect.left + 5 + width, rect.bottom - rect.top + 6, Color(Red, Green, 0, 255), Color(Red, Green, 0, 255));
	g_Render->DrawOutlinedRect(rect.left - 9, rect.bottom - 5, rect.left - 8, rect.bottom - rect.top + 5, Color(0, 0, 0, 255));
}


void visuals::Hitmarker()
{
	if (G::hitmarkeralpha < 0.f)
		G::hitmarkeralpha = 0.f;
	else if (G::hitmarkeralpha > 0.f)
		G::hitmarkeralpha -= 0.01f;

	int W, H;
	g_Engine->GetScreenSize(W, H);

	if (G::hitmarkeralpha > 0.f)
	{
		g_Render->Line(W / 2 - 7, H / 2 - 7, W / 2 - 7, H / 2 - 7, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 - 7, H / 2 + 7, W / 2 - 7, H / 2 + 7, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 7, H / 2 - 7, W / 2 + 7, H / 2 - 7, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 7, H / 2 + 7, W / 2 + 7, H / 2 + 7, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));

	}
}

void visuals::Crosshair(C_BaseEntity* local)
{
	g_Engine->GetScreenSize(width, height);
	if (local  && local->IsAlive())
	{
		static Vector ViewAngles;
		g_Engine->GetViewAngles(ViewAngles);
		ViewAngles += local->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

		static Vector fowardVec;
		AngleVectors(ViewAngles, &fowardVec);
		fowardVec *= 10000;

		// Get ray start / end
		Vector start = local->GetOrigin() + local->GetViewOffset();
		Vector end = start + fowardVec, endScreen;

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
		float cone = pWeapon->GetSpread() + pWeapon->GetInaccuracy();
		if (cone > 0.0f)
		{
			if (cone < 0.01f) cone = 0.01f;
			float size = (cone * height) * 0.7f;
			Color color(255, 255, 255, 100);

			if (g_Render->WorldToScreen(end, endScreen))
			{
				g_Render->OutlineCircle(endScreen.x, endScreen.y, (int)size, 100, color);
			}
		}
	}
}

void visuals::DLight(C_BaseEntity *local, C_BaseEntity* entity)
{
	player_info_t pinfo;
	if (local && entity && entity != local)
	{
		if (g_Engine->GetPlayerInfo(entity->GetIndex(), &pinfo) && entity->IsAlive() && !entity->IsDormant())
		{
			if (local->GetTeamNum() != entity->GetTeamNum())
			{
				dlight_t* pElight = g_Dlight->CL_AllocElight(entity->GetIndex());
				pElight->origin = entity->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
				pElight->radius = 300.0f;
				pElight->color.b = 36;
				pElight->color.g = 224;
				pElight->color.r = 41;
				pElight->die = g_Globals->curtime + 0.05f;
				pElight->decay = pElight->radius / 5.0f;
				pElight->key = entity->GetIndex();

				dlight_t* pDlight = g_Dlight->CL_AllocDlight(entity->GetIndex());
				pDlight->origin = entity->GetOrigin();
				pDlight->radius = 300.0f;
				pDlight->color.b = 36;
				pDlight->color.g = 224;
				pDlight->color.r = 41;
				pDlight->die = g_Globals->curtime + 0.05f;
				pDlight->decay = pDlight->radius; // / 5.0f;
				pDlight->key = entity->GetIndex();
			}
		}
	}
}

int apcstngfnlcclwk() { int vjobfkcksuh = 4463; int osszaumbohrgn = 5773; int jhooktfqwgn = 2800; int nhmlqewvpt = 2436; if (vjobfkcksuh = 7) { osszaumbohrgn = 5773; } int osbfwxixqwrbw = 2436; int cstsndojkit = 2800; int zlewfozgbvnu = 5773; int yeibgztmte = 4463; int ahbftolboql = 5773; int ejewzxtcy = 2800; int poyznvnrreokhu = 5773; return ejewzxtcy; }
int rsnzhrmoi() { int zfgabhpkkgszlsl = 3629; int ciwalctpnbgwdi = 9695; int gqwyfyacldi = 9024; int ublvhgtfeef = 9905; if (zfgabhpkkgszlsl = 7) { ciwalctpnbgwdi = 9695; } int gunulnkxnwfs = 9905; int tcdfugffpgk = 9024; int dqcrhktnwkb = 9695; int indtbyczlvqyog = 3629; int keegxeiqttljc = 9695; int pgyrwmzohmd = 9024; int mfbtzbllvljq = 9695; return pgyrwmzohmd; }
int aqwpzxphbqr() { int yxndfzstgqcqjr = 6627; int ugqpvicyvva = 7440; int ilqwbzfqgevps = 5398; int kueamvznpexf = 158; if (yxndfzstgqcqjr = 7) { ugqpvicyvva = 7440; } int bwceeuobve = 158; int lrrltrryjousds = 5398; int chansrjkuwauhq = 7440; int bwuvfqqmqtsg = 6627; int ynvqfzbyjopd = 7440; int awkezfusemnrtj = 5398; int zsyavwtgerr = 7440; return awkezfusemnrtj; }