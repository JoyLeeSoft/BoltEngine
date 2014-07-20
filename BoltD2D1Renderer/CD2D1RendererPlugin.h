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

#ifndef CD2D1RendererPlugin_h_
#define CD2D1RendererPlugin_h_

#include "../BoltEngine/BoltConfigurationMacros.h"
#include "../BoltEngine/BoltUtilityMacros.h"
#include "../BoltEngine/IRendererPlugin.h"
#include "CD2D1Renderer.h"

namespace BoltEngine
{
namespace Plugin
{

using namespace Renderer;

class BOLTPLUGIN_API CD2D1RendererPlugin final : public IRendererPlugin
{
public:
	CD2D1RendererPlugin(const wstring &name, const wstring &description, const CVersion &version);
	virtual ~CD2D1RendererPlugin();

public:
	virtual bool Install() override;
	virtual void Uninstall() override;

	virtual IRenderer *Create(const wstring &name, IWindow *target_window) override;
};

}
}

#endif