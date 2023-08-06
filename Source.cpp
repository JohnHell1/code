#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif


#include<string>
#include<Windows.h>
#include<CommCtrl.h>

HMENU menubas,altmenu;
using namespace std;
HINSTANCE g_Instance;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND mywindow,button,combobox,tooltip;
LPCWSTR myclass[] = { L"tten" ,L"amk"};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpArgument, int nCmdShow) {
	MSG message;
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = NULL;
	wnd.lpszClassName = myclass[0];
	wnd.lpszMenuName = NULL;
	wnd.lpfnWndProc = WndProc;
	wnd.hInstance = hInstance;


	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	


	if (!RegisterClassEx(&wnd))return 0;


	mywindow = CreateWindowEx(0, myclass[0], L"mywindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);
	g_Instance = hInstance;
	ShowWindow(mywindow, nCmdShow);
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
	return message.wParam;
}

LPCWSTR mystrings[] = {L"AHMET",L"MEHMET",L"YOK",L""};
LPCWSTR emptyaa = L"";
string getsrt;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_CREATE:

		combobox = CreateWindow(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBN_DROPDOWN | CBS_HASSTRINGS, 0, 0, 100, 100, hwnd, NULL, NULL, NULL);

		menubas = CreateMenu();
		altmenu = CreateMenu();
		AppendMenu(menubas, MF_STRING, 104, L"&TTEN");
		AppendMenu(menubas, MF_STRING, 104, L"&zTEN");
		AppendMenu(altmenu, MF_POPUP, (UINT_PTR)menubas, L"Atten");
		SetMenu(hwnd, altmenu);
		tooltip = CreateWindowEx(0, TOOLTIPS_CLASS, L"", TTS_ALWAYSTIP | WS_POPUP | WS_VISIBLE, CW_DEFAULT, CW_DEFAULT, CW_DEFAULT, CW_DEFAULT, hwnd, NULL, g_Instance, NULL);


		TOOLINFO tti = { 0 };
		tti.cbSize = sizeof(TOOLINFO);
		tti.hinst = g_Instance;
		tti.hwnd = hwnd;
		tti.uId = (UINT_PTR)combobox;
		tti.lpszText = (LPWSTR)L"GÖTTEN";
		tti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;


		SendMessageW(tooltip, TTM_ADDTOOL, 0, (LPARAM)&tti);

		SendMessageW(tooltip, TTM_ACTIVATE, TRUE, NULL);
		for (int i = 0; strcmp((const char*)mystrings[i], (const char*)emptyaa); i++) {
			SendMessageW(combobox, CB_ADDSTRING, 0, (LPARAM)mystrings[i]);
		}

		

		break;

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			int mesaj = SendMessageW(combobox, CB_GETCURSEL, 0, 0);

			SendMessageW(combobox, CB_GETLBTEXT, (WPARAM)mesaj, (LPARAM)getsrt.c_str());
			MessageBoxEx(hwnd, (LPCWSTR)getsrt.c_str(), L"pırt", MB_OKCANCEL,NULL);
		}
		
		
		break;
	case WM_DRAWITEM:

		switch ((UINT)wParam)
		{
		case 101:



			break;

		}
		break;
	
	
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}