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

#ifndef BoltConfigurationMacros_h_
#define BoltConfigurationMacros_h_

#ifdef BOLTENGINE_EXPORT
#ifdef _MSC_VER
#define BOLTENGINE_API __declspec(dllexport)
#endif
#else
#ifdef _MSC_VER
#define BOLTENGINE_API __declspec(dllimport)
#endif
#endif

#ifdef _MSC_VER
#ifdef _DEBUG
#define BOLTENGINE_DEBUGMODE 1
#else 
#define BOLTENGINE_DEBUGMODE 0
#endif
#else
#endif


#define BOLTENGINE_PLATFORM_WIN32 0
#define BOLTENGINE_PLATFORM_LINUX 1
#define BOLTENGINE_PLATFORM_MAC 2

#ifndef BOLTENGINE_PLATFORM 
#define BOLTENGINE_PLATFORM BOLTENGINE_PLATFORM_WIN32
#endif


#define BOLTENGINE_COMPILED_VISUALCPP 0
#define BOLTENGINE_COMPILED_GCC 1

#ifndef BOLTENGINE_COMPILED
#define BOLTENGINE_COMPILED BOLTENGINE_COMPILED_VISUALCPP
#endif

#if BOLTENGINE_COMPILED == BOLTENGINE_COMPILED_VISUALCPP
#pragma warning(disable : 4251)
#endif

#endif