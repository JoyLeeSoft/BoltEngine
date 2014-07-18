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

#include "../BoltEngine/BoltUtilityMacros.h"
#include "../BoltEngine/CException.h"
#include "../BoltEngine/IWindow.h"

#include "CD2D1Renderer.h"

namespace BoltEngine
{
namespace Renderer
{

using namespace Exception;

CD2D1Renderer::CD2D1Renderer(IWindow *target_window) : m_Factory(nullptr), m_RenderTarget(nullptr), 
	m_TargetWindow(target_window)
{

}

CD2D1Renderer::~CD2D1Renderer()
{
	Destroy();
}

void CD2D1Renderer::Initialize()
{
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory)))
		THROW_EXCEPTION(RendererException, _W(BOOST_CURRENT_FUNCTION), L"Could not create Direct 2D factory");

	auto param = m_TargetWindow->GetCreationParams();

	D2D1_SIZE_U size = D2D1::SizeU(param.Width, param.Height);

	if (FAILED(m_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties((HWND)
		m_TargetWindow->GetHandle(), size, D2D1_PRESENT_OPTIONS_IMMEDIATELY), &m_RenderTarget)))
	{
		SAFE_RELEASE(m_Factory);
		THROW_EXCEPTION(RendererException, _W(BOOST_CURRENT_FUNCTION), L"Could not create render target");
	}
}

void CD2D1Renderer::Destroy()
{
	SAFE_RELEASE(m_RenderTarget);
	SAFE_RELEASE(m_Factory);
}

void CD2D1Renderer::BeginDraw(const CColor &color)
{
	m_RenderTarget->BeginDraw();

	float arr[4];
	color.ToFloat4(arr);

	m_RenderTarget->Clear(D2D1::ColorF(arr[0], arr[1], arr[2], arr[3]));
}

void CD2D1Renderer::EndDraw()
{
	m_RenderTarget->EndDraw();
}

}
}