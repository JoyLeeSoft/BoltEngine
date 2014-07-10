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

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "../Debug/BoltEngine")
#else
#pragma comment(lib, "../Release/BoltEngine")
#endif
#endif

#include "BoltD2D1RendererMain.h"
#include "CD2D1RendererPlugin.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Renderer)

using namespace Plugin;

CD2D1RendererPlugin *g_Plugin;

extern "C" BOLTPLUGIN_API void OnLibLoad()
{
	g_Plugin = new CD2D1RendererPlugin("BoltEngine Direct 2D version 1 renderer plugin", CVersion(1, 0, 0));
}

extern "C" BOLTPLUGIN_API void OnLibUnload()
{
	SAFE_DELETE(g_Plugin);
}

extern "C" BOLTPLUGIN_API IPlugin *GetPlugin()
{
	return g_Plugin;
}

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()