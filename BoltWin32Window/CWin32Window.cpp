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

#ifdef _MSC_VER
#include "resource.h"
#endif

#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

#include "../BoltEngine/STL.h"
#include "../BoltEngine/IScene.h"
#include "../BoltEngine/CBoltEngine.h"
#include "../BoltEngine/CWindowManager.h"
#include "../BoltEngine/CException.h"

#include "CWin32Window.h"

namespace BoltEngine
{
namespace Renderer
{

using namespace Exception;
using namespace Renderer;

class CLogoScene final : public IScene
{
public:
	CLogoScene(const wstring &name, IScene *start_scene)
	{
		m_Name = name;
		m_StartScene = start_scene;
	}

private:
	IScene *m_StartScene;
	HWND m_hWnd;
	wstring m_Name;
	ULONG_PTR m_GPToken;
	unsigned int m_width, m_height;
	Gdiplus::Image *m_Logo;
	Gdiplus::Bitmap *m_MemoryBitmap;
	Gdiplus::Graphics *m_MemoryGraphic;
	HINSTANCE m_hInst;
	float m_Alpha;
	bool m_Up;
	CWin32Window *window;
	unsigned int m_W, m_Y;

public:
	virtual void OnCreate() override
	{
		window = (CWin32Window *)CBoltEngine::Get().GetWindowManager().GetByName(m_Name);
		m_hWnd = (HWND)window->GetHandle();
		m_width = window->GetCreationParams().Width;
		m_height = window->GetCreationParams().Height;
		m_hInst = GetModuleHandleW(L"BoltWin32Window");

		Gdiplus::GdiplusStartupInput gpsi;
		if (GdiplusStartup(&m_GPToken, &gpsi, NULL) != Gdiplus::Ok) {}

		HRSRC hResource = FindResourceW(m_hInst, MAKEINTRESOURCEW(IDB_LOGO),
			L"PNG");
		if (!hResource) return;

		DWORD imageSize = SizeofResource(m_hInst, hResource);
		HGLOBAL hGlobal = LoadResource(m_hInst, hResource);
		LPVOID pData = LockResource(hGlobal);

		HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
		LPVOID pBuffer = GlobalLock(hBuffer);
		CopyMemory(pBuffer, pData, imageSize);
		GlobalUnlock(hBuffer);

		IStream *pStream;
		HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);
		m_Logo = new Gdiplus::Image(pStream);
		pStream->Release();

		m_MemoryBitmap = new Gdiplus::Bitmap(m_width, m_height);
		m_MemoryGraphic = new Gdiplus::Graphics(m_MemoryBitmap);

		m_Alpha = 0.0f;
		m_Up = true;

		m_W = (m_width - m_Logo->GetWidth()) / 2;
		m_Y = (m_height - m_Logo->GetHeight()) / 2;
	}

	virtual void OnDestroy() override
	{
		delete m_Logo;
		delete m_MemoryGraphic;
		delete m_MemoryBitmap;
		Gdiplus::GdiplusShutdown(m_GPToken);
	}

	virtual void OnUpdate() override
	{
		m_Up ? m_Alpha += 0.03f : m_Alpha -= 0.03f;

		if (m_Alpha > 1.00f) m_Up = false;
		if (m_Alpha < 0.00f) window->ChangeScene(m_StartScene);
	}
	
	virtual void OnRender() override
	{
		Gdiplus::Graphics G(m_hWnd);
		Gdiplus::ImageAttributes imageAtt;
		Gdiplus::ColorMatrix colorMatrix = 
			{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, m_Alpha, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		
		imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault,
			Gdiplus::ColorAdjustTypeBitmap);
		m_MemoryGraphic->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color::Black), 0, 0, m_width, m_height);
		m_MemoryGraphic->DrawImage(m_Logo, Gdiplus::Rect(m_W, m_Y, m_Logo->GetWidth(), m_Logo->GetHeight()),
			0, 0, m_Logo->GetWidth(), m_Logo->GetHeight(), Gdiplus::UnitPixel, &imageAtt);
		G.DrawImage(m_MemoryBitmap, 0, 0);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	m_SceneManager->ChangeScene(new CLogoScene(m_Name, m_StartScene));

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
			Update();
			Render();
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

void CWin32Window::ChangeScene(IScene *scene)
{
	m_SceneManager->ChangeScene(scene);
}

void CWin32Window::SetCaption(const wstring &caption)
{
	SetWindowTextW(m_hWnd, caption.c_str());
}

}
}