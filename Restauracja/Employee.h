#pragma once

namespace ent {

	class Employee : public Entity, public Person {

		float Salary = 0;
		std::string Occupation;
		ut::Address Address;
	public:

		Employee(std::string& str)
		{
			int position;
			std::string date;
			std::stringstream ss(str);
			ss >> Id
				>> Name
				>> Surname
				>> date
				>> Salary
				>> Occupation;
			DateOfBirth = td::Date(date);
			position = str.find('#');
			str = str.substr(position + 1);
			Address = ut::Address(str);
		}

		Employee(int id, float salary, const std::string& occupation, const ent::Person& person, const ut::Address& address) :
			Entity(id),
			Salary(salary),
			Occupation(occupation),
			Person(person),
			Address(address) {};

		std::string GetOccupation() const noexcept
		{
			return Occupation;
		}

		std::string DisplayTemplate() const noexcept
		{
			std::stringstream ss;

			ss << std::setw(7) << std::setfill(' ') << std::left << "Id:"
				<< std::setw(20) << std::setfill(' ') << std::left << "Name:"
				<< std::setw(30) << std::setfill(' ') << std::left << "Surname:"
				<< std::setw(15) << std::setfill(' ') << std::left << "Occupation:"
				<< std::setw(15) << std::setfill(' ') << "DateOfBirth:"
				<< std::setw(15) << std::setfill(' ') << "Salary:"
				<< std::setw(10) << std::setfill(' ') << "Address:\n";

			return ss.str();
		}

		std::string DisplayPartialTemplate() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << "Id:"
				<< std::setw(20) << std::setfill(' ') << std::left << "Name:"
				<< std::setw(30) << std::setfill(' ') << std::left << "Surname:" << "\n";
			return ss.str();
		}

		std::string GetInfo() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << "Id:"
				<< std::setw(20) << std::setfill(' ') << std::left << "Name:"
				<< std::setw(30) << std::setfill(' ') << std::left << "Surname:"
				<< std::setw(15) << std::setfill(' ') << std::left << "Occupation:"
				<< std::setw(15) << std::setfill(' ') << std::left << "Salary:" << "\n"
				<< std::setw(7) << std::setfill(' ') << std::left << std::to_string(Id)
				<< std::setw(20) << std::setfill(' ') << std::left << Name
				<< std::setw(30) << std::setfill(' ') << std::left << Surname
				<< std::setw(15) << std::setfill(' ') << std::left << Occupation
				<< std::setw(15) << std::setfill(' ') << std::left << Salary << "\n"
				<< std::setw(15) << std::setfill(' ') << std::left << "DateOfBirth:"
				<< std::setw(40) << std::setfill(' ') << std::left << "Address:" << "\n"
				<< std::setw(15) << std::setfill(' ') << DateOfBirth.GetDate()
				<< std::setw(40) << std::setfill(' ') << Address.GetAddress() << "\n";
			return ss.str();
		}

		std::string GetPartialInfo() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << std::to_string(Id)
				<< std::setw(20) << std::setfill(' ') << std::left << Name
				<< std::setw(30) << std::setfill(' ') << std::left << Surname << "\n";

			return ss.str();
		}

		std::string GetSaveString() const noexcept
		{
			return std::to_string(Id) + " "	+ Name + " " + Surname + " " + DateOfBirth.GetSaveString()
				+ " " + std::to_string(Salary) + " " + Occupation + " #" + Address.GetSaveString() + "\n";
		}

		void PatchSalary(float salary)
		{
			Salary = salary;
		}

		void PatchOccupation(const std::string& occupation)
		{
			Occupation = occupation;
		}

		void PatchAddress(const ut::Address& address)
		{
			Address = address;
		}

	};

	std::ostream& operator << (std::ostream& output, const Employee& emp)
	{
		output << emp.GetSaveString();
		return output;
	}
}
