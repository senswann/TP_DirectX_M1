#pragma once
#include "App/pch.h"
#include <wrl/client.h>

namespace DXWindowDefaults
{
	//Default window size
	extern const UINT WIDTH;
	extern const UINT HEIGHT;

	//String identifier
	extern LPCWSTR CLASS_NAME;
	extern LPCWSTR INSTANCE_NAME;

	//Window Styling Windowed
	extern const DWORD WINDOW_DEFAULT_STYLE;
	extern const DWORD WINDOW_DEFAULT_EXSTYLE;

	//Window Styling Fullscreen
	extern const DWORD WINDOW_FULLSCREEN_STYLE;
	extern const DWORD WINDOW_FULLSCREEN_EXSTYLE;
}
namespace AYCDX {

	class WindowHandler {
	public:

		WindowHandler(const WindowHandler& InOther) = delete;
		WindowHandler& operator=(const WindowHandler& other) = delete;

		inline static WindowHandler& Get() { return Instance; };
		inline bool GetClose() { return m_shouldClose; };

		bool Init(/*Prametre*/);
		void Shutdown();

		void Update();

	private:

		ATOM m_wndClass = 0;
		HWND m_window = nullptr;

		//User action
		bool m_shouldClose = false;

		static LRESULT OnWindowMessage(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static WindowHandler Instance;
		WindowHandler() = default;
	};
}