#include "Gen_App/Config/AppConfig.h"
#include <iostream>
#include <string>

#ifdef USE_DEBUG
    #include "App/Tools/Debug/AYCLog.h"
#endif

#include "App/Handler/WindowHandler.h"

using namespace AYCDX;
namespace DXwd = DXWindowDefaults;

WindowHandler WindowHandler::Instance = WindowHandler();

const UINT DXwd::WIDTH = 1920;
const UINT DXwd::HEIGHT = 1080;

LPCWSTR DXwd::CLASS_NAME = L"CLS_DirectX_Window";
LPCWSTR DXwd::INSTANCE_NAME = L"RenduCMake2024 ";

const DWORD DXwd::WINDOW_DEFAULT_STYLE = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
const DWORD DXwd::WINDOW_DEFAULT_EXSTYLE = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW;

const DWORD DXwd::WINDOW_FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
const DWORD DXwd::WINDOW_FULLSCREEN_EXSTYLE = WS_EX_APPWINDOW;

bool AYCDX::WindowHandler::Init() {
	// Pour pouvoir rajouter la version au nom de la window on converti la variable et l'ajoute
	std::wstring version_minor_str = std::to_wstring(VERSION_MINOR);
	std::wstring window_name_wide = DXwd::INSTANCE_NAME + version_minor_str;

	LPCWSTR window_name = window_name_wide.c_str();

	WNDCLASSEXW wcex
	{
		.cbSize = sizeof(wcex),
		.style = CS_OWNDC,
		.lpfnWndProc = &WindowHandler::OnWindowMessage,
		.cbClsExtra = 0, //Extra memory per Window Class, default = 0
		.cbWndExtra = 0, //Extra memory per Window Instance, default = 0
		.hInstance = GetModuleHandle(nullptr), //Instance ptr of owning app
		.hIcon = LoadIcon(nullptr, IDI_APPLICATION),
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = nullptr,
		.lpszMenuName = nullptr,
		.lpszClassName = DXwd::CLASS_NAME,
		.hIconSm = LoadIcon(nullptr, IDI_APPLICATION)
	};

	m_wndClass = RegisterClassExW(&wcex);

	if (m_wndClass == 0) {
		return false;
	}

	//get monitor current
	POINT pos{ 0,0 };
	GetCursorPos(&pos);
	HMONITOR monitor = MonitorFromPoint(pos, MONITOR_DEFAULTTOPRIMARY);

	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfoW(monitor, &monitorInfo);

	m_window = CreateWindowExW(
		DXwd::WINDOW_DEFAULT_EXSTYLE,
		(LPCWSTR)m_wndClass,
		window_name,
		DXwd::WINDOW_DEFAULT_STYLE,
		monitorInfo.rcWork.left + 100,
		monitorInfo.rcWork.top + 100,
		DXwd::WIDTH, DXwd::HEIGHT, nullptr, nullptr, wcex.hInstance, nullptr
	);
	if (m_window == nullptr)
	{
		return false;
	}
	return true;
}

void AYCDX::WindowHandler::Shutdown() {
	if (m_window) {
		DestroyWindow(m_window);
	}
	if (m_wndClass) {
		UnregisterClassW((LPCWSTR)m_wndClass, GetModuleHandleW(nullptr));
	}
}

void AYCDX::WindowHandler::Update()
{
	MSG msg;
	//true si le msg est en attente
	while (PeekMessage(&msg, m_window, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		//envoyer a OnWindowMessage
		DispatchMessageW(&msg);
	}
}

LRESULT AYCDX::WindowHandler::OnWindowMessage(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam){
	switch (msg)
	{
	case WM_CLOSE:
		Get().m_shouldClose = true;
		return 0;
	case WM_KEYDOWN: // message envoyé lorsqu'une touche est enfoncée
		#ifdef USE_DEBUG
		switch (wparam) {
		case 'Z':
			AYCLog::Log(LOG_DISPLAY, TEXT("Touche Z enfoncee"));
			return 0;
		case 'Q':
			AYCLog::Log(LOG_DISPLAY, TEXT("Touche Q enfoncee"));
			return 0;
		case 'S':
			AYCLog::Log(LOG_DISPLAY, TEXT("Touche S enfoncee"));
			return 0;
		case 'D':
			AYCLog::Log(LOG_DISPLAY, TEXT("Touche D enfoncee"));
			return 0;
		}
		#endif
	default:
		break;
	}
	return DefWindowProcW(wnd, msg, wparam, lparam);
}
