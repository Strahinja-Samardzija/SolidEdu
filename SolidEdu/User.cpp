#include "User.h"
#include "Factory.h"

namespace solid_edu
{
	User::User(const std::string& username, const std::string& password) :
		username{ username }, password{ password }, inbox{}, myCourses{}
	{
		this->inbox = Factory::GetInbox(username);
		initializeMyCourses();
	}

	User* User::clone()
	{
		return new User(username, password);
	}

	void User::initializeMyCourses()
	{
		myCourses = Factory::GetCourseFileManager()->ReadCoursesForUser(username);
	}

	void User::changePassword(const std::string& newPassword)
	{
		this->password = newPassword;
	}

	std::unique_ptr<IInbox> User::getInbox() const
	{
		return std::unique_ptr<IInbox> {inbox->clone()};
	}

	Course_HashSet User::getCourses() const
	{
		return myCourses;
	}

	std::string User::getUsername() const
	{
		return username;
	}
}
