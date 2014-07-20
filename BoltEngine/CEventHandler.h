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

#ifndef CEventHandler_h_
#define CEventHandler_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "STL.h"

namespace BoltEngine
{
namespace Event
{

struct SEventArgs 
{
public:
	void *Sender;
};

template <typename EventArgs> class CEventHandler
{
public:
	typedef function<void(EventArgs &)> EventFunction;
	typedef void(*EventFunctionPtr)(EventArgs &);

private:
	typedef vector<EventFunction> EventList;
	EventList m_EventList;

	typedef vector<EventFunctionPtr> RemovableEventList;
	RemovableEventList m_RemovableEventList;



public:
	void operator +=(EventFunction func)
	{
		m_EventList.push_back(func);
	}

	void AddRemovable(EventFunctionPtr func)
	{
		m_RemovableEventList.push_back(func);
	}

	void operator -=(EventFunctionPtr func)
	{
		m_RemovableEventList.erase(remove(m_RemovableEventList.begin(), m_RemovableEventList.end(), 
			func), m_RemovableEventList.end());
	}

	void operator ()(EventArgs &e)
	{
		for (auto func : m_EventList)
		{
			func(e);
		}

		for (auto func : m_RemovableEventList)
		{
			func(e);
		}
	}
};

}
}

#endif