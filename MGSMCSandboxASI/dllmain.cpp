#include "pch.h"
#include <string>
using namespace std;
DWORD64 baseAddress;
template<typename T>
void Write(uintptr_t writeAddress, T value)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)(writeAddress), sizeof(T), PAGE_EXECUTE_WRITECOPY, &oldProtect);
	*(reinterpret_cast<T*>(writeAddress)) = value;
	VirtualProtect((LPVOID)(writeAddress), sizeof(T), oldProtect, &oldProtect);
}

void ReplaceText(DWORD64 codeOffset, std::string newText, int maxLength = 128) {
	DWORD64 codeLoc = codeOffset + baseAddress;
	for (size_t i = 0; i < maxLength; ++i) Write((codeLoc + i), (i <= newText.length() ? newText[i] : ' '));
}
DWORD WINAPI Start(LPVOID lpParam)
{
	baseAddress = (DWORD64)GetModuleHandle(NULL);
	if (baseAddress == NULL) return 0;
	//ZIP: Waits until MGS3 is running!
	std::string strExeName;
	char chExeName[MAX_PATH];
	while (strExeName.find("METAL GEAR SOLID3.exe") == std::string::npos) {
		GetModuleFileNameA(nullptr, chExeName, MAX_PATH);
		strExeName = chExeName;
		Sleep(5000);
	}
	ReplaceText(0x88C370, "KA-BAR:\nA combat and utility knife that has a\n7-inch 1095 carbon steel clip point\nblade and leather handle.", 126);
	ReplaceText(0x894520, "Mk22:\nA modified version of the Smith &\nWesson 39 handgun that fires\ntranquilizer rounds.", 92);
	ReplaceText(0x8945E0, "XM16E1:\nA modified variant of the M16\nwhich featured improvements\nsuch as forward assist and\nchrome bolt carrier.", 124);
	ReplaceText(0x8801F0, "RGD-5:\nA grenade containing 110g of TNT.\nReleases up to 350 fragments\nwithin 25 meters.", 92);
	ReplaceText(0x8AAB30, "SVD:\nA semi-automatic sniper rifle\nchambered in the fully-powered\n7.62×54mmR cartridge.", 108);
	ReplaceText(0x8AAA70, "Ithaca 37:\nA sawn-off, pump-action shotgun\nthat carries four 12 gauge shells.", 94);
	ReplaceText(0x8AA9F0, "AK-47:\nA gas-operated assault rifle that is\nchambered for the 7.62×39mm\ncartridge.", 124);
	ReplaceText(0x894580, "M1911A1:\nA variant of the M1911 with a\nshorter trigger and longer\nsafety grip.", 92);
	ReplaceText(0x8AAC20, "RPG-7:\nA portable, reusable, unguided,\nshoulder-launched, anti-tank,\nrocket-propelled grenade launcher.", 124);
	ReplaceText(0x8AABA0, "M91/30:\nA modified variant of the M1891\nbolt-action rifle that fires tranquilizer\nrounds.", 124);
	ReplaceText(0x8898B0, "Sa vz. 61:\nA 32. caliber compact Czech\nsubmachine gun/machine pistol\nthat's equipped with a laser sight.", 128);
	ReplaceText(0x874CA0, "Colt Single Action Army:\nA single-action revolver handgun\nthat holds six rounds of .45 Colt\nammo.", 114);
	ReplaceText(0x884400, "Stoner 63:\nA 5.56×45mm modular weapon\nsystem with LMG configuration.", 89);
	ReplaceText(0x887070, "Patriot:\nA modified version of the XM16E1\nwith stock removed, shortened\nbarrel and ∞-shaped drum mag.", 128);
	ReplaceText(0x87AFB0, "Chaff Grenade:\nA grenade that consists of small\naluminum strips that are designed\nto confuse radar frequencies.", 124);
	ReplaceText(0x88E3F0, "M15:\nA white phosphorous grenade\nthat's been fitted with a Soviet \nUZRGM fuze.", 124);
	ReplaceText(0x88B3B0, "Smoke Grenade:\nA grenade that releases a thick\ngreyish-white smoke that can\nconceal you from enemies.", 126);
	ReplaceText(0x88C280, "Stun Grenade:\nA grenade that produces a blinding\nflash of light and extremely loud\nbang, stunning enemies.", 125);
	ReplaceText(0x8AAD00, "TNT:\nA remote-detonated explosive used\nto ambush enemies and demolish\nstorage areas.", 100);
	ReplaceText(0x8AAE40, "Claymore:\nA directional anti-personnel mine\nthat fires steel balls when front\nsensor is tripped.", 108);
	return 0;
}
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DWORD dwThreadId, dwThrdParam = 1;
		HANDLE hThread;
		hThread = CreateThread(NULL, 0, Start, &dwThrdParam, 0, &dwThreadId);
	}
	return 1;
}