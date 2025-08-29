#include "Character.h"
#include "BHGui.h"
#include "ProcessManager.h"

ProcessManager pm(L"Souls.exe");
Character* character = nullptr;

void grow_pp()
{
	const static int pp_value = 100000;
	pm.WriteInt(reinterpret_cast<DWORD>(&character->NegativePP), -pp_value);
	pm.WriteInt(reinterpret_cast<DWORD>(&character->PP), pp_value);
	pm.WriteInt(reinterpret_cast<DWORD>(&character->NegativeGoldPieces), -pp_value * 10);
	pm.WriteInt(reinterpret_cast<DWORD>(&character->GoldPieces), pp_value * 10);
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow
)
{
	DWORD character_pointer;
	if (pm.Read(reinterpret_cast<LPCVOID>(PLAYER_BASE), &character_pointer, sizeof(character_pointer)) == 0) {
		return 1;
	}

	character = (Character*)character_pointer;

	BHGui gui{ "Bobby Hill's Gold and PP Trainer", 450, 200 };
	gui.Run(grow_pp);
	return 0;
}