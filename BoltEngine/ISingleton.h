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

#ifndef ISingleton_h_
#define ISingleton_h_

#include "BoltUtilityMacros.h"
#include "IUnCopyable.h"

namespace BoltEngine
{
namespace Utility
{

/**
 * @author Lee
 * @brief Need to implementation singleton
 */
#define SET_SINGLETON_THIS_CLASS(type) friend class ISingleton<type>


/**
 * @author Lee
 * @brief A class for singleton
 * @code class Foo : public ISingleton<Foo>
 * @endcode
 */
template <typename T> class ISingleton abstract : private IUnCopyable
{
private:
	static T *m_Instance;

public:
	/**
	 * @brief Getting an instance
	 * @return Reference of the instance
	 * @code Foo &foo = Foo::Get();
	 * @endcode 
	 */
	static T &Get()
	{
		if (m_Instance == nullptr)
			m_Instance = new T;

		return *m_Instance;
	}

	/**
	 * @brief Getting an instance pointer
	 * @return Pointer of the instance
	 * @code Foo *foo_ptr = Foo::GetPtr();
	 * @endcode
	 */
	static T *GetPtr()
	{
		return &(Get());
	}

	/**
	 * @brief Delete an instance
	 * @code Foo::Delete();
	 * @endcode
	 */
	static void Delete()
	{
		delete m_Instance;
	}
};

template <typename T> T *ISingleton<T>::m_Instance = nullptr;

}
}

#endif