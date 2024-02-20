#include <sdk/HaggleSDK.hpp> //for deluxe
#include <sdk/SexySDK.hpp> //for deluxe
#include <sdk/SexyNightsSDK.hpp> //for nights
#include <MinHook.h>
#include <utils/memory.hpp>

void init()
{
	MH_Initialize();
	ini_t* ini;

	//This runs before the mod loader switches the directory back, maybe look into a mod init import function eventually for haggle
	if (!std::filesystem::exists("mods/strmgr.ini"))
	{
		//Check again because the file path changes
		if (!std::filesystem::exists("mods/strmgr.ini"))
		{
			std::printf("%s\n", std::filesystem::current_path().string().c_str());
			const char* ini_default = ""
				"[skill-shot]\n"
				"extreme = Extreme!\n"
				"tubular = Tubular!\n"
				"radical = Radical!\n"
				"awesome = Awesome!\n"
				"insane = Insane!\n"
				"freakout = Freak Out!\n"
				"whoa = Whoa...\n"
				"wicked = Wicked!\n"
				"madskills = Mad Skills!\n"
				"excellent = Excellent!\n"
				"rockon = Rock On!\n"
				"toasty Toasty!\n"

				"[abilities]\n"
				"superguide = Super Guide\n"
				"flippers = Flippers\n"
				"multiball = Multiball!\n"
				"pyramid = Pyramid\n"
				"spaceblast = SpaceBlast!\n"
				"spookyball = SpookyBall\n"
				"zenshot = ZenBall\n"
				"flowerpower = FlowerPower!\n"
				"fireball = Fireball\n"
				"electrobolt = Electrobolt\n"
			;

			ini = ini_create(ini_default, strlen(ini_default));
			ini_save(ini, "mods/strmgr.ini");
		}
	}
	else if (std::filesystem::exists("mods/strmgr.ini"))
	{
		ini = ini_load("mods/strmgr.ini");
	}

	switch (Haggle::get_game_version())
	{
		case Haggle::PeggleVersion::Deluxe101:
		{
		}

		case Haggle::PeggleVersion::NightsDeluxe10:
		{
			set(0x0046EE29 + 0x1, ini_get(ini, "abilities", "superguide"));
			set(0x0046EE78 + 0x1, ini_get(ini, "abilities", "flippers"));
			set(0x0046EA76 + 0x3, ini_get(ini, "abilities", "multiball"));
			set(0x0046EECC + 0x1, ini_get(ini, "abilities", "pyramid"));
			set(0x0046EA86 + 0x3, ini_get(ini, "abilities", "spaceblast"));
			set(0x0046EC45 + 0x1, ini_get(ini, "abilities", "spookyball"));
			set(0x0046ECE6 + 0x1, ini_get(ini, "abilities", "zenshot"));
			set(0x0046EAA6 + 0x3, ini_get(ini, "abilities", "flowerpower"));
			set(0x0046ED6D + 0x1, ini_get(ini, "abilities", "fireball"));
			set(0x0046ED6D + 0x1, ini_get(ini, "abilities", "electrobolt"));

			set(0x0045A21E + 0x2, ini_get(ini, "skillshot", "extreme"));
			set(0x0045A225 + 0x2, ini_get(ini, "skillshot", "tubular"));
			set(0x0045A22C + 0x2, ini_get(ini, "skillshot", "radical"));
			set(0x0045A233 + 0x2, ini_get(ini, "skillshot", "awesome"));
			set(0x0045A23A + 0x2, ini_get(ini, "skillshot", "insane"));
			set(0x0045A241 + 0x2, ini_get(ini, "skillshot", "freakout"));
			set(0x0045A248 + 0x2, ini_get(ini, "skillshot", "whoa"));
			set(0x0045A24F + 0x2, ini_get(ini, "skillshot", "wicked"));
			set(0x0045A256 + 0x2, ini_get(ini, "skillshot", "madskills"));
			set(0x0045A25D + 0x2, ini_get(ini, "skillshot", "excellent"));
			set(0x0045A264 + 0x2, ini_get(ini, "skillshot", "tockon"));
			set(0x0045A26B + 0x2, ini_get(ini, "skillshot", "toasty"));
		}
	}
	
	MH_EnableHook(MH_ALL_HOOKS);
}

DWORD WINAPI OnAttachImpl(LPVOID lpParameter)
{
	init();
	return 0;
}

DWORD WINAPI OnAttach(LPVOID lpParameter)
{
	__try
	{
		return OnAttachImpl(lpParameter);
	}
	__except (0)
	{
		FreeLibraryAndExitThread((HMODULE)lpParameter, 0xDECEA5ED);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, OnAttach, hModule, 0, nullptr);
		return true;
	}

	return false;
}
