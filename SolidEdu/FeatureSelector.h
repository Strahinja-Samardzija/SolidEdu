#pragma once

#include "IFeatureSelector.h"
#include <iostream>

namespace solid_edu
{
	class FeatureSelector : public IFeatureSelector
	{
	public:
		std::unique_ptr<solid_edu::IStudentFeature> selectFeature() const override;
	};
}
