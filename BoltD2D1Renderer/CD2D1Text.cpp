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

#include "CD2D1Text.h"
#include "../BoltEngine/CException.h"

namespace BoltEngine
{
namespace Renderer
{

using namespace Exception;

CD2D1Text::CD2D1Text(CD2D1Renderer *renderer, const wstring &font, const CColor &color,
	ETextStyle style, unsigned int size)
{
	m_RenderTarget = renderer->GetRenderTarget();
	m_DWFactory = renderer->GetDWriteFactory();

	if (FAILED(m_DWFactory->CreateTextFormat(font.c_str(), 0, DWRITE_FONT_WEIGHT_NORMAL,
		(DWRITE_FONT_STYLE)style, DWRITE_FONT_STRETCH_NORMAL, (FLOAT)size, L"", &m_Format)))
		THROW_EXCEPTION(RendererException, _W(BOOST_CURRENT_FUNCTION), L"Could not create DirectWrite text");

	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(color.ToRGB()), &m_Brush);
	m_RenderTargetSize = m_RenderTarget->GetSize();
}

CD2D1Text::~CD2D1Text()
{
	SAFE_RELEASE(m_Brush);
	SAFE_RELEASE(m_Format);
	SAFE_RELEASE(m_DWFactory);
	SAFE_RELEASE(m_RenderTarget);
}

void CD2D1Text::SetColor(const CColor &color)
{
	m_Brush->SetColor(D2D1::ColorF(color.ToRGB()));
}

void CD2D1Text::Render(const wstring &str, int x, int y)
{
	m_RenderTarget->DrawTextA(str.c_str(), str.size(), m_Format,
		D2D1::RectF((float)x, (float)y, m_RenderTargetSize.width, m_RenderTargetSize.height), m_Brush);
}

}
}