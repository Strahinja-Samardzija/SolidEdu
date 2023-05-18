#include "pch.h"
#include "framework.h"
#include "ConnectionsGraph.h"
#include "StringLib.h"

#include <iterator>

#define MAX_FRIENDS 100
#define USERNAME_LENGTH 30

//todo check if some should be const
namespace connections_graph
{
	ConnectionsGraph::ConnectionsGraph(const std::string& graphFileDestination)
	{
		this->graphFileDestination = graphFileDestination;
		InitializeGraph();
	}

	void ConnectionsGraph::InitializeGraph()
	{
		auto lines = stringlib::readAllLines(graphFileDestination);

		for (auto& line : lines)
		{
			std::string user{ stringlib::trim(line.substr(0, line.find("-"))) };

			// bilo line.substr(0, 2) todo otkud umjesto "- "
			if (stringlib::endsWith(line, "- "))
			{
				userToFriendList[user] = std::vector<std::string>();
				continue;
			}

			users.push_back(user);

			auto friends = stringlib::split(line.substr(line.find('-') + 1), ',');

			for (auto& aFriend : friends)
			{
				if (userToFriendList.find(user) != userToFriendList.end())
				{
					userToFriendList[user].push_back(aFriend);
				}
				else
				{
					userToFriendList.emplace(user, std::vector<std::string> {aFriend});
				}
			}
			if (friends.size() == 0)
			{
				userToFriendList.emplace(user, std::vector<std::string>{});
			}
		}
	}

	int ConnectionsGraph::shortestPath(const std::string& userA, const std::string& userB) const
	{
		return guidedBFS(userA, userB); // most friends first
	}

	int ConnectionsGraph::guidedBFS(const std::string& userA, const std::string& userB) const
	{
		std::unordered_set<std::string> visited;
		std::list<std::tuple<int, int, std::string>> priorityQueue_dist_friendCount_name;

		priorityQueue_dist_friendCount_name.push_back(
			std::make_tuple(0, userToFriendList.at(userA).size(), userA));
		std::string userFrom = "";

		while (priorityQueue_dist_friendCount_name.size() != 0)
		{
			userFrom = std::get<2>(priorityQueue_dist_friendCount_name.front());
			int currentDistance = std::get<0>(priorityQueue_dist_friendCount_name.front());
			visited.insert(userFrom);

			priorityQueue_dist_friendCount_name.erase(priorityQueue_dist_friendCount_name.begin());

			if (userFrom == userB)
			{
				return currentDistance;
			}

			std::vector<std::string> friendsToVisit;
			std::copy_if(
				userToFriendList.at(userFrom).cbegin(), userToFriendList.at(userFrom).cend(),
				std::back_inserter(friendsToVisit),
				[&visited](std::string userTo)
				{
					return visited.find(userTo) == visited.end();
				}
			);

			for (auto& userTo : friendsToVisit)
			{
				EnqueuePriority(userTo, currentDistance, priorityQueue_dist_friendCount_name);
			}
		}
		return -1;
	}

	void ConnectionsGraph::EnqueuePriority(
		const std::string& user,
		int currentDistance,
		std::list<std::tuple<int, int, std::string>>& priorityQueue_dist_friendCount_name
	) const
	{
		auto iterator = priorityQueue_dist_friendCount_name.begin();
		for (int i = 0; i < priorityQueue_dist_friendCount_name.size(); i++)
		{
			auto& info = *iterator;
			if (std::get<0>(info) < currentDistance + 1 ||
				std::get<1>(info) >= userToFriendList.at(user).size())
			{
				iterator++;
				continue;
			}
			else
			{
				priorityQueue_dist_friendCount_name.insert(
					iterator,
					std::make_tuple(
						currentDistance + 1,
						userToFriendList.at(user).size(),
						user)
				);
				return;
			}
		}
		// place last
		priorityQueue_dist_friendCount_name.push_back(
			std::make_tuple(
				currentDistance + 1,
				userToFriendList.at(user).size(),
				user)
		);
	}

	double ConnectionsGraph::averageDistanceForFeatures(const IStudentFeature& feature, const IStudentFeature& feature2) const
	{
		std::map<std::pair<std::string, std::string>, int> distanceMatrix = convertToMatrix();
		floydWarshall(distanceMatrix);

		std::vector<std::string> representativesA;
		std::copy_if(users.cbegin(), users.cend(), back_inserter(representativesA),
			[&feature](const std::string& student)
			{
				return feature.hasFeature(student);
			}
		);

		std::vector<std::string> representativesB;
		std::copy_if(users.cbegin(), users.cend(), back_inserter(representativesB),
			[&feature2](const std::string& student)
			{
				return feature2.hasFeature(student);
			}
		);

		int sum = 0;
		int addingsCount = 0;
		for (int i = 0; i < representativesA.size() - 1; i++)
		{
			for (int j = 0; j < representativesB.size(); j++)
			{
				addingsCount++;
				if (distanceMatrix.find(std::make_pair(representativesA[i], representativesB[j])) != distanceMatrix.end())
				{
					sum += userToFriendList.size() - distanceMatrix[std::make_pair(representativesA[i], representativesB[j])];
				}
				else
				{
					sum += userToFriendList.size();
					continue;
				}
			}
		}

		return addingsCount != 0 ? (double)(sum) / addingsCount : -1;
	}

	void ConnectionsGraph::floydWarshall(std::map<std::pair<std::string, std::string>, int>& distanceMatrix) const
	{
		for (auto& userK : users)
		{
			for (auto& userFrom : users)
			{
				for (auto& userTo : users)
				{
					if (userFrom == userTo)
					{
						distanceMatrix[std::make_pair(userFrom, userTo)] = 0;
					}

					if (std::find(userToFriendList.at(userFrom).cbegin(), userToFriendList.at(userFrom).cend(),
						userTo) != userToFriendList.at(userFrom).cend())
					{
						distanceMatrix[std::make_pair(userFrom, userTo)] = 1;
					}

					if (userK == userFrom || userK == userTo)
					{
						continue;
					}

					if (distanceMatrix.find(std::make_pair(userFrom, userK)) != distanceMatrix.end()
						&& distanceMatrix.find(std::make_pair(userK, userTo)) != distanceMatrix.end())
					{
						if (distanceMatrix.find(std::make_pair(userFrom, userTo)) != distanceMatrix.end())
						{
							if (distanceMatrix[std::make_pair(userFrom, userTo)] >
								distanceMatrix[std::make_pair(userFrom, userK)] + distanceMatrix[std::make_pair(userK, userTo)])
							{
								distanceMatrix[std::make_pair(userFrom, userTo)] =
									distanceMatrix[std::make_pair(userFrom, userK)] + distanceMatrix[std::make_pair(userK, userTo)];
							}
						}
						else
						{

							distanceMatrix[std::make_pair(userFrom, userTo)] =
								distanceMatrix[std::make_pair(userFrom, userK)] + distanceMatrix[std::make_pair(userK, userTo)];

						}
					}
				}
			}
		}
	}

	std::map<std::pair<std::string, std::string>, int> ConnectionsGraph::convertToMatrix() const
	{
		auto distanceMatrix = std::map<std::pair<std::string, std::string>, int>();

		for (auto& userFrom : users)
		{
			for (auto& userTo : userToFriendList.at(userFrom))
			{
				distanceMatrix[std::make_pair(userFrom, userTo)] = 1;
			}
		}

		return distanceMatrix;
	}
}
