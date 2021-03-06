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

#include <iostream>

#include "CBoltEngine.h"
#include "CLog.h"

namespace BoltEngine
{

using namespace Log;

CBoltEngine::CBoltEngine()
{
	CLog::Get();
	SetLogStream(&wclog);
	CPluginManager::Get();
	CWindowManager::Get();
	CRendererManager::Get();

	//LOG(Information, L"Created engine");
}

CBoltEngine::~CBoltEngine()
{
	CRendererManager::Delete();
	CWindowManager::Delete();
	CPluginManager::Delete();

	LOG(Information, L"Destroyed engine");
	CLog::Delete();
}

CPluginManager &CBoltEngine::GetPluginManager()
{
	return CPluginManager::Get();
}

CWindowManager &CBoltEngine::GetWindowManager()
{
	return CWindowManager::Get();
}

CRendererManager &CBoltEngine::GetRendererManager()
{
	return CRendererManager::Get();
}

unsigned int CBoltEngine::GetFPS() const
{
	static int PreTick;
	static int NowTick = GetTickCount();
	static float FrameTime, Tick = 0;
	static int Count = 0;
	static int FPS = 0;

	PreTick = NowTick;
	NowTick = GetTickCount();

	FrameTime = (NowTick - PreTick) * 0.001f;
	Tick += FrameTime;

	Count++;

	if (Tick >= 1.0f)
	{
		Tick -= 1.0f;
		FPS = Count;
		Count = 0;
	}

	return FPS;
}

IWindow *CBoltEngine::CreateWindow(const wstring &name, const IWindow::SCreationParams &param, IScene *scene)
{
	LOG(Information, L"Created window");
	return GetPluginManager()._create_window(name, param, scene);
}

IRenderer *CBoltEngine::CreateRenderer(const wstring &name, IWindow *target_window)
{
	LOG(Information, L"Created renderer");
	return GetPluginManager()._create_renderer(name, target_window);
}

void CBoltEngine::SetLogStream(wostream *stream)
{
	CLog::Get().SetLogStream(stream);
}

}