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

#include "../BoltEngine/CBoltEngine.h"
#include "../BoltEngine/CException.h"
#include "CWin32WindowPlugin.h"
#include "CWin32Window.h"

namespace BoltEngine
{
namespace Plugin
{

using namespace Exception;
using namespace Renderer;

CWin32WindowPlugin::CWin32WindowPlugin(const wstring &name, const wstring &description, 
	const CVersion &version) : IWindowPlugin(name, description, version)
{

}

CWin32WindowPlugin::~CWin32WindowPlugin()
{

}

bool CWin32WindowPlugin::Install()
{
	CBoltEngine::Get().GetPluginManager().InsertWindowFactoryPlugin(this);
	return true;
}

void CWin32WindowPlugin::Uninstall()
{
	CBoltEngine::Get().GetPluginManager().DeleteWindowFactoryPlugin(this);
}

IWindow *CWin32WindowPlugin::Create(const wstring &name, const IWindow::SCreationParams &param, IScene *scene)
{
	CWin32Window *window = new CWin32Window(name);
	window->Initialize(param, scene);

	return window;
}

}
}