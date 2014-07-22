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

//#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "ISingleton.h"
#include "STL.h"

namespace BoltEngine
{
namespace Log
{

using namespace Utility;

enum ELogKind : unsigned int
{
#define e(x) x,
#include "LogCodes.enum"
#undef e
};

struct SLog
{
public:
	ELogKind Kind;
	wstring File;
	unsigned int Line;
	wstring Func;
	wstring Msg;
};

class /*BOLTENGINE_API*/ CLog final : public ISingleton<CLog>
{
	SET_SINGLETON_THIS_CLASS(CLog);

private:
	CLog();
	~CLog();

private:
	static const vector<const wstring> m_LogCodeNames;

private:
	typedef vector<SLog> LogList;
	LogList m_LogList;
	wostream *m_Stream;

public:
	void AddLog(ELogKind kind, const wstring &file, unsigned int line, const wstring &func, 
		const wstring &msg);
	void SetLogStream(wostream *stream);
};

#define LOG(kind, msg) Log::CLog::Get().AddLog(kind, _W(__FILE__), __LINE__, _W(BOOST_CURRENT_FUNCTION), msg);

}
}