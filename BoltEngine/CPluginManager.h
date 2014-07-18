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

#ifndef CPluginManager_h_
#define CPluginManager_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "ISingleton.h"
#include "STL.h"
#include "CDynamicLib.h"
#include "IPlugin.h"

namespace BoltEngine
{
namespace Manager
{

using namespace Plugin;
using namespace Utility;

class BOLTENGINE_API CPluginManager : public ISingleton<CPluginManager>
{
	SET_SINGLETON_THIS_CLASS(CPluginManager);

private:
	CPluginManager();
	~CPluginManager();

private:
	struct SPluginStruct
	{
	public:
		CDynamicLib *m_PluginLib;
		IPlugin *m_Plugin;
	};

	typedef map<wstring, SPluginStruct> PluginMap;
	PluginMap m_Plugins;

public:
	void LoadPlugin(const wstring &name);
	void UnloadPlugin(const wstring &name);

private:
	void _ShutdownPlugin(PluginMap::iterator &it);
};

}
}

#endif