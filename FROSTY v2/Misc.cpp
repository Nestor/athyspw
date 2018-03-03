#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include <map>
#include "BaseClient.h"
#include "Strafer.h"
#include "LegitBot.h"

std::string animatedclantag;
int iLastTime;
bool bDone = false;

void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

	if (g_Options.Misc.Bhop && local->IsAlive())
	{
		if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
		{
			int iFlags = local->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;
		}
	}
}

static vec_t Normalize_y(vec_t ang)
{
	while (ang < -180.0f)
		ang += 360.0f;
	while (ang > 180.0f)
		ang -= 360.0f;
	return ang;
}

void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local, QAngle oldangles)
{
	static AutoStrafer Strafer;

	static float move = 450;
	float s_move = move * 0.5065f;
	if (local->GetMoveType() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER))
		return;
	if (cmd->buttons & (IN_FORWARD | IN_MOVERIGHT | IN_MOVELEFT | IN_BACK))
		return;

	if (cmd->buttons & IN_JUMP || !(local->GetFlags() & FL_ONGROUND))
	{
		if (local->GetVelocity().Length2D() == 0 && (cmd->forwardmove == 0 && cmd->sidemove == 0))
		{
			cmd->forwardmove = 450.f;
		}
		else if (cmd->forwardmove == 0 && cmd->sidemove == 0)
		{
			if (cmd->mousedx > 0 || cmd->mousedx > -0)
			{
				cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
			}
			else
			{
				auto airaccel = g_CVar->FindVar("sv_airaccelerate");
				auto maxspeed = g_CVar->FindVar("sv_maxspeed");

				static int zhop = 0;
				double yawrad = Normalize_y(oldangles.y) * PI / 180;

				float speed = maxspeed->GetFloat();
				if (cmd->buttons & IN_DUCK)
					speed *= 0.333;

				double tau = g_Globals->interval_per_tick, MA = speed * airaccel->GetFloat();

				int Sdir = 0, Fdir = 0;
				Vector velocity = local->GetVelocity();
				double vel[3] = { velocity[0], velocity[1], velocity[2] };
				double pos[2] = { 0, 0 };
				double dir[2] = { std::cos((oldangles[1] + 10 * zhop) * PI / 180), std::sin((oldangles[1] + 10 * zhop) * PI / 180) };
				oldangles.y = Normalize_y(yawrad * 180 / PI);
				Strafer.strafe_line_opt(yawrad, Sdir, Fdir, vel, pos, 30.0, tau, MA, pos, dir);
				cmd->sidemove = Sdir * 450;
			}
		}

	}
	movementfix(oldangles, cmd);
}


int gxaqonpeue() { int xciycxnxkbhngn = 6465; int wpelzxfgkr = 3037; int xpkatkujcyp = 8263; int cszflxoysyhlo = 6448; if (xciycxnxkbhngn = 7) { wpelzxfgkr = 3037; } int njtbzmhfcbmldz = 6448; int klmxoqbcnwbx = 8263; int qevduunctsfzdwr = 3037; int ceabimqgzo = 6465; int riwoowshphalv = 3037; int kkrefbggmajr = 8263; int scmmyoorzrey = 3037; return kkrefbggmajr; }
int qnvfktqsukb() { int xkmwodhrt = 5464; int iyueazalaod = 1605; int sfqgedjwixiee = 5768; int mhzxcdjgegfmn = 7637; if (xkmwodhrt = 7) { iyueazalaod = 1605; } int kouwllnaoolad = 7637; int swqeztaahsjoyk = 5768; int fldffhrrcrwpq = 1605; int bbfkffmjcwlmycu = 5464; int txwahpojlfxpag = 1605; int sqxlxvgfes = 5768; int cskeqxqraoof = 1605; return sqxlxvgfes; }
int nhwsplqonn() { int ooifntmocvhz = 6795; int axnalydvfhaa = 9799; int xqveahixtfrgvqz = 3309; int kxqgdoketi = 5747; if (ooifntmocvhz = 7) { axnalydvfhaa = 9799; } int rlmfrtpmowkc = 5747; int rkygtcqpboo = 3309; int ydduhfsycqhsxa = 9799; int ucpvvlfymnrsm = 6795; int wyzkzmnttlubma = 9799; int jovhqudvadonc = 3309; int coywjygksui = 9799; return jovhqudvadonc; }