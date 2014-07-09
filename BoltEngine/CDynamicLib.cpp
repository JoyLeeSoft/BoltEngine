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

#include "CDynamicLib.h"
#include "CException.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Plugin)

using namespace Exception;

CDynamicLib::CDynamicLib(const CString &name) : m_IsLoaded(false), m_LibName(name), m_LibHandle(0)
{
	
}

CDynamicLib::~CDynamicLib()
{

}

void CDynamicLib::Load()
{
	CString name = m_LibName;
#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
	if (name.substr(name.length() - 4, 4) != ".dll")
		name += ".dll";
#endif

	m_LibHandle = DYNAMIC_LIB_LOAD(m_LibName.c_str());

	if (!m_LibHandle)
		THROW_EXCEPTION(FileNotOpendException, "BoltEngine::Plugin::CDynamicLib::Load",
			"Could not load dynamic library (" + m_LibName + ")");

	m_IsLoaded = true;
}

void CDynamicLib::Unload()
{
	if (m_IsLoaded)
	{
		if (!DYNAMIC_LIB_FREE(m_LibHandle))
		{
			THROW_EXCEPTION(InternalException, "BoltEngine::Plugin::CDynamicLib::Unload",
				"Could not unload dynamic library (" + m_LibName + ")");
		}
	}
}

bool CDynamicLib::IsLoaded() const
{
	return m_IsLoaded;
}

const CString &CDynamicLib::GetName() const
{
	return m_LibName;
}

void *CDynamicLib::GetSymbol(const CString &name) const
{
	return (void *)DYNAMIC_LIB_GETSYMBOL(m_LibHandle, name.c_str());
}

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()