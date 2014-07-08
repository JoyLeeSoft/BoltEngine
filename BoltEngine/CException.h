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

#ifndef CException_h_
#define CException_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "Type.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Exception)


enum EExceptionCode : Int
{
#define e(name) name,
#include "ExceptionCodes.enum"
#undef e
};


class BOLTENGINE_API CException
{
protected:
	EExceptionCode m_ExceptionCode;
	CString m_FunctionName;
	CString m_Description;

private:
	static const Vector<const CString>::Type m_ExceptionNames;

public:
	CException(EExceptionCode code, const CString &func_name, const CString &desc);
	CException(CException &other);
	~CException() throw();

	virtual Int GetExceptionCode() const throw();
	virtual const CString &GetExceptionName() const throw();
	virtual const CString &GetFunctionName() const throw();
	virtual const CString &GetDescription() const throw();

	CException &operator =(const CException &rhs);
};

#ifndef MAKE_EXCEPTION_CLASS
#define MAKE_EXCEPTION_CLASS(name) \
	class BOLTENGINE_API name : public CException\
	{\
	public:\
		name(EExceptionCode code, const CString &func_name, const CString &desc) : CException(code, func_name, desc)\
		{\
		}\
	};
#endif

#define e(name) MAKE_EXCEPTION_CLASS(C##name##Exception)
#include "ExceptionCodes.enum"
#undef e

#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(error_code, func_name, desc) \
	throw C##error_code##Exception(error_code, func_name, desc)
#endif

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()

#endif