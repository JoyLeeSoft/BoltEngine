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

#ifndef CWin32Window_h_
#define CWin32Window_h_

#include <windows.h>

#include "../BoltEngine/BoltConfigurationMacros.h"
#include "../BoltEngine/BoltUtilityMacros.h"
#include "../BoltEngine/IWindow.h"

namespace BoltEngine
{
namespace Renderer
{

class BOLTPLUGIN_API CWin32Window final : public IWindow
{
public:
	CWin32Window(const wstring &name);
	virtual ~CWin32Window();

private:
	bool m_IsInitialized;
	HWND m_hWnd;
	bool m_Loop;
	IScene *m_StartScene;

public:
	virtual void Initialize(const IWindow::SCreationParams &param, IScene *scene) override;
	virtual void Destroy() override;

	virtual void *GetHandle() override;

	virtual void Begin() override;
	virtual void End() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void ChangeScene(IScene *scene) override;

	virtual void SetCaption(const wstring &caption) override;
};

}
}

#endif