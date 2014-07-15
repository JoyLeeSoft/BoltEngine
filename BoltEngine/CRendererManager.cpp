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

#include "CRendererManager.h"
#include "CException.h"

namespace BoltEngine
{
namespace Manager
{

using namespace Exception;

CRendererManager::CRendererManager() : m_FactoryPlugin(nullptr)
{

}

CRendererManager::~CRendererManager()
{

}

void CRendererManager::InsertFactoryPlugin(IRendererPlugin *plugin)
{
	m_FactoryPlugins.push_back(plugin);
}

void CRendererManager::DeleteFactoryPlugin(IRendererPlugin *plugin)
{
	if (m_FactoryPlugin == plugin)
		m_FactoryPlugin = nullptr;

	m_FactoryPlugins.remove(plugin);
}

void CRendererManager::SetFactoryPlugin(const wstring &name)
{
	auto it = find_if(m_FactoryPlugins.begin(), m_FactoryPlugins.end(), [name](IRendererPlugin *plugin)
	{
		return plugin->GetName() == name;
	});

	if (it != m_FactoryPlugins.end())
	{
		m_FactoryPlugin = *it;
	}
	else
	{
		THROW_EXCEPTION(ArgumentException, _W(BOOST_CURRENT_FUNCTION), L"Could not found plugin \"" + name + L"\"");
	}
}

IRenderer *CRendererManager::Create(IWindow *target_window)
{
	if (m_FactoryPlugin == nullptr)
		THROW_EXCEPTION(InvalidOperationException, _W(BOOST_CURRENT_FUNCTION), L"No active factory plugins");

	return m_FactoryPlugin->Create(target_window);
}

}
}