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
#include "STL.h"

namespace BoltEngine
{
namespace Exception
{

enum EExceptionCode : int
{
#define e(name) name##Exception,
#include "ExceptionCodes.enum"
#undef e
};

/**
 * @author Lee
 * @brief A BoltEngine exception class
 */
class BOLTENGINE_API CException
{
private:
	EExceptionCode m_ExceptionCode;
	wstring m_FunctionName;
	wstring m_Description;

private:
	static const vector<const wstring> m_ExceptionNames;

public:
	/**
	 * @brief Constructor.
	 * @param code : An exception code
	 * @param func_name : A name of the function where the exception occurred
	 * @param desc : A description
	 */
	CException(EExceptionCode code, const wstring &func_name, const wstring &desc);

	/**
	 * @brief Copy constructor.
	 * @param other : An exception class to copy
	 */
	CException(CException &other);

	/**
	 * @brief Getting error code
	 * @return An error code
	 * @code int error_code = e.GetCode();
	 * @endcode
	 */
	virtual int GetCode() const throw();

	/**
	 * @brief Getting error name
	 * @return An error name
	 * @code std::wstring error_name = e.GetName();
	 * @endcode
	 */
	virtual const wstring &GetName() const throw();

	/**
	 * @brief Getting function name
	 * @return A function name
	 * @code std::wstring func_name = e.GetFunctionName();
	 * @endcode
	 */
	virtual const wstring &GetFunctionName() const throw();

	/**
	 * @brief Getting description
	 * @return A description
	 * @code std::wstring desc = e.GetDescription();
	 * @endcode
	 */
	virtual const wstring &GetDescription() const throw();

	/**
	 * @brief Copying operator
	 * @return This instance
	 * @code CException e = other;
	 * @endcode
	 */
	CException &operator =(const CException &rhs);
};

#ifndef MAKE_EXCEPTION_CLASS
#define MAKE_EXCEPTION_CLASS(name) \
	class BOLTENGINE_API name : public CException\
	{\
	public:\
		name(EExceptionCode code, const wstring &func_name, const wstring &desc) : CException(code, func_name, desc)\
		{\
		}\
	};
#endif

#define e(name) MAKE_EXCEPTION_CLASS(C##name##Exception)
#include "ExceptionCodes.enum"
#undef e

/**
 * @author
 * @brief Throw an exception class
 * @code THROW_EXCEPTION(ExceptionCode, L"Function name", L"Description");
 * @endcode
 */
#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(error_code, func_name, desc) \
	throw C##error_code(error_code, func_name, desc)
#endif

#ifdef BOLTENGINE_PLATFORM_WIN32
BOLTENGINE_API wstring HResultToString(unsigned int hr);
#endif

}
}

#endif