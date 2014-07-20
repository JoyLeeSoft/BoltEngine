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

namespace BoltEngine
{
namespace Renderer
{

using namespace Exception;

CWin32Window::CWin32Window(const wstring &name) : IWindow(name), m_hWnd(0), m_Loop(false), m_IsInitialized(false)
{
	m_SceneManager = new CSceneManager();
}

CWin32Window::~CWin32Window()
{
	delete m_SceneManager;
	Destroy();
}

void CWin32Window::Initialize(const IWindow::SCreationParams &param, IScene *scene)
{
	m_CreationParams = param;
	m_StartScene = scene;

	if (!m_IsInitialized)
	{
		WNDCLASSW WndClass;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClass.hInstance = GetModuleHandle(nullptr);
		WndClass.lpfnWndProc = (WNDPROC)IWindow::WndProc;
		WndClass.lpszClassName = L"BoltEngine Win32 Window Class";
		WndClass.lpszMenuName = NULL;
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		if (RegisterClassW(&WndClass) == 0)
			THROW_EXCEPTION(WindowException, _W(BOOST_CURRENT_FUNCTION), L"Could not register window class");

		DWORD dwStyle = WS_OVERLAPPEDWINDOW;

		if (param.FullScreen)
			dwStyle |= WS_EX_TOPMOST;

		m_hWnd = CreateWindowW(L"BoltEngine Win32 Window Class", param.Tilte.c_str(), dwStyle,
			param.Left, param.Top, param.Width, param.Height,
			NULL, (HMENU)NULL, GetModuleHandle(nullptr), this);
		if (!m_hWnd)
		{
			UnregisterClassW(L"BoltEngine Win32 Window Class", GetModuleHandle(nullptr));
			THROW_EXCEPTION(WindowException, _W(BOOST_CURRENT_FUNCTION), L"Could not create window");
		}

		ShowWindow(m_hWnd, SW_SHOW);

		m_IsInitialized = true;
	}
	else
	{
		THROW_EXCEPTION(InvalidOperationException, _W(BOOST_CURRENT_FUNCTION), L"Window is already initialized");
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
		THROW_EXCEPTION(InvalidOperationException, _W(BOOST_CURRENT_FUNCTION), L"Window is already destroyed");
	}
}

void *CWin32Window::GetHandle()
{
	return (void *)m_hWnd;
}

void CWin32Window::Begin()
{
	MSG msg;

	m_Loop = true;
	m_SceneManager->ChangeScene(m_StartScene);

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
			SIdleEventArgs arg;
			arg.Sender = this;
			OnIdle(arg);
		}

		Sleep(1);
	}
}

void CWin32Window::End()
{
	m_Loop = false;
}

void CWin32Window::Update()
{
	m_SceneManager->Update();
}

void CWin32Window::Render()
{
	m_SceneManager->Render();
}

void CWin32Window::SetCaption(const wstring &caption)
{
	SetWindowTextW(m_hWnd, caption.c_str());
}

}
}