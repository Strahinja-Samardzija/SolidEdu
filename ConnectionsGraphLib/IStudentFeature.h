#pragma once

#include <string>

namespace connections_graph
{
	class IStudentFeature
	{
	public:
		virtual bool hasFeature(const std::string& username) const = 0;
		virtual ~IStudentFeature() = 0 {};
	};
}


