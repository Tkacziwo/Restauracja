#pragma once
#include <iostream>
#include "EntityController.h"

namespace mod
{
	void ModifyEmployee(ent::Employee& e)
	{
		bool loop;
		std::string inputHandler;
		int option;
		do
		{
			system("cls");
			std::cout << "Current properties:\n";
			std::cout << e.GetInfo();
			std::cout << "\nWhat to modify? Type q to leave\n";
			ut::DisplayInfoNumber(5);
			inputHandler = ut::MenuInputter();
			if (inputHandler == "-1")
				loop = 0;
			else
				loop = 1;
			if (loop)
			{
				option = std::stoi(inputHandler);
				switch (option)
				{
				case 1:
				{
					std::cout << "Provide new name\n";
					std::string name = ut::StringInputter();
					e.PatchName(name);
					break;
				}
				case 2:
				{
					std::cout << "Provide new surname\n";
					std::string surname = ut::StringInputter();
					e.PatchSurname(surname);
					break;
				}
				case 3:
				{
					std::cout << "Provide new salary\n";
					float salary = ut::FloatInputter();
					e.PatchSalary(salary);
					break;
				}
				case 4:
				{
					std::cout << "Provide new occupation\n";
					std::string occupation = ut::OccupationSelector();
					e.PatchOccupation(occupation);
					break;
				}
				case 5:
				{
					std::cout << "Provide new address\n";
					ut::Address address = ut::AddAddress();
					e.PatchAddress(address);
					break;
				}
				default:
					break;
				}
			}

		} while (loop);
	}

	void ModifyTable(ent::Table& table)
	{
		bool loop;
		std::string inputHandler;

		do
		{
			system("cls");
			std::cout << "Current properties:\n";
			std::cout << table.GetInfo();
			std::cout << "Type q to leave\n";
			std::cout << "Modify number of seats\n";
			inputHandler = ut::MenuInputter();

			if (inputHandler == "-1")
				loop = 0;
			else
				loop = 1;
			if (loop)
			{
				table.PatchNumberOfSeats(std::stoi(inputHandler));
			}
		} while (loop);
	}

	void ChangeTableNumber(ent::Reservation& res, std::vector<ent::Table>& tables)
	{
		bool loop;
		std::string inputHandler;
		int tableId;

		do
		{
			system("cls");
			std::cout << "Which table to change to?\nType q to leave";
			ut::GetPartialCollection(tables);
			inputHandler = ut::MenuInputter();

			if (inputHandler == "-1")
				loop = 0;
			else
				loop = 1;

			if (loop)
			{
				tableId = std::stoi(inputHandler);
				if (ut::CheckIfExist(tableId, tables))
				{
					ent::Table& oldTable = ut::GetById(res.TableId, tables);
					ent::Table& table = ut::GetById(tableId, tables);

					if (table.IsTableFree())
					{
						res.TableId = tableId;
						table.ReserveTable();
						oldTable.ReleaseTable();
					}
				}
			}
		} while (loop);
	}

	void ModifyDelivery(ent::Delivery& d)
	{
		std::string o = ent::AddOrder();
		ent::Client c = ent::AddClientReturnable();
		d.PatchOrder(o);
		d.PatchClient(c);
	}

	void ModifyReservation(ent::Reservation& res, std::vector<ent::Reservation>& reservations, std::vector<ent::Table>& tables)
	{
		bool loop;
		std::string inputHandler;
		int option;

		do
		{

			system("cls");
			std::cout << "Current properties:\n";
			std::cout << res.GetInfo();
			std::cout << "\nWhat to modify? Type q to leave\n";
			ut::DisplayInfoNumber(6);
			inputHandler = ut::MenuInputter();
			if (inputHandler == "-1")
				loop = 0;
			else
				loop = 1;

			if (loop)
			{
				switch (std::stoi(inputHandler))
				{
				case 1:
					ChangeTableNumber(res, tables);
					break;
				case 2:
					res.PatchClient(ent::AddClientReturnable());
					break;
				case 3:
					res.PatchReservationTime(td::AddReservationTime());
					break;
				default:
					break;
				}
			}
		} while (loop);
	}

	void ModifyClient(ent::Client& c)
	{
		std::string name;
		std::string surname;
		std::string contactNumber;
		std::cout << "Provide name:\n";
		name = ut::StringInputter();
		std::cout << "Provide surname:\n";
		surname = ut::StringInputter();
		std::cout << "Provide contact number:\n";
		contactNumber = ut::StringInputter();

		c.PatchName(name);
		c.PatchSurname(surname);
		c.PatchClientContactNumber(contactNumber);
	}
}