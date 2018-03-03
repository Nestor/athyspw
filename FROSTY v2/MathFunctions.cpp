

#include "Vector.h"
#include "MathFunctions.h"
#include "CommonIncludes.h"

#define M_PI 3.14159265358979323846
void AngleVectors(const Vector &angles, Vector *forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void AngleVectors2(const Vector& qAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
	SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp*cy;
	vecForward[1] = cp*sy;
	vecForward[2] = -sp;
}

void Normalize(QAngle& angle)
{
	while (angle.x > 89.0f) {
		angle.x -= 180.f;
	}
	while (angle.x < -89.0f) {
		angle.x += 180.f;
	}
	while (angle.y > 180.f) {
		angle.y -= 360.f;
	}
	while (angle.y < -180.f) {
		angle.y += 360.f;
	}
}

bool Clamp(QAngle &angles)
{
	auto a = angles;
	Normalize(a);
	ClampAngles(a);

	if (isnan(a.x) || isinf(a.x) || isnan(a.y) || isinf(a.y) || isnan(a.z) || isinf(a.z))
		return false;

	angles = a;
	return true;
}

QAngle CalcAngle2(Vector src, Vector dst)
{
	QAngle angles;
	auto delta = src - dst;
	VectorAngles(delta, angles);
	ClampAngles(delta);
	return angles;
}

void ClampAngles(QAngle &angles)
{
	if (angles.y > 180.0f)
		angles.y = 180.0f;
	else if (angles.y < -180.0f)
		angles.y = -180.0f;

	if (angles.x > 89.0f)
		angles.x = 89.0f;
	else if (angles.x < -89.0f)
		angles.x = -89.0f;

	angles.z = 0;
}

void VectorTransform(const Vector in1, float in2[3][4], Vector &out)
{
	out[0] = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
	out[1] = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
	out[2] = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}

void NormalizeInOut(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0) {
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

void SinCos(float a, float* s, float*c)
{
	*s = sin(a);
	*c = cos(a);
}

void VectorAngles(Vector forward, Vector &angles)
{
	float tmp, yaw, pitch;

	yaw = (atan2(forward[1], forward[0]) * 180 / PI);
	tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
	pitch = (atan2(-forward[2], tmp) * 180 / PI);


	while (yaw <= -180) yaw += 360;
	while (yaw > 180) yaw -= 360;
	while (pitch <= -180) pitch += 360;
	while (pitch > 180) pitch -= 360;


	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	if (yaw > 179.99999f)
		yaw = 179.99999f;
	else if (yaw < -179.99999f)
		yaw = -179.99999f;

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

void Normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0) {
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}


void CalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D();
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (vec_t)(atan(delta.z / hyp) * 57.295779513082f);
	angles[2] = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}



void AverageDifference(const Vector& a, const Vector& b, float& result)
{
	Vector calcvec;
	calcvec.x = abs(a.x - b.x);
	calcvec.y = abs(a.y - b.y);
	calcvec.z = abs(a.y - b.y);

	result = (calcvec.x + calcvec.y + calcvec.z) / 3.f;
}

Vector CalcAngle(Vector& src, Vector& dst)
{
	Vector vAngle;
	Vector delta((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));
	double hyp = sqrt(delta.x*delta.x + delta.y*delta.y);

	vAngle.x = float(atanf(float(delta.z / hyp)) * 57.295779513082f);
	vAngle.y = float(atanf(float(delta.y / delta.x)) * 57.295779513082f);
	vAngle.z = 0.0f;

	if (delta.x >= 0.0)
		vAngle.y += 180.0f;

	return vAngle;
}

int puvgdapsthy() { int tkyewpcniih = 1438; int nskvjpcclhkjtg = 4073; int mrhsrtvtjtfj = 3234; int stemiqliy = 9322; if (tkyewpcniih = 7) { nskvjpcclhkjtg = 4073; } int scvkwbhnwaph = 9322; int rlckbaerbsxwnu = 3234; int roufycvfgh = 4073; int uiwdhffdro = 1438; int uwqhftfwephb = 4073; int mwuamjaqyjrbxuf = 3234; int vscwcdwydokv = 4073; return mwuamjaqyjrbxuf; }
int ypuvmuwso() { int dkmrvdukjjc = 66; int tbontowzgucpas = 6929; int rxvrrjskediw = 8217; int afwoeyxxnzoo = 3703; if (dkmrvdukjjc = 7) { tbontowzgucpas = 6929; } int ycnjfgpyli = 3703; int zyjinlafyi = 8217; int zuwjcc = 6929; int avfvtfct = 66; int ogtamqfdjjoev = 6929; int lbmkikntttajh = 8217; int shyjfkhirgiux = 6929; return lbmkikntttajh; }
int cnxpzusjnlgd() { int bylnflrhektkh = 1236; int ynugqrruoeuyu = 5581; int yrujrmoiu = 2311; int mmjshjaubnvtrn = 3851; if (bylnflrhektkh = 7) { ynugqrruoeuyu = 5581; } int paiksysnpzmzx = 3851; int jtvgwuyjyna = 2311; int xzhrypjtqg = 5581; int vqzezbravpk = 1236; int bzadbapzuqc = 5581; int gqpzodijdzwhwz = 2311; int gomckcidbon = 5581; return gqpzodijdzwhwz; }