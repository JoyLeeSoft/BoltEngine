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

#ifndef CD2D1Renderer_h_
#define CD2D1Renderer_h_

#include <d2d1.h>

#include "../BoltEngine/BoltConfigurationMacros.h"
#include "../BoltEngine/BoltUtilityMacros.h"
#include "../BoltEngine/IRenderer.h"

namespace BoltEngine
{
namespace Renderer
{

class BOLTPLUGIN_API CD2D1Renderer final : public IRenderer
{
public:
	CD2D1Renderer(const wstring &name, IWindow *target_window);
	virtual ~CD2D1Renderer();

private:
	IWindow *m_TargetWindow;
	ID2D1Factory *m_Factory;
	ID2D1HwndRenderTarget *m_RenderTarget;

public:
	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void BeginDraw(const CColor &color) override;
	virtual void EndDraw() override;
};

}
}

#endif