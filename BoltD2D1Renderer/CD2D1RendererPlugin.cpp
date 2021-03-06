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
#include "CD2D1RendererPlugin.h"
#include "CD2D1Renderer.h"

namespace BoltEngine
{
namespace Plugin
{

using namespace Exception;

CD2D1RendererPlugin::CD2D1RendererPlugin(const wstring &name, const wstring &description, const CVersion &version) 
	: IRendererPlugin(name, description, version)
{
	
}

CD2D1RendererPlugin::~CD2D1RendererPlugin()
{

}

bool CD2D1RendererPlugin::Install()
{
	CBoltEngine::Get().GetPluginManager().InsertRendererFactoryPlugin(this);
	return true;
}

void CD2D1RendererPlugin::Uninstall()
{
	CBoltEngine::Get().GetPluginManager().DeleteRendererFactoryPlugin(this);
}

IRenderer *CD2D1RendererPlugin::Create(const wstring &name, IWindow *target_window)
{
	CD2D1Renderer *renderer = new CD2D1Renderer(name, target_window);
	renderer->Initialize();

	return renderer;
}

}
}