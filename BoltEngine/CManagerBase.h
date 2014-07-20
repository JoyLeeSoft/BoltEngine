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

#ifndef CManagerBase_h_
#define CManagerBase_h_

#include <boost/current_function.hpp>

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "CException.h"

namespace BoltEngine
{
namespace Manager
{

using namespace Exception;

class CPluginManager;

template <typename T> class CManagerBase
{
	friend class CPluginManager;

protected:
	CManagerBase()
	{

	}

	virtual ~CManagerBase()
	{
		for (auto element : m_ElementList)
		{
			try
			{
				delete element;
			}
			catch (...)
			{

			}
		}

		m_ElementList.clear();
	}

private:
	typedef vector<T *> ElementList;
	ElementList m_ElementList;

private:
	void _insert_element(T *element)
	{
		m_ElementList.push_back(element);
	}

public:
	T *GetByName(const wstring &name)
	{
		auto it = find_if(m_ElementList.begin(), m_ElementList.end(), [name](T *element)
		{
			return element->GetName() == name;
		});

		if (it != m_ElementList.end())
			return *it;
		else
			THROW_EXCEPTION(ArgumentException, _W(BOOST_CURRENT_FUNCTION), L"Could not find element \"" +
				name + L"\"");
	}
};

}
}

#endif