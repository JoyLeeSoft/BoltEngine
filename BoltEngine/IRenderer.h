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

#ifndef IRenderer_h_
#define IRenderer_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "CColor.h"
#include "STL.h"
#include "IText.h"
#include "ITexture.h"

namespace BoltEngine
{
namespace Renderer
{

using namespace Utility;

#ifdef BOLTENGINE_PLATFORM_WIN32
#undef CreateWindow
#endif

class IWindow;

class BOLTENGINE_API IRenderer abstract
{
public:
	IRenderer(const wstring &name);
	virtual ~IRenderer();

protected:
	wstring m_Name;

public:
	const wstring &GetName() const { return m_Name; }

public:
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;

	virtual void BeginDraw(const CColor &color) = 0;
	virtual void EndDraw() = 0;

	virtual IText *CreateText(const wstring &font, const CColor &color, 
		IText::ETextStyle style, unsigned int size) = 0;
	virtual ITexture *CreateTexture(const wstring &filename) = 0;
};

}
}

#endif