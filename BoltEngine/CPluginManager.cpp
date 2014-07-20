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
#include "IRenderer.h"
#include "CWindowManager.h"
#include "CRendererManager.h"

namespace BoltEngine
{
namespace Manager
{

using namespace Plugin;
using namespace Renderer;
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
		try
		{
			_shutdown_plugin(it);
		}
		catch (...)
		{
			//OutputDebugStringW(L"some f*** error...\n");
		}
	}

	m_Plugins.clear();
}

void CPluginManager::LoadPlugin(const wstring &name)
{
	if (m_Plugins.find(name) == m_Plugins.end())
	{
		CDynamicLib *plugin_lib = new CDynamicLib(name);
		
		try 
		{
			plugin_lib->Load();
		}
		catch (CFileLoadException &e)
		{
			delete plugin_lib;
			throw e;
		}
		
		OnLibLoadFuncPtr OnLibLoad = (OnLibLoadFuncPtr)plugin_lib->GetSymbol(L"OnLibLoad");
		if (OnLibLoad == nullptr)
			THROW_EXCEPTION(SystemException, _W(BOOST_CURRENT_FUNCTION), L"Could not found plugin entry point");
		OnLibLoad();

		GetPluginFuncPtr GetPlugin = (GetPluginFuncPtr)plugin_lib->GetSymbol(L"GetPlugin");
		if (GetPlugin == nullptr)
			THROW_EXCEPTION(SystemException, _W(BOOST_CURRENT_FUNCTION), L"Could not found plugin object");
		IPlugin *plugin = GetPlugin();

		if (!plugin->Install())
		{
			OnLibUnloadFuncPtr OnLibUnload = (OnLibUnloadFuncPtr)plugin_lib->GetSymbol(L"OnLibUnload");
			if (OnLibUnload)
				OnLibUnload();

			plugin_lib->Unload();
			delete plugin_lib;

			THROW_EXCEPTION(SystemException, _W(BOOST_CURRENT_FUNCTION), L"Could not install plugin");
		}

		m_Plugins[name] = { plugin_lib, plugin };
	} 
	else
	{
		THROW_EXCEPTION(ArgumentException, _W(BOOST_CURRENT_FUNCTION), L"Plugin \"" + name + L"\" is already loaded");
	}
}

void CPluginManager::UnloadPlugin(const wstring &name)
{
	auto it = m_Plugins.find(name);

	if (it != m_Plugins.end())
	{
		_shutdown_plugin(it);
		m_Plugins.erase(it);
	}
	else
	{
		THROW_EXCEPTION(ArgumentException, _W(BOOST_CURRENT_FUNCTION), L"Could not found Plugin \"" + name + L"\"");
	}
}

void CPluginManager::SetWindowFactoryPlugin(const wstring &name)
{
	auto it = find_if(m_WindowFactoryPlugins.begin(), m_WindowFactoryPlugins.end(), [name](IWindowPlugin *plugin)
	{
		return plugin->GetName() == name;
	});

	if (it != m_WindowFactoryPlugins.end())
	{
		m_WindowFactoryPlugin = *it;
	}
	else
	{
		THROW_EXCEPTION(ArgumentException, _W(BOOST_CURRENT_FUNCTION), L"Could not found plugin \"" + name + L"\"");
	}
}

void CPluginManager::SetRendererFactoryPlugin(const wstring &name)
{
	auto it = find_if(m_RendererFactoryPlugins.begin(), m_RendererFactoryPlugins.end(), [name](IRendererPlugin *plugin)
	{
		return plugin->GetName() == name;
	});

	if (it != m_RendererFactoryPlugins.end())
	{
		m_RendererFactoryPlugin = *it;
	}
	else
	{
		THROW_EXCEPTION(ArgumentException, _W(BOOST_CURRENT_FUNCTION), L"Could not found plugin \"" + name + L"\"");
	}
}

IWindow *CPluginManager::_create_window(const wstring &name, const IWindow::SCreationParams &param)
{
	if (m_WindowFactoryPlugin == nullptr)
		THROW_EXCEPTION(InvalidOperationException, _W(BOOST_CURRENT_FUNCTION), L"No active factory plugins");

	IWindow *window = m_WindowFactoryPlugin->Create(name, param);
	CWindowManager::Get()._insert_element(window);

	return window;
}

IRenderer *CPluginManager::_create_renderer(const wstring &name, IWindow *target_window)
{
	if (m_RendererFactoryPlugin == nullptr)
		THROW_EXCEPTION(InvalidOperationException, _W(BOOST_CURRENT_FUNCTION), L"No active factory plugins");

	IRenderer *renderer = m_RendererFactoryPlugin->Create(name, target_window);
	CRendererManager::Get()._insert_element(renderer);

	return renderer;
}

void CPluginManager::InsertWindowFactoryPlugin(IWindowPlugin *plugin)
{
	m_WindowFactoryPlugins.push_back(plugin);
}

void CPluginManager::DeleteWindowFactoryPlugin(IWindowPlugin *plugin)
{
	if (m_WindowFactoryPlugin == plugin)
		m_WindowFactoryPlugin = nullptr;

	m_WindowFactoryPlugins.remove(plugin);
}

void CPluginManager::InsertRendererFactoryPlugin(IRendererPlugin *plugin)
{
	m_RendererFactoryPlugins.push_back(plugin);
}

void CPluginManager::DeleteRendererFactoryPlugin(IRendererPlugin *plugin)
{
	if (m_RendererFactoryPlugin == plugin)
		m_RendererFactoryPlugin = nullptr;

	m_RendererFactoryPlugins.remove(plugin);
}

void CPluginManager::_shutdown_plugin(PluginMap::iterator &it)
{
	it->second.m_Plugin->Uninstall();

	auto plugin_lib = it->second.m_PluginLib;

	OnLibUnloadFuncPtr OnLibUnload = (OnLibUnloadFuncPtr)plugin_lib->GetSymbol(L"OnLibUnload");
	if (OnLibUnload == nullptr)
		THROW_EXCEPTION(SystemException, _W(BOOST_CURRENT_FUNCTION), L"Could not found plugin exit point");
	OnLibUnload();

	plugin_lib->Unload();
	delete plugin_lib;
}

}
}