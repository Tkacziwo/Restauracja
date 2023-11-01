#pragma once
#include <iostream>
#include "Client.h"
#include "Person.h"
#include "UtilitiesController.h"
#include "TimeAndDateController.h"

namespace ent
{
	Person AddPerson(int mode)
	{
		std::string name;
		std::string surname;

		if (mode == 0)
		{
			while (true)
			{
				system("cls");
				std::cout << "Provide employee name\n";
				name = ut::StringInputter();
				if (!name.empty())
				{
					break;
				}
			}

			while (true)
			{
				system("cls");
				std::cout << "Provide employee surname\n";
				surname = ut::StringInputter();
				if (!name.empty())
				{
					break;
				}
			}

			td::Date date = td::AddEmployeeDateOfBirth();
			Person person(name, surname, date);
			person.AddDateOfBirth(date);
			return person;

		}
		else
		{
			while (true)
			{
				system("cls");
				std::cout << "Provide client name\n";
				name = ut::StringInputter();
				if (!name.empty())
				{
					break;
				}
			}

			while (true)
			{
				system("cls");
				std::cout << "Provide client surname\n";
				surname = ut::StringInputter();
				if (!name.empty())
				{
					break;
				}
			}

			Person person(name, surname);
			return person;
		}

	}

	Client AddClientReturnable()
	{
		std::string contactNumber;
		Person person = AddPerson(1);
		std::cout << "Give contact number\n";
		contactNumber = ut::ContactNumberInputter();
		Client e(person, contactNumber);
		return e;
	}

	std::string AddOrder()
	{
		std::string desc;
		std::cout << "Give description of what you want\n";
		std::getline(std::cin >> std::ws, desc);
		return desc;
	}
}