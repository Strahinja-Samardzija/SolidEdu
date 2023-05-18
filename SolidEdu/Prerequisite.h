#pragma once

#include <string>

namespace solid_edu
{
	// every concrete should have a static method new_object which calls the constructor
	class Prerequisite
	{
	public:
		virtual void failMassage() const = 0;

		virtual bool metBy(const std::string& username) const = 0;

		virtual std::string GetConcreteDescription() const = 0;

		virtual std::string GetTypeDescription() const = 0;

		// used by teachers when adding prerequisites of existing types
		// eg. Please enter the course's name
		virtual std::string SupplyArgsInstruction() const = 0;

		virtual Prerequisite* clone() const = 0;

		virtual ~Prerequisite() = 0 {};
	};
}

namespace std
{
	template<> struct hash<solid_edu::Prerequisite>
	{
		size_t operator()(const solid_edu::Prerequisite& x) const
		{
			return hash<string>()(x.GetConcreteDescription());
		}
	};

	template<> struct equal_to<solid_edu::Prerequisite>
	{
		bool operator()(const solid_edu::Prerequisite& p1, const solid_edu::Prerequisite& p2) const
		{
			return p1.GetConcreteDescription() == p2.GetConcreteDescription();
		}
	};
}
