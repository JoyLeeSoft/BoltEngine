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

#ifndef CVersion_h_
#define CVersion_h_

#include "BoltConfigurationMacros.h"
#include "BoltUtilityMacros.h"
#include "STL.h"

namespace BoltEngine
{
namespace Utility
{

/**
 * @author Lee
 * @brief A simple version class
 */
class BOLTENGINE_API CVersion
{
private:
	int m_Major;
	int m_Minor;
	int m_Build;

public:
	/**
	 * @brief Constructor
	 * @param major : A major version
	 * @param minor : A minor version
	 * @param build : A build number
	 * @code CVersion version(1, 0, 0);
	 * @endcode
	 */
	CVersion(int major, int minor, int build);

	/**
	 * @brief Constructor to convert from string
	 * @param version_str : A string for expression version value
	 * @code CVersion version(L"1.0.0");
	 * @endcode
	 * @throws CArgumentException : If the version_str is not available
	 */
	CVersion(const wstring &version_str);

	/**
	 * @brief Getting major version
	 * @return A major version
	 * @code int major_version = version.GetMajor();
	 * @endcode
	 */
	int GetMajor() const;

	/**
	 * @brief Getting minor version
	 * @return A minor version
	 * @code int minor_version = version.GetMinor();
	 * @endcode
	 */
	int GetMinor() const;

	/**
	 * @brief Getting build number
	 * @return A build number
	 * @code int build_number = version.GetBuild();
	 * @endcode
	 */
	int GetBuild() const;

	/**
	 * @brief Comparison two versions
	 * @return If the second version is high, function returns true\n
	 * If the second version is low or same, function returns false
	 * @code bool second_is_high = ver1 < ver2;
	 * @endcode
	 */
	bool operator <(const CVersion &rhs);

	/**
	 * @brief Comparison two versions
	 * @return If the second version is high or same, function returns true\n
	 * If the second version is low, function returns false
	 * @code bool second_is_high_or_same = ver1 <= ver2;
	 * @endcode
	 */
	bool operator <=(const CVersion &rhs);

	/**
	 * @brief Comparison two versions
	 * @return If the second version is low, function returns true\n
	 * If the second version is same or high, function returns false
	 * @code bool second_low = ver1 > ver2;
	 * @endcode
	 */
	bool operator >(const CVersion &rhs);


	/**
	 * @brief Comparison two versions
	 * @return If the second version is low or same, function returns true\n
	 * If the second version is high, function returns false
	 * @code bool second_is_low_or_same = ver1 >= ver2;
	 * @endcode
	 */
	bool operator >=(const CVersion &rhs);

	/**
	 * @brief Comparison two versions
	 * @return If two versions are same, function returns true\n
	 * If they are not same, function returns false
	 * @code bool two_version_are_same = ver1 == ver2;
	 * @endcode
	 */
	bool operator ==(const CVersion &rhs);

	/**
	 * @brief Comparison two versions
	 * @return If two versions are not same, function returns true,\n
	 * If they are same, function returns false
	 * @code bool two_version_are_not_same = ver1 != ver2;
	 * @endcode
	 */
	bool operator !=(const CVersion &rhs);

	/**
	 * @brief Convert to string
	 * @return Converted version string
	 * @code std::wstring version_string = static_cast<std::wstring>(version);
	 * @endcode
	 */
	operator const wstring() const;
};

}
}

#endif