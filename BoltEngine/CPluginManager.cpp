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

#include "CPluginManager.h"
#include "CDynamicLib.h"
#include "CException.h"
#include "IPlugin.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Plugin)

using namespace Exception;

namespace
{
	typedef void (*OnLibLoadFuncPtr)(void);
	typedef IPlugin *(*GetPluginFuncPtr)(void);
	typedef void (*OnLibUnloadFuncPtr)(void);
}

CPluginManager::CPluginManager()
{

}

CPluginManager::~CPluginManager()
{
	for (auto it = m_Plugins.begin(); it != m_Plugins.end(); it++)
	{
		_ShutdownPlugin(it);
	}

	m_Plugins.clear();
}

void CPluginManager::LoadPlugin(const string &name)
{
	if (m_Plugins.find(name) == m_Plugins.end())
	{
		CDynamicLib *plugin_lib = new CDynamicLib(name);
		plugin_lib->Load();
		
		OnLibLoadFuncPtr OnLibLoad = (OnLibLoadFuncPtr)plugin_lib->GetSymbol("OnLibLoad");
		if (OnLibLoad == nullptr)
			THROW_EXCEPTION(SystemException, BOOST_CURRENT_FUNCTION, "Could not found plugin entry point");
		OnLibLoad();

		GetPluginFuncPtr GetPlugin = (GetPluginFuncPtr)plugin_lib->GetSymbol("GetPlugin");
		if (GetPlugin == nullptr)
			THROW_EXCEPTION(SystemException, BOOST_CURRENT_FUNCTION, "Could not found plugin object");
		IPlugin *plugin = GetPlugin();

		if (!plugin->Install())
		{
			OnLibUnloadFuncPtr OnLibUnload = (OnLibUnloadFuncPtr)plugin_lib->GetSymbol("OnLibUnloaded");
			if (OnLibUnload)
				OnLibUnload();

			plugin_lib->Unload();
			SAFE_DELETE(plugin_lib);

			THROW_EXCEPTION(SystemException, BOOST_CURRENT_FUNCTION, "Could not install plugin");
		}

		switch (plugin->GetKind())
		{
		case EPluginKind::Renderer:
			
			break;

		default:
			break;
		}

		m_Plugins[name] = { plugin_lib, plugin };
	} 
	else
	{
		THROW_EXCEPTION(ArgumentException, BOOST_CURRENT_FUNCTION, "Plugin \"" + name + "\" is already loaded");
	}
}

void CPluginManager::UnloadPlugin(const string &name)
{
	auto it = m_Plugins.find(name);

	if (it != m_Plugins.end())
	{
		_ShutdownPlugin(it);
		m_Plugins.erase(it);
	}
	else
	{
		THROW_EXCEPTION(ArgumentException, BOOST_CURRENT_FUNCTION, "Could not found Plugin \"" + name + "\"");
	}
}

void CPluginManager::_ShutdownPlugin(PluginMap::iterator &it)
{
	it->second.m_Plugin->Uninstall();

	auto plugin_lib = it->second.m_PluginLib;

	OnLibUnloadFuncPtr OnLibUnload = (OnLibUnloadFuncPtr)plugin_lib->GetSymbol("OnLibUnloaded");
	if (OnLibUnload == nullptr)
		THROW_EXCEPTION(SystemException, BOOST_CURRENT_FUNCTION, "Could not found plugin exit point");
	OnLibUnload();

	plugin_lib->Unload();
	SAFE_DELETE(plugin_lib);
}

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()