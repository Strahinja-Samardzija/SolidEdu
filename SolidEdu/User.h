#pragma once
#include "IUser.h"
#include "Course.h"
#include <memory>
#include <string>
#include <unordered_set>

namespace solid_edu
{
	class User : public IUser // da bi mogao dodati decorator koji ima i spisak ocjena za ucenika
	{
	private:
		std::string username;
		std::string password;

		std::unique_ptr<IInbox> inbox;

		Course_HashSet myCourses;

	public:
		User(const std::string& username, const std::string& password);

		User* clone() override;

	private:
		void initializeMyCourses();

	public:
		void changePassword(const std::string& newPassword) override;

		std::unique_ptr<IInbox> getInbox() const override;

		inline Course_HashSet getCourses() const override;

		inline std::string getUsername() const override;
	};

}
