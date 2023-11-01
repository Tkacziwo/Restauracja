#pragma once
#include <string>
#include <sstream>
#include "Date.h"

namespace ent {
	class Person
	{
	protected:
		std::string Name;
		std::string Surname;
		td::Date DateOfBirth;
	public:

		Person() {};

		Person(const std::string& name, const std::string& surname) : Name(name), Surname(surname) {};

		Person(const std::string& name, const std::string& surname, const td::Date& date)
			: Name(name), Surname(surname), DateOfBirth(date) {};

		void AddDateOfBirth(const td::Date& date)
		{
			DateOfBirth = date;
		}

		std::string GetName() const noexcept
		{
			return Name;
		}

		std::string GetSurname() const noexcept
		{
			return Surname;
		}

		std::string GetDateOfBirth() const noexcept
		{
			return DateOfBirth.GetSaveString();
		}

		void PatchName(const std::string& name)
		{
			Name = name;
		}

		void PatchSurname(const std::string& surname)
		{
			Surname = surname;
		}

		void PatchDateOfBirth(const td::Date& date)
		{
			DateOfBirth = date;
		}
		
		std::string GetPartialInfo() const noexcept
		{
			return Name + " " + Surname;
		}
	};

	std::ostream& operator << (std::ostream& output, const Person& p)
	{
		output << p.GetName() << "\n" << p.GetSurname() << "\n" << p.GetDateOfBirth() << "\n";
		return output;
	}
}