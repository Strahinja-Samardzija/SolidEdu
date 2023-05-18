#pragma once

#include "solid_edu_IStudentFeature.h"
#include <string>
#include <memory>

namespace solid_edu
{
	class IConnectionsGraph
	{
	public:
		virtual double averageDistanceForFeatures(std::unique_ptr<solid_edu::IStudentFeature> feature, 
			std::unique_ptr<solid_edu::IStudentFeature> feature2) const = 0;
		virtual int shortestPath(const std::string& userA, const std::string& userB) const = 0;

		virtual ~IConnectionsGraph() = 0 {};
	};
}
