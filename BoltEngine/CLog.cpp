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

#include <fstream>
#include <time.h>

#include "CLog.h"

namespace BoltEngine
{
namespace Log
{

const vector<const wstring> CLog::m_LogCodeNames =
{
#define e(x) L#x,
#include "LogCodes.enum"
#undef e
};

CLog::CLog()
{

}

CLog::~CLog()
{

}

void CLog::AddLog(ELogKind kind, const wstring &file, unsigned int line, const wstring &func, const wstring &msg)
{
	if (m_Stream == nullptr)
		return;

	wstring str = m_LogCodeNames[kind] + L":\nFile : " + file + L"\nLine : " + to_wstring(line) + L"\nFunction : "
		+ func + L'\n' + msg + L"\n\n";
	(*m_Stream)<<(str.c_str());
}

void CLog::SetLogStream(wostream *stream)
{
	m_Stream = stream;
}

}
}