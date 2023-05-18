#include "ConnectionsGraphAdapterFromLibrary.h"
#include "StudentFeatureAdapterToLibrary.h"

namespace solid_edu
{
	ConnectionsGraphAdapterFromLibrary::ConnectionsGraphAdapterFromLibrary(
		std::shared_ptr<connections_graph::ConnectionsGraph> connectionsGraph)
		: connectionsGraphAdaptee{ connectionsGraph } {}

	double ConnectionsGraphAdapterFromLibrary::averageDistanceForFeatures(std::unique_ptr<solid_edu::IStudentFeature> feature, 
		std::unique_ptr<solid_edu::IStudentFeature> feature2) const 
	{
		StudentFeatureAdapterToLibrary temp{ std::move(feature) };
		StudentFeatureAdapterToLibrary temp2{ std::move(feature2) };
		return connectionsGraphAdaptee->averageDistanceForFeatures(temp, temp2);
	}

	int ConnectionsGraphAdapterFromLibrary::shortestPath(const std::string& userA, const std::string& userB) const
	{
		return connectionsGraphAdaptee->shortestPath(userA, userB);
	}
}
