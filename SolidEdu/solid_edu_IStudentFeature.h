#pragma once

#include <string>

namespace solid_edu
{
	class IStudentFeature
	{
	public:
		virtual bool hasFeature(const std::string& username) const = 0;

		virtual ~IStudentFeature() = 0 {};
	};
}
