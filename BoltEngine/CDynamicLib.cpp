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
#include <boost/locale.hpp>

#include "CDynamicLib.h"
#include "CException.h"

namespace BoltEngine
{
namespace Plugin
{

using namespace Exception;

CDynamicLib::CDynamicLib(const wstring &name) : m_IsLoaded(false), m_LibName(name), m_LibHandle(0)
{
	
}

CDynamicLib::~CDynamicLib()
{
	Unload();
}

void CDynamicLib::Load()
{
	wstring name = m_LibName;
#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
	if (name.substr(name.length() - 4, 4) != L".dll")
		name += L".dll";
#endif

	m_LibHandle = DYNAMIC_LIB_LOAD(name.c_str());

	if (!m_LibHandle)
		THROW_EXCEPTION(FileLoadException, _W(BOOST_CURRENT_FUNCTION),
			L"Could not load dynamic library \"" + m_LibName + L"\"");

	m_IsLoaded = true;
}

void CDynamicLib::Unload()
{
	if (m_IsLoaded)
	{
		if (!DYNAMIC_LIB_FREE(m_LibHandle))
		{
			THROW_EXCEPTION(SystemException, _W(BOOST_CURRENT_FUNCTION),
				L"Could not unload dynamic library (" + m_LibName + L")");
		}

		m_IsLoaded = false;
	}
}

bool CDynamicLib::IsLoaded() const
{
	return m_IsLoaded;
}

const wstring &CDynamicLib::GetName() const
{
	return m_LibName;
}

void *CDynamicLib::GetSymbol(const wstring &name) const
{
	string temp = boost::locale::conv::from_utf(name, "ISO8859-15");
	return (void *)DYNAMIC_LIB_GETSYMBOL(m_LibHandle, temp.c_str());
}

}
}