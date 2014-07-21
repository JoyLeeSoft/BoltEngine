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

#ifndef IWindow_h_
#define IWindow_h_

#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
#include <windows.h>
#endif

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "STL.h"
#include "CEventHandler.h"
#include "IScene.h"
#include "CSceneManager.h"

namespace BoltEngine
{
namespace Renderer
{

using namespace Manager;
using namespace Event;

class BOLTENGINE_API IWindow abstract
{
public:
	struct SCreationParams 
	{
	public:
		int Left, Top;
		unsigned int Width, Height;
		wstring Tilte;
		bool FullScreen;
	};

public:
	IWindow(const wstring &name);
	virtual ~IWindow();

protected:
	wstring m_Name;
	SCreationParams m_CreationParams;
	CSceneManager *m_SceneManager;

public:
	const wstring &GetName() const { return m_Name; }
	const SCreationParams &GetCreationParams() const { return m_CreationParams; }
	
public:
	struct SClosingEventArgs : public SEventArgs
	{
	public:
		bool Close;
	};
	CEventHandler<SClosingEventArgs> OnClosing;

	struct SClosedEventArgs : public SEventArgs { };
	CEventHandler<SClosedEventArgs> OnClosed;

	struct SIdleEventArgs : SEventArgs { };
	CEventHandler<SIdleEventArgs> OnIdle;

public:
	virtual void Initialize(const SCreationParams &param, IScene *scene) = 0;
	virtual void Destroy() = 0;

	virtual void *GetHandle() = 0;

	virtual void Begin() = 0;
	virtual void End() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ChangeScene(IScene *scene) = 0;

	virtual void SetCaption(const wstring &caption) = 0;

public:
#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
#endif
};

}
}

#endif