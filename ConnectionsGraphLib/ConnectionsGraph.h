#pragma once

#include "IConnectionsGraph.h"
#include "IStudentFeature.h"

#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

namespace connections_graph
{
	class ConnectionsGraph : public IConnectionsGraph
	{
	private:
		std::vector<std::string> users = std::vector<std::string>();
		std::unordered_map<std::string, std::vector<std::string>> userToFriendList = 
			std::unordered_map<std::string, std::vector<std::string>>();

		std::string graphFileDestination;

	public:
		ConnectionsGraph(const std::string& graphFileDestination);

		int shortestPath(const std::string& userA, const std::string& userB) const override;
		
		// averageDistance means the average length of the shortest path in the worst possible arrangement of people
		// the worst arrangement - if userA and userB have the feature,
		//      but are not connected directly nor indirectly, then every other user will be visited sooner on path from userA to userB
		double averageDistanceForFeatures(const IStudentFeature& feature, const IStudentFeature& feature2) const override;
	
	private:
		void InitializeGraph();
		
		int guidedBFS(const std::string& userA, const std::string& userB) const;

		void EnqueuePriority(const std::string& user, int currentDistance,
			std::list<std::tuple<int, int, std::string>>& priorityQueue_dist_friendCount_name) const;
		
		void floydWarshall(std::map<std::pair<std::string, std::string>, int>& distanceMatrix) const;

		std::map<std::pair<std::string, std::string>, int> convertToMatrix() const;
	};
}

