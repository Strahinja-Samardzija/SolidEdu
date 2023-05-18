#pragma once

#include "solid_edu_IConnectionsGraph.h"
#include "solid_edu_IStudentFeature.h"
#include "ConnectionsGraph.h"
#include <string>

namespace solid_edu
{
	//todo solid_edu ima svoj IFeature
	class ConnectionsGraphAdapterFromLibrary : public solid_edu::IConnectionsGraph
	{
	private:
		std::shared_ptr<connections_graph::ConnectionsGraph> connectionsGraphAdaptee;

	public:
		ConnectionsGraphAdapterFromLibrary(std::shared_ptr<connections_graph::ConnectionsGraph> connectionsGraph);

		double averageDistanceForFeatures(std::unique_ptr<solid_edu::IStudentFeature> feature, 
			std::unique_ptr<solid_edu::IStudentFeature> feature2) const override;

		int shortestPath(const std::string& userA, const std::string& userB) const override;
	};
}
