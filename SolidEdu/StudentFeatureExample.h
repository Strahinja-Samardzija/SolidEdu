#pragma once

#include "solid_edu_IStudentFeature.h"
#include <string>
#include "stringlib.h"

namespace solid_edu
{
	class StudentFeatureExample : public solid_edu::IStudentFeature
	{
	public:
		bool hasFeature(const std::string& username) const;
	};

	class StudentFeatureExample2 : public solid_edu::IStudentFeature
	{
	public:
		bool hasFeature(const std::string& username) const;
	};
}
