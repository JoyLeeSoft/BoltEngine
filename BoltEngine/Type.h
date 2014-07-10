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

#ifndef Type_h_
#define Type_h_

/* Standard C++ header includes */
#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <algorithm>

using namespace std;

#include "BoltUtilityMacros.h"
#include "BoltConfigurationMacros.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)

typedef
#if BOLTENGINE_COMPILED == BOLTENGINE_COMPILED_VISUALCPP
__int32
#endif
Int;

typedef
#if BOLTENGINE_COMPILED == BOLTENGINE_COMPILED_VISUALCPP
__int16
#endif
Short;

typedef
#if BOLTENGINE_COMPILED == BOLTENGINE_COMPILED_VISUALCPP
__int8
#endif
Byte;

typedef
#if BOLTENGINE_COMPILED == BOLTENGINE_COMPILED_VISUALCPP
__int32
#endif
Int;

typedef
#if BOLTENGINE_COMPILED == BOLTENGINE_COMPILED_VISUALCPP
__int64
#endif
Long;

typedef float Float;

typedef double Double;

typedef bool Bool;

typedef char Char;
typedef wchar_t WChar;

BOLTENGINE_NAMESPACE_END()

#endif