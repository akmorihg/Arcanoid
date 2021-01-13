#pragma once
#pragma warning(disable : 4996)
#include <Windows.h>

// Функция для скрытия каретки
void CursorHide() {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get console handle
	hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);

	// Hide console cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hOUTPUT, &cursorInfo);
}

void SetColor(WORD wAttributes) {// функция для смена цвета
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOUTPUT, wAttributes);
}

// Функция для выбора позиции
void SetPos(int x, int y) {// функция для установки позиции каретки по координатам
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}



typedef BOOL(WINAPI* SETCONSOLEFONT)(HANDLE, DWORD);
typedef BOOL(WINAPI* SETCURRENTCONSOLEFONTEX)(HANDLE, BOOL, PCONSOLE_FONT_INFOEX);
SETCONSOLEFONT SetConsoleFont;


void start() {
	OSVERSIONINFOEX osvi;
	CONSOLE_FONT_INFOEX cfon;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO*)&osvi);
	HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");
	if (osvi.dwMajorVersion < 6) {
		SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
		if (!SetConsoleFont) { exit(1); }
		SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	}
	else
	{
		if (!SetCurrentConsoleFontEx) { exit(1); }
		ZeroMemory(&cfon, sizeof(CONSOLE_FONT_INFOEX));

		cfon.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfon.nFont = 5;
		cfon.FontFamily = 0;
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfon);
	}

	system("mode con cols=80 lines=50");
	system("cls");
	CursorHide();
}

