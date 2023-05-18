#pragma once

#include "IStudentFeature.h"

namespace connections_graph
{
	class IConnectionsGraph
	{
	public:
		virtual double averageDistanceForFeatures(const IStudentFeature& feature, const IStudentFeature& feature2) const = 0;
		virtual int shortestPath(const std::string& userA, const std::string& userB) const = 0;
		virtual ~IConnectionsGraph() = 0 {};
	};
}


