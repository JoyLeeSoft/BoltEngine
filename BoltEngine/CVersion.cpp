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

#include <vector>
#include <boost/tokenizer.hpp>
#include <string>
#include <stdexcept>

#include "CVersion.h"
#include "CException.h"

BOLTENGINE_NAMESPACE_BEGIN(BoltEngine)
BOLTENGINE_NAMESPACE_BEGIN(Utility)

using namespace Exception;

std::vector<string> SplitString(const string &str, const string &token)
{
	boost::tokenizer<boost::char_separator<Char>, string::const_iterator, string>
		temp(str, boost::char_separator<Char>(token.c_str()));
	return std::vector<string>(temp.begin(), temp.end());
}

CVersion::CVersion(Int major, Int minor, Int build)
{
	m_Major = major;
	m_Minor = minor;
	m_Build = build;
}

CVersion::CVersion(const string &version_str)
{
	Int n = count(version_str.begin(), version_str.end(), '.');
	
	if (n == 2)
	{
		auto token = SplitString(version_str, ".");

		try
		{
			m_Major = std::stoi(token[0]);
			m_Minor = std::stoi(token[1]);
			m_Build = std::stoi(token[2]);
		}
		catch (std::invalid_argument &)
		{
			THROW_EXCEPTION(ArgumentException, BOOST_CURRENT_FUNCTION,
				"Argument 'version_str' is not available");
		}

		return;
	}

	THROW_EXCEPTION(ArgumentException, BOOST_CURRENT_FUNCTION,
		"Argument 'version_str' is not available");
}

Int CVersion::GetMajor() const { return m_Major; }

Int CVersion::GetMinor() const { return m_Minor; }

Int CVersion::GetBuild() const { return m_Build; }

Bool CVersion::operator <(const CVersion &rhs)
{
	if (m_Major < rhs.m_Major)
		if (m_Minor < rhs.m_Minor)
			if (m_Build < rhs.m_Build)
				return true;

	return false;
}

Bool CVersion::operator <=(const CVersion &rhs)
{
	return (*this == rhs) || (*this < rhs);
}

Bool CVersion::operator >(const CVersion &rhs)
{
	return !(*this <= rhs);
}

Bool CVersion::operator >=(const CVersion &rhs)
{
	return !(*this < rhs);
}

Bool CVersion::operator ==(const CVersion &rhs)
{
	return (m_Major == rhs.m_Major) && (m_Minor == rhs.m_Minor) && (m_Build == rhs.m_Build);
}

Bool CVersion::operator !=(const CVersion &rhs)
{
	return !(*this == rhs);
}

CVersion::operator const string() const
{
	return std::to_string(m_Major) + '.' + std::to_string(m_Minor) + '.' + std::to_string(m_Build);
}

BOLTENGINE_NAMESPACE_END()
BOLTENGINE_NAMESPACE_END()