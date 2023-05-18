#pragma once

#include "solid_edu_IStudentFeature.h"
#include <memory>

namespace solid_edu
{
	class IFeatureSelector
	{
	public:
		virtual std::unique_ptr<solid_edu::IStudentFeature> selectFeature() const = 0;
	};
}
