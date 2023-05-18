#pragma once

#include "ConnectionsGraph.h"
#include "solid_edu_IStudentFeature.h"
#include <string>

namespace solid_edu
{
	class StudentFeatureAdapterToLibrary : public connections_graph::IStudentFeature
	{
	private:
		std::unique_ptr<solid_edu::IStudentFeature> studentFeatureAdaptee;

	public:
		StudentFeatureAdapterToLibrary(std::unique_ptr<solid_edu::IStudentFeature> feature);

		bool hasFeature(const std::string& username) const override;
	};
}
