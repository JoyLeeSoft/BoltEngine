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

#ifndef CWindowManager_h_
#define CWindowManager_h_

#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
#include <windows.h>
#endif

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "Type.h"
#include "ISingleton.h"
#include "IWindow.h"
#include "IWindowPlugin.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Manager)

using namespace Renderer;
using namespace Utility;
using namespace Plugin;

class BOLTENGINE_API CWindowManager : public ISingleton<CWindowManager>
{
public:
	CWindowManager();
	~CWindowManager();

private:
	typedef list<IWindowPlugin *> WindowFactoryPluginList;
	WindowFactoryPluginList m_FactoryPlugins;

	IWindowPlugin *m_FactoryPlugin;

public:
	void InsertFactoryPlugin(IWindowPlugin *plugin);
	void DeleteFactoryPlugin(IWindowPlugin *plugin);

public:
	void SetFactoryPlugin(const wstring &name);

	IWindow *Create(const wstring &name, const IWindow::SCreationParams &param);

public:
#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
#endif
};

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()

#endif