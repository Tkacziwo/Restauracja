#pragma once
#include <string>
#include "Person.h"
#include "Entity.h"
#include "Address.h"

namespace ent {
	class Client : public Person {
		std::string ContactNumber = "";
	public:

		Client() {}

		Client(const std::string& c)
		{
			std::string addressHandler;
			std::stringstream ss(c);
			ss
				>> Name
				>> Surname
				>> ContactNumber;

			std::getline(ss, addressHandler);
		}

		Client(const ent::Person& person, const std::string& number) : Person(person), ContactNumber(number) {};

		std::string GetClientInfo() const noexcept
		{
			return Name + " " + Surname + " " + ContactNumber;
		}

		void PatchClientContactNumber(const std::string& contactNumber)
		{
			ContactNumber = contactNumber;
		}
	};

	std::ostream& operator << (std::ostream& output, ent::Client c)
	{
		output << c.GetClientInfo()<<"\n";
		return output;
	}
}