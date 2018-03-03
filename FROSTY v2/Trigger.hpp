#pragma once

#include "SDK.h"
#include "EnginePrediction.h"
#include "Global.h"
#include "MathFunctions.h"
#include "MiscClasses.h"
#include "Interface.h"

class Trigger
{
public:
	void CreateMove_Post(C_BaseEntity* pLocal, CInput::CUserCmd* pCmd) const
	{
		if (!IsEnabled(pLocal))
			return;

		if (!IsTargetInSight(pLocal, pCmd))
			return;

		auto pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
		if (!pWeapon || pWeapon->ammo() == 0)
			return;

		if (MiscFunctions::IsPistol(pWeapon))
			AutoPistol(pLocal, pWeapon, pCmd);
		else
			pCmd->buttons |= IN_ATTACK;
	}
private:
	void AutoPistol(C_BaseEntity* pLocal, CBaseCombatWeapon* pWeapon, CInput::CUserCmd* pCmd) const
	{
		// Let AutoPistol class handle this situation
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
			return;

		if (pWeapon->GetNextPrimaryAttack() > pLocal->GetTickBase() * g_Globals->interval_per_tick)
			return;

		if (*pWeapon->ItemDefinitionIndex() == WEAPON_REVOLVER)
			pCmd->buttons |= IN_ATTACK2;
		else
			pCmd->buttons |= IN_ATTACK;
	}

	bool IsEnabled(C_BaseEntity* pLocal) const
	{
		if (!(g_Options.Triggerbot.Enabled) || pLocal == nullptr || !pLocal->IsAlive())
			return false;

		if (!GetAsyncKeyState(g_Options.KeysID[g_Options.Triggerbot.Key]) && !g_Options.Triggerbot.AlwaysActive)
			return false;

		auto pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
		if (!pWeapon)
			return false;

		const auto shouldBeScoped = g_Options.Triggerbot.SniperScopedOnly && MiscFunctions::IsPistol(pWeapon);
		if (shouldBeScoped && !pLocal->IsScoped())
			return false;

		return !(MiscFunctions::IsGrenade(pWeapon) || MiscFunctions::IsKnife(pWeapon));
	}

	bool IsTargetInSight(C_BaseEntity* pLocal, CInput::CUserCmd* pCmd) const
	{
		auto vTraceForward = Vector(0, 0, 0);
		auto vTraceAngles = pCmd->viewangles;
		Vector AimPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();
		const auto punchAngles = AimPunch * 2.0f;
		if (punchAngles.x != 0.0f || punchAngles.y != 0)
		{
			vTraceAngles -= punchAngles;
			ClampAngles(vTraceAngles);
		}
		AngleVectors(vTraceAngles, &vTraceForward);
		const auto vTraceStart = pLocal->GetEyePosition();
		const auto vTraceEnd = vTraceStart + vTraceForward * 8192.0f;

		trace_t trace;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = pLocal;
		ray.Init(vTraceStart, vTraceEnd);
		g_EngineTrace->TraceRay(ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &trace);
		if (trace.fraction == 1.f)
			return false;

		auto target = static_cast<C_BaseEntity*>(trace.m_pEnt);
		if (!target || !target->IsAlive() || target->GetHealth() < 1 || target->HasGunGameImmunity())
			return false;

		if (target && target->GetTeamNum() == pLocal->GetTeamNum())
			return false;

		return true;
	}
};

extern Trigger trigger;