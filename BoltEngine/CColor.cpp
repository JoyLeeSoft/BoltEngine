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

#include "CColor.h"
#include "BoltUtilityMacros.h"

namespace BoltEngine
{
namespace Utility
{
namespace
{
	const unsigned int RedShift = 24;
	const unsigned int GreenShift = 16;
	const unsigned int BlueShift = 8;
	const unsigned int AlphaShift = 0;
	const unsigned int RedMask = 0xff << RedShift;
	const unsigned int GreenMask = 0xff << GreenShift;
	const unsigned int BlueMask = 0xff << BlueShift;
	const unsigned int AlphaMask = 0xff << AlphaShift;
}

CColor::CColor(ColorType red /* = 255 */, ColorType green /* = 255 */, ColorType blue /* = 255 */, 
	ColorType alpha /* = 0 */) : m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha) 
{

}

CColor::CColor(const CColor &other)
{
	CHANGE_MEMBER_BEGIN(other)
		CHANGE_MEMBER(m_Alpha)
		CHANGE_MEMBER(m_Red)
		CHANGE_MEMBER(m_Green)
		CHANGE_MEMBER(m_Blue)
	CHANGE_MEMBER_END()
}

CColor::CColor(EColorKind hex_color)
{
	m_Red = ((hex_color & RedMask) >> RedShift);
	m_Green = ((hex_color & GreenMask) >> GreenShift);
	m_Blue = ((hex_color & BlueMask) >> BlueShift);
	m_Alpha = ((hex_color & AlphaMask) >> AlphaShift);
}

CColor::ColorType CColor::GetRed() const
{
	return m_Red;
}

CColor::ColorType CColor::GetGreen() const
{
	return m_Green;
}

CColor::ColorType CColor::GetBlue() const
{
	return m_Blue;
}

CColor::ColorType CColor::GetAlpha() const
{
	return m_Alpha;
}

unsigned int CColor::ToRGBA() const
{
	return (((m_Red & 0xff) << RedShift) |
		((m_Green & 0xff) << GreenShift) |
		((m_Blue & 0xff) << BlueShift) |
		(m_Alpha & AlphaShift));
}

unsigned int CColor::ToRGB() const
{
	return (((m_Red & 0xff) << GreenShift) |
		((m_Green & 0xff) << BlueShift) |
		((m_Blue & 0xff) << AlphaShift));
}

void CColor::ToFloatRGBA(float arr[4]) const
{
	unsigned int hex = ToRGBA();

	arr[0] = static_cast<float>((hex & RedMask) >> RedShift) / 255.f;
	arr[1] = static_cast<float>((hex & GreenMask) >> GreenShift) / 255.f;
	arr[2] = static_cast<float>((hex & BlueMask) >> BlueShift) / 255.f;
	arr[3] = static_cast<float>((hex & AlphaMask) >> AlphaShift) / 255.f;
}

}
}