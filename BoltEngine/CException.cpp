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

#include "CException.h"
#include "BoltUtilityMacros.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Exception)

const Vector<const CString>::Type CException::m_ExceptionNames =
{
#define e(x) #x,
#include "ExceptionCodes.enum"
#undef e
};

CException::CException(EExceptionCode code, const CString &func_name, const CString &desc) : m_ExceptionCode(code),
	m_FunctionName(func_name), m_Description(desc)
{

}

CException::CException(CException &rhs)
{
	CHANGE_MEMBER_BEGIN(rhs)
		CHANGE_MEMBER(m_ExceptionCode)
		CHANGE_MEMBER(m_FunctionName)
		CHANGE_MEMBER(m_Description)
	CHANGE_MEMBER_END()
}

CException::~CException() throw()
{

}

Int CException::GetExceptionCode() const throw()
{
	return m_ExceptionCode;
}

const CString &CException::GetExceptionName() const throw()
{
	return m_ExceptionNames[m_ExceptionCode];
}

const CString &CException::GetFunctionName() const throw()
{
	return m_FunctionName;
}

const CString &CException::GetDescription() const throw()
{
	return m_Description;
}

CException &CException::operator =(const CException &rhs)
{
	CHANGE_MEMBER_BEGIN(rhs)
		CHANGE_MEMBER(m_ExceptionCode)
		CHANGE_MEMBER(m_FunctionName)
		CHANGE_MEMBER(m_Description)
	CHANGE_MEMBER_END()

	return *this;
}

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()