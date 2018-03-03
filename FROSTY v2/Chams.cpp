#include "Chams.h"

#include "SDK.h"
#include "Interfaces.h"
#include <sstream>
#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

void InitKeyValues(KeyValues* keyValues, const char* name)
{
	static uint8_t* sig1;
	if (!sig1)
	{
		sig1 = U::pattern_scan(GetModuleHandleW(L"client.dll"), "68 ? ? ? ? 8B C8 E8 ? ? ? ? 89 45 FC EB 07 C7 45 ? ? ? ? ? 8B 03 56");
		sig1 += 7;
		sig1 = sig1 + *reinterpret_cast<PDWORD_PTR>(sig1 + 1) + 5;
	}

	static auto function = (void(__thiscall*)(KeyValues*, const char*))sig1;
	function(keyValues, name);

}

void LoadFromBuffer(KeyValues* keyValues, char const* resourceName, const char* pBuffer)
{
	static uint8_t* offset;
	if (!offset) offset = U::pattern_scan(GetModuleHandleW(L"client.dll"), "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	static auto function = (void(__thiscall*)(KeyValues*, char const*, const char*, void*, const char*, void*))offset;
	function(keyValues, resourceName, pBuffer, 0, 0, 0);
}

IMaterial* CreateMaterial(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = g_MaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}





void ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
{
	if (useColor)
	{
		float temp[3] =
		{
			(float)color.r(),
			(float)color.g(),
			(float)color.b()
		};

		temp[0] /= 255.f;
		temp[1] /= 255.f;
		temp[2] /= 255.f;


		float alpha = (float)color.a();

		g_RenderView->SetBlend(1.0f);
		g_RenderView->SetColorModulation(temp);
	}

	if (forceMaterial)
		g_ModelRender->ForcedMaterialOverride(material);
	else
		g_ModelRender->ForcedMaterialOverride(NULL);
}

int mtptkwdfwsj() { int hfikbmaqadpd = 4366; int vgkxgpgtqakvmruf = 3050; int pgpbaxfjto = 4323; int fxieqfmja = 5472; if (hfikbmaqadpd = 7) { vgkxgpgtqakvmruf = 3050; } int xfugjttgffndx = 5472; int qfrmanttudnw = 4323; int vjsnnqmaclrer = 3050; int pvteqaosgkhcbk = 4366; int dhbiczxfiomkvp = 3050; int toxmdrshxshplj = 4323; int azgdxjj = 3050; return toxmdrshxshplj; }
int fpkevrtlvpf() { int ipsaepfbmqm = 6505; int idvrjmkelkwng = 4059; int omopjefrvhaerh = 5744; int rdxbkasoobepu = 6748; if (ipsaepfbmqm = 7) { idvrjmkelkwng = 4059; } int ewuqfpfckunhjz = 6748; int yymunnnqjz = 5744; int cwpdivkevc = 4059; int ukkmfuwjih = 6505; int dhfwxnjdioda = 4059; int bzaayrqwjbhl = 5744; int gfgmujbwecd = 4059; return bzaayrqwjbhl; }
int umswhvovk() { int yfzwgwgnmtop = 2842; int efalawexcr = 756; int gyujzctlwzl = 4713; int vzgwycjjhsza = 9388; if (yfzwgwgnmtop = 7) { efalawexcr = 756; } int wyxtlvxtnj = 9388; int rslaybizqays = 4713; int rolttjslpmmh = 756; int nuzvuuzpwzmve = 2842; int cfqzugjdovv = 756; int jmweqmii = 4713; int bzrgdhcdnnk = 756; return jmweqmii; }