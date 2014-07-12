// Copyright (c) 2014, Lee
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <boost/current_function.hpp>

#include "CWin32Window.h"
#include "../BoltEngine/CWindowManager.h"
#include "../BoltEngine/CException.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Renderer)

using namespace Exception;

CWin32Window::CWin32Window(const string &title) : IWindow(title), m_hWnd(0), m_Loop(false), m_IsInitialized(false)
{

}

CWin32Window::~CWin32Window()
{
	Destroy();
}

void CWin32Window::Initialize()
{
	if (!m_IsInitialized)
	{
		WNDCLASSW WndClass;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClass.hInstance = GetModuleHandle(nullptr);
		WndClass.lpfnWndProc = (WNDPROC)Manager::CWindowManager::WndProc;
		WndClass.lpszClassName = L"BoltEngine Win32 Window Class";
		WndClass.lpszMenuName = NULL;
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		if (RegisterClassW(&WndClass) == 0)
			THROW_EXCEPTION(WindowException, BOOST_CURRENT_FUNCTION, "Could not register window class");

		m_hWnd = CreateWindowA("BoltEngine Win32 Window Class", m_Name.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, (HMENU)NULL, GetModuleHandle(nullptr), NULL);
		if (!m_hWnd)
		{
			UnregisterClassA("BoltEngine Win32 Window Class", GetModuleHandle(nullptr));
			THROW_EXCEPTION(WindowException, BOOST_CURRENT_FUNCTION, "Could not create window");
		}

		ShowWindow(m_hWnd, SW_SHOW);
		m_IsInitialized = true;
	}
	else
	{
		THROW_EXCEPTION(InvalidOperationException, BOOST_CURRENT_FUNCTION, "Window is already initialized");
	}
}

void CWin32Window::Destroy()
{
	if (m_IsInitialized)
	{
		UnregisterClassW(L"BoltEngine Win32 Window Class", GetModuleHandle(nullptr));
	}
	else
	{
		THROW_EXCEPTION(InvalidOperationException, BOOST_CURRENT_FUNCTION, "Window is already destroyed");
	}
}

void CWin32Window::Begin()
{
	MSG msg;

	m_Loop = true;
	while (m_Loop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				End();
				continue;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
		}

		Sleep(1);
	}
}

void CWin32Window::End()
{
	m_Loop = false;
}

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()