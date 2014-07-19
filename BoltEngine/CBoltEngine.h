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

#ifndef CBoltEngine_h_
#define CBoltEngine_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "CPluginManager.h"
#include "CWindowManager.h"
#include "CRendererManager.h"
#include "ISingleton.h"
#include "IWindow.h"
#include "IRenderer.h"

namespace BoltEngine
{

using namespace Utility;
using namespace Manager;
using namespace Renderer;

/**
 * @author Lee
 * @brief A main class of the BoltEngine
 */
class BOLTENGINE_API CBoltEngine : public ISingleton<CBoltEngine>
{
	SET_SINGLETON_THIS_CLASS(CBoltEngine);

private:
	CBoltEngine();
	~CBoltEngine();

public:
	/**
	 * @brief Getting plugin manager
	 * @return Instance of the plugin manager
	 * @code CPluginManager &plugin_manager = engine.GetPluginManager();
	 * @endcode
	 */
	CPluginManager &GetPluginManager();

	/**
	 * @brief Getting window manager
	 * @return Instance of the window manager
	 * @code CWindowManager &window_manager = engine.GetWindowManager();
	 * @endcode
	 */
	CWindowManager &GetWindowManager();

	/**
	 * @brief Getting renderer manager
	 * @return Instance of the renderer manager
	 * @code CRendererManager &renderer_manager = engine.GetRendererManager();
	 * @endcode
	 */
	CRendererManager &GetRendererManager();

	unsigned int GetFPS() const;

	IWindow *CreateWindow(const wstring &name, const IWindow::SCreationParams &param);
	IRenderer *CreateRenderer(const wstring &name, IWindow *target_window);
};

}

#endif