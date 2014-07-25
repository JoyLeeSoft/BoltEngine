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

#include <boost/scope_exit.hpp>

#include "../BoltEngine/CException.h"

#include "CD2D1Texture.h"

#include <sstream>



namespace BoltEngine
{
namespace Renderer
{

using namespace Exception;

CD2D1Texture::CD2D1Texture(CD2D1Renderer *renderer, const wstring &filename)
{
	m_RenderTarget = renderer->GetRenderTarget();
	m_WICFactory = renderer->GetWICFactory();

	IWICBitmapDecoder *decoder = nullptr;
	IWICBitmapFrameDecode *frame = nullptr;
	IWICFormatConverter *converter = nullptr;

	BOOST_SCOPE_EXIT((decoder)(frame)(converter))
	{
		SAFE_RELEASE(converter);
		SAFE_RELEASE(frame);
		SAFE_RELEASE(converter);
	}
	BOOST_SCOPE_EXIT_END

	HRESULT hr = m_WICFactory->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder);
	if (FAILED(hr))
		THROW_EXCEPTION(FileLoadException, _W(BOOST_CURRENT_FUNCTION), L"Could not load texture file \""
			+ filename + L"\"\nHRESULT code : " + BoltEngine::Exception::HResultToString(hr));

	hr = decoder->GetFrame(0, &frame);
	if (FAILED(hr))
		THROW_EXCEPTION(RendererException, _W(BOOST_CURRENT_FUNCTION), L"Could not create decoder\n"
			L"HRESULT code : " + BoltEngine::Exception::HResultToString(hr));

	hr = m_WICFactory->CreateFormatConverter(&converter);
	if (FAILED(hr))
		THROW_EXCEPTION(RendererException, _W(BOOST_CURRENT_FUNCTION), L"Could not create format converter\n"
			L"HRESULT code : " + BoltEngine::Exception::HResultToString(hr));

	hr = converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
		nullptr, 0.0, WICBitmapPaletteTypeCustom);
	if (FAILED(hr))
		THROW_EXCEPTION(RendererException, _W(BOOST_CURRENT_FUNCTION), L"Could not initialization format converter\n"
			L"HRESULT code : " + BoltEngine::Exception::HResultToString(hr));

	m_RenderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &m_Bitmap);
}

CD2D1Texture::~CD2D1Texture()
{
	SAFE_RELEASE(m_Bitmap);
	SAFE_RELEASE(m_WICFactory);
	SAFE_RELEASE(m_RenderTarget);
}

void CD2D1Texture::Render(unsigned int x, unsigned int y)
{
	m_RenderTarget->DrawBitmap(m_Bitmap, D2D1::RectF((float)x, (float)y, (float)m_Bitmap->GetSize().width,
		(float)m_Bitmap->GetSize().height));
}

}
}