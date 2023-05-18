#pragma once

#include "IInbox.h"
#include "Course.h"
#include <string>
#include <memory>
#include <unordered_set>

namespace solid_edu
{
	class IUser
	{
	public:
		virtual void changePassword(const std::string& newPassword) = 0;
		virtual Course_HashSet getCourses() const = 0;
		virtual std::unique_ptr<IInbox> getInbox() const = 0;
		virtual std::string getUsername() const = 0;

		virtual IUser* clone() = 0;
		virtual ~IUser() = 0 {};
	};
}
