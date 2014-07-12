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

#ifndef CDynamicLib_h_
#define CDynamicLib_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "Type.h"

#if BOLTENGINE_PLATFORM == BOLTENGINE_PLATFORM_WIN32
#include <windows.h>
#define DYNAMIC_LIB_HANDLE HMODULE
#define DYNAMIC_LIB_LOAD(name) LoadLibraryExW(name, NULL, LOAD_WITH_ALTERED_SEARCH_PATH)
#define DYNAMIC_LIB_GETSYMBOL(module, name) GetProcAddress(module, name)
#define DYNAMIC_LIB_FREE(module) FreeLibrary(module)
#endif

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Plugin)

class BOLTENGINE_API CDynamicLib
{
public:
	CDynamicLib(const wstring &name);
	virtual ~CDynamicLib();

private:
	DYNAMIC_LIB_HANDLE m_LibHandle;
	const wstring m_LibName;

	Bool m_IsLoaded;

public:
	void Load();
	void Unload();

	Bool IsLoaded() const;
	const wstring &GetName() const;

	void *GetSymbol(const wstring &name) const;
};

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()

#endif