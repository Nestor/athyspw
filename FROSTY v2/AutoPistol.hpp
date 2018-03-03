#pragma once
#include "Entities.h"
#include "Configuration.hpp"
#include "Variables.h"
#include "Interfaces.h"
#include "MiscClasses.h"

class AutoPistol
{
public:
	AutoPistol()
	{
		m_bLMBDown = false;
		m_bRMBDown = false;
	}

	void CreateMove_Post(C_BaseEntity* pLocal, CInput::CUserCmd* pCmd) const
	{
		if (g_Options.Menu.Opened)
			return;

		auto pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
		if (!pWeapon || !MiscFunctions::IsPistol(pWeapon) || pWeapon->ammo() == 0)
			return;

		const auto isRevolver = *pWeapon->ItemDefinitionIndex() == WEAPON_REVOLVER;
		if (isRevolver && !m_bRMBDown || !isRevolver && !m_bLMBDown)
			return;

		const auto curtime = pLocal->GetTickBase() * g_Globals->interval_per_tick;
		if (pWeapon->GetNextPrimaryAttack() >= curtime || pLocal->GetNextAttack() >= curtime)
			pCmd->buttons &= isRevolver ? ~IN_ATTACK2 : ~IN_ATTACK;
		else
			pCmd->buttons |= isRevolver ? IN_ATTACK2 : IN_ATTACK;
	}

	void CheckToggle(bool vecPressedKeys[256])
	{
		m_bLMBDown = vecPressedKeys[VK_LBUTTON];
		m_bRMBDown = vecPressedKeys[VK_RBUTTON];
	}

private:
	bool m_bLMBDown;
	bool m_bRMBDown;
};

extern AutoPistol apist;