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

#ifndef CColor_h_
#define CColor_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"

namespace BoltEngine
{
namespace Utility
{

class CColor
{
public:
	enum EColorKind : unsigned int
	{
		AliceBlue = 0xF0F8FF00,
		AntiqueWhite = 0xFAEBD700,
		Aqua = 0x00FFFF00,
		Aquamarine = 0x7FFFD400,
		Azure = 0xF0FFFF00,
		Beige = 0xF5F5DC00,
		Bisque = 0xFFE4C400,
		Black = 0x00000000,
		BlanchedAlmond = 0xFFEBCD00,
		Blue = 0x0000FF00,
		BlueViolet = 0x8A2BE200,
		Brown = 0xA52A2A00,
		BurlyWood = 0xDEB88700,
		CadetBlue = 0x5F9EA000,
		Chartreuse = 0x7FFF0000,
		Chocolate = 0xD2691E00,
		Coral = 0xFF7F5000,
		CornflowerBlue = 0x6495ED00,
		Cornsilk = 0xFFF8DC00,
		Crimson = 0xDC143C00,
		Cyan = 0x00FFFF00,
		DarkBlue = 0x00008B00,
		DarkCyan = 0x008B8B00,
		DarkGoldenrod = 0xB8860B00,
		DarkGray = 0xA9A9A900,
		DarkGreen = 0x00640000,
		DarkKhaki = 0xBDB76B00,
		DarkMagenta = 0x8B008B00,
		DarkOliveGreen = 0x556B2F00,
		DarkOrange = 0xFF8C0000,
		DarkOrchid = 0x9932CC00,
		DarkRed = 0x8B000000,
		DarkSalmon = 0xE9967A00,
		DarkSeaGreen = 0x8FBC8F00,
		DarkSlateBlue = 0x483D8B00,
		DarkSlateGray = 0x2F4F4F00,
		DarkTurquoise = 0x00CED100,
		DarkViolet = 0x9400D300,
		DeepPink = 0xFF149300,
		DeepSkyBlue = 0x00BFFF00,
		DimGray = 0x69696900,
		DodgerBlue = 0x1E90FF00,
		Firebrick = 0xB2222200,
		FloralWhite = 0xFFFAF000,
		ForestGreen = 0x228B2200,
		Fuchsia = 0xFF00FF00,
		Gainsboro = 0xDCDCDC00,
		GhostWhite = 0xF8F8FF00,
		Gold = 0xFFD70000,
		Goldenrod = 0xDAA52000,
		Gray = 0x80808000,
		Green = 0x00800000,
		GreenYellow = 0xADFF2F00,
		Honeydew = 0xF0FFF000,
		HotPink = 0xFF69B400,
		IndianRed = 0xCD5C5C00,
		Indigo = 0x4B008200,
		Ivory = 0xFFFFF000,
		Khaki = 0xF0E68C00,
		Lavender = 0xE6E6FA00,
		LavenderBlush = 0xFFF0F500,
		LawnGreen = 0x7CFC0000,
		LemonChiffon = 0xFFFACD00,
		LightBlue = 0xADD8E600,
		LightCoral = 0xF0808000,
		LightCyan = 0xE0FFFF00,
		LightGoldenrodYellow = 0xFAFAD200,
		LightGreen = 0x90EE9000,
		LightGray = 0xD3D3D300,
		LightPink = 0xFFB6C100,
		LightSalmon = 0xFFA07A00,
		LightSeaGreen = 0x20B2AA00,
		LightSkyBlue = 0x87CEFA00,
		LightSlateGray = 0x77889900,
		LightSteelBlue = 0xB0C4DE00,
		LightYellow = 0xFFFFE000,
		Lime = 0x00FF0000,
		LimeGreen = 0x32CD3200,
		Linen = 0xFAF0E600,
		Magenta = 0xFF00FF00,
		Maroon = 0x80000000,
		MediumAquamarine = 0x66CDAA00,
		MediumBlue = 0x0000CD00,
		MediumOrchid = 0xBA55D300,
		MediumPurple = 0x9370DB00,
		MediumSeaGreen = 0x3CB37100,
		MediumSlateBlue = 0x7B68EE00,
		MediumSpringGreen = 0x00FA9A00,
		MediumTurquoise = 0x48D1CC00,
		MediumVioletRed = 0xC7158500,
		MidnightBlue = 0x19197000,
		MintCream = 0xF5FFFA00,
		MistyRose = 0xFFE4E100,
		Moccasin = 0xFFE4B500,
		NavajoWhite = 0xFFDEAD00,
		Navy = 0x00008000,
		OldLace = 0xFDF5E600,
		Olive = 0x80800000,
		OliveDrab = 0x6B8E2300,
		Orange = 0xFFA50000,
		OrangeRed = 0xFF450000,
		Orchid = 0xDA70D600,
		PaleGoldenrod = 0xEEE8AA00,
		PaleGreen = 0x98FB9800,
		PaleTurquoise = 0xAFEEEE00,
		PaleVioletRed = 0xDB709300,
		PapayaWhip = 0xFFEFD500,
		PeachPuff = 0xFFDAB900,
		Peru = 0xCD853F00,
		Pink = 0xFFC0CB00,
		Plum = 0xDDA0DD00,
		PowderBlue = 0xB0E0E600,
		Purple = 0x80008000,
		Red = 0xFF000000,
		RosyBrown = 0xBC8F8F00,
		RoyalBlue = 0x4169E100,
		SaddleBrown = 0x8B451300,
		Salmon = 0xFA807200,
		SandyBrown = 0xF4A46000,
		SeaGreen = 0x2E8B5700,
		SeaShell = 0xFFF5EE00,
		Sienna = 0xA0522D00,
		Silver = 0xC0C0C000,
		SkyBlue = 0x87CEEB00,
		SlateBlue = 0x6A5ACD00,
		SlateGray = 0x70809000,
		Snow = 0xFFFAFA00,
		SpringGreen = 0x00FF7F00,
		SteelBlue = 0x4682B400,
		Tan = 0xD2B48C00,
		Teal = 0x00808000,
		Thistle = 0xD8BFD800,
		Tomato = 0xFF634700,
		Turquoise = 0x40E0D000,
		Violet = 0xEE82EE00,
		Wheat = 0xF5DEB300,
		White = 0xFFFFFF00,
		WhiteSmoke = 0xF5F5F500,
		Yellow = 0xFFFF0000,
		YellowGreen = 0x9ACD3200,
	};

private:
	static const unsigned int RedShift = 24;
	static const unsigned int GreenShift = 16;
	static const unsigned int BlueShift = 8;
	static const unsigned int AlphaShift = 0;
	static const unsigned int RedMask = 0xff << RedShift;
	static const unsigned int GreenMask = 0xff << GreenShift;
	static const unsigned int BlueMask = 0xff << BlueShift;
	static const unsigned int AlphaMask = 0xff << AlphaShift;

public:
	typedef unsigned int ColorType;

public:
	CColor(ColorType red = 255, ColorType green = 255, ColorType blue = 255, ColorType alpha = 0) 
		: m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha) { }

	CColor(const CColor &other)
	{
		CHANGE_MEMBER_BEGIN(other)
			CHANGE_MEMBER(m_Alpha)
			CHANGE_MEMBER(m_Red)
			CHANGE_MEMBER(m_Green)
			CHANGE_MEMBER(m_Blue)
		CHANGE_MEMBER_END()
	}

	CColor(EColorKind hex_color)
	{
		m_Red = ((hex_color & RedMask) >> RedShift);
		m_Green = ((hex_color & GreenMask) >> GreenShift);
		m_Blue = ((hex_color & BlueMask) >> BlueShift);
		m_Alpha = ((hex_color & AlphaMask) >> AlphaShift);
	}

private:
	ColorType m_Red, m_Green, m_Blue, m_Alpha;

public:
	ColorType GetRed() const { return m_Red; }
	ColorType GetGreen() const { return m_Green; }
	ColorType GetBlue() const { return m_Blue; }
	ColorType GetAlpha() const { return m_Alpha; }

	unsigned int ToHex() const
	{
		unsigned a = (((m_Red & 0xff) << RedShift) | 
			((m_Green & 0xff) << GreenShift) | 
			((m_Blue & 0xff) << BlueShift) | 
			(m_Alpha & AlphaShift));
		return a;
	}

	void ToFloat4(float arr[4]) const
	{
		unsigned int hex = ToHex();

		arr[0] = static_cast<float>((hex & RedMask) >> RedShift) / 255.f;
		arr[1] = static_cast<float>((hex & GreenMask) >> GreenShift) / 255.f;
		arr[2] = static_cast<float>((hex & BlueMask) >> BlueShift) / 255.f;
		arr[3] = static_cast<float>((hex & AlphaMask) >> AlphaShift) / 255.f;
	}
};

}
}

#endif