#pragma once
#include "Reservations.h"
#include "employee.h"
#include "Table.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Entity.h"
#include "Client.h"
#include "Deliveries.h"
#include <iomanip>
#include <stdlib.h>
#include "FileController.h"
#include "UtilitiesController.h"
#include "Date.h"
#include "ReservationTime.h"
#include <ctime>
#include "TimeAndDateController.h"
#include "ModificationController.h"
#include "EntityController.h"

namespace rest {

	class Restaurant {
		int MaxTables = 64;
		std::vector<ent::Table> Tables;
		std::vector<ent::Reservation> Reservations;
		std::vector<ent::Employee> Employees;
		std::vector<ent::Delivery> Deliveries;

	public:

		std::vector<ent::Entity*> DataReport;

		void SaveDetailedDataReport()
		{
			std::string inputHandler;
			std::cout << "Provide output file name (without file extension):\n";
			inputHandler = ut::StringInputter();
			inputHandler += ".txt";
			std::ofstream output(inputHandler);
			output << "Tables: " << Tables.size() << "\n";
			ut::SaveSingleReport(Tables, DataReport);
			SaveReportDetailed(DataReport, output);
			output << "Reservations: " << Reservations.size() << "\n";
			ut::SaveSingleReport(Reservations, DataReport);
			SaveReportDetailed(DataReport, output);
			output << "Employees: " << Employees.size() << "\n";
			ut::SaveSingleReport(Employees, DataReport);
			SaveReportDetailed(DataReport, output);
			output << "Deliveries: " << Deliveries.size() << "\n";
			ut::SaveSingleReport(Deliveries, DataReport);
			SaveReportDetailed(DataReport, output);

			output.close();
		}

		template<typename T>
		void SaveDistinctReport(const std::vector<T>& vec, std::string temp)
		{
			std::string inputHandler;
			std::cout << "Provide output file name (without file extension):\n";
			inputHandler = ut::StringInputter();
			inputHandler += ".txt";
			std::ofstream output(inputHandler);
			output << temp << ":" << vec.size()<<"\n";
			for (size_t i = 0; i < vec.size(); i++)
			{
				output << vec[i].GetInfo()<<"\n";
			}
			output.close();
			
		}

		void ChooseDistinctReport()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "Which collection to save? Type q to leave\n";
				ut::DisplayInfoNumber(1);
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
						SaveDistinctReport(Tables, "Tables");
						break;
					case 2:
						SaveDistinctReport(Employees, "Employees");
						break;
					case 3:
						SaveDistinctReport(Reservations, "Reservations");
						break;
					case 4:
						SaveDistinctReport(Deliveries, "Deliveries");
						break;
					default:
						break;
					}
				}

			} while (loop);
		}

		void SaveReportDetailed(std::vector<ent::Entity*>& report, std::ofstream& output)
		{
			for (const auto& ent : report)
			{
				output << ent->GetInfo() << "\n";

			}
			for (size_t i = 0; i < report.size(); i++)
			{
				delete report[i];
			}
			report.clear();
		}

		void SaveReportPartial(std::vector<ent::Entity*>& report, std::ofstream& output)
		{
			for (const auto& ent : report)
			{
				output << report[0]->DisplayPartialTemplate();
				output << ent->GetPartialInfo() << "\n";

			}
			for (size_t i = 0; i < report.size(); i++)
			{
				delete report[i];
			}
			report.clear();
		}

		void SavePartialDataReport()
		{
			std::string inputHandler;
			std::cout << "Provide output file name (without file extension):\n";
			inputHandler = ut::StringInputter();
			inputHandler += ".txt";
			std::ofstream output(inputHandler);
			output << "Tables: " << Tables.size() << "\n";
			ut::SaveSingleReport(Tables, DataReport);
			SaveReportPartial(DataReport, output);
			output << "Reservations: " << Reservations.size() << "\n";
			ut::SaveSingleReport(Reservations, DataReport);
			SaveReportPartial(DataReport, output);
			output << "Employees: " << Employees.size() << "\n";
			ut::SaveSingleReport(Employees, DataReport);
			SaveReportPartial(DataReport, output);
			output << "Deliveries: " << Deliveries.size() << "\n";
			ut::SaveSingleReport(Deliveries, DataReport);
			SaveReportPartial(DataReport, output);

			output.close();
		}

		void FetchDatabase(const std::string& database)
		{
			std::fstream db(database);
			std::string handler;
			std::string name;
			int noofrows;
			while (std::getline(db, handler))
			{
				std::stringstream ss(handler);
				ss >> name >> noofrows;
				if (name == "Employee")
				{
					ut::GetSingleCategory(db, Employees, noofrows);
				}
				if (name == "Table")
				{
					ut::GetSingleCategory(db, Tables, noofrows);
				}
				if (name == "Reservation")
				{
					ut::GetSingleCategory(db, Reservations, noofrows);
				}
				if (name == "Delivery")
				{
					ut::GetSingleCategory(db, Deliveries, noofrows);
				}
			}
			db.close();
		}

		void SaveDatabase(const std::string& database)
		{
			std::ofstream db(database);
			ut::SaveSingleCategory(db, Employees, "Employee");
			ut::SaveSingleCategory(db, Tables, "Table");
			ut::SaveSingleCategory(db, Reservations, "Reservation");
			ut::SaveSingleCategory(db, Deliveries, "Delivery");
			db.close();
		}

		void AddTable()
		{
			bool loop;
			std::string inputHandler;
			do
			{
				system("cls");
				std::cout << "Give number of seats. Type q to quit\n";
				inputHandler = ut::MenuInputter();

				if (inputHandler == "-1")
					loop = 0;
				else if (inputHandler == "0")
					std::cout << "Cannot assign 0 as valid number of seats\n";
				else
					loop = 1;

				if (loop)
				{
					int numberOfSeats = std::stoi(inputHandler);
					if (numberOfSeats != 0)
					{
						if (Tables.empty())
						{
							ent::Table t(0, numberOfSeats);
							Tables.push_back(t);
						}
						else
						{
							int maxId = ut::FindMaxId(Tables);
							ent::Table t(maxId + 1, numberOfSeats);
							Tables.push_back(t);
						}
					}
				}
			} while (loop);
		}

		void RemoveTable(int tableId)
		{
			Tables.erase(Tables.begin() + ut::GetPositionInVector(tableId, Tables));
		}

		void AddReservation()
		{
			bool loop;
			std::string inputHandler;
			do
			{
				system("cls");
				std::cout << "Please select which table to reserve. Type q to quit\n";
				ut::GetCollection(Tables);
				inputHandler = ut::MenuInputter();

				if (inputHandler == "-1")
					loop = 0;
				else
					loop = 1;

				if (loop)
				{
					int tableId = std::stoi(inputHandler);
					if (ut::CheckIfExist(tableId, Tables))
					{

						ent::Table& t = ut::GetById(tableId, Tables);
						if (t.IsTableFree())
						{
							ent::Client client = ent::AddClientReturnable();
							td::ReservationTime time = td::AddReservationTime();
							if (Reservations.empty())
							{
								ent::Reservation r(0, tableId, time, client);
								Reservations.push_back(r);
							}
							else
							{
								int maxId = ut::FindMaxId(Reservations);
								ent::Reservation r(maxId + 1, tableId, time, client);
								Reservations.push_back(r);
							}
							t.ReserveTable();
						}
						else
						{
							std::cout << "Table is already taken!\n";
							system("pause");
						}
					}
				}
			} while (loop);
		}

		void RemoveReservation(int reservationId)
		{
			ent::Reservation& r = ut::GetById(reservationId, Reservations);
			ent::Table& t = ut::GetById(r.TableId, Tables);
			t.ReleaseTable();
			Reservations.erase(Reservations.begin() + ut::GetPositionInVector(reservationId, Reservations));
		}

		void AddEmployee()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "You're about to create an employee. Type q to quit. Type y to continue\n";
				inputHandler = ut::MenuInputter();

				if (inputHandler == "-1")
					loop = 0;
				if (inputHandler == "-3")
				{
					loop = 1;
					float salary;
					ent::Person person = ent::AddPerson(0);
					std::string occupation = ut::OccupationSelector();
					std::cout << "Provide salary\n";
					salary = ut::FloatInputter();

					ut::Address address = ut::AddAddress();

					if (Employees.size() == 0)
					{
						ent::Employee e(0, salary, occupation, person, address);
						Employees.push_back(e);
					}
					else
					{
						int maxId = ut::FindMaxId(Employees);
						ent::Employee e(maxId + 1, salary, occupation, person, address);
						Employees.push_back(e);
					}
				}
			} while (loop);
		}

		void RemoveEmployee(int employeeId)
		{
			Employees.erase(Employees.begin() + ut::GetPositionInVector(employeeId, Employees));
		}

		void AddDelivery()
		{
			bool loop;
			std::string inputHandler;
			int handler;

			do
			{
				system("cls");
				std::cout << "You're about to create delivery. Type q to leave. Type y to continue\n";
				inputHandler = ut::MenuInputter();
				if (inputHandler == "-1")
					loop = 0;
				if (inputHandler == "-3")
				{
					loop = 1;
					std::cout << "Assign employee\n";
					GetEmployeeFilteredCollection("Delivery");
					handler = ut::IntInputter();
					ent::Client client = ent::AddClientReturnable();
					std::string order = ent::AddOrder();
					if (Deliveries.size() == 0)
					{
						ent::Delivery delivery(0, handler, client, order);
						Deliveries.push_back(delivery);
					}
					else
					{
						int maxId = ut::FindMaxId(Deliveries);
						ent::Delivery delivery(maxId + 1, handler, client, order);
						Deliveries.push_back(delivery);
					}
				}
			} while (loop);


		}

		void RemoveDelivery(int deliveryId)
		{
			Deliveries.erase(Deliveries.begin() + ut::GetPositionInVector(deliveryId, Deliveries));
		}

		void GetEmployeeFilteredCollection(const std::string& filter, int choice = 0)
		{
			for (size_t i = 0; i < Employees.size(); i++)
			{
				if (Employees[i].GetOccupation() == filter)
				{
					std::cout << Employees[i].GetPartialInfo();
				}
			}
		}

		void ChooseCollection()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "Which collection to choose? Type q to leave\n";
				ut::DisplayInfoNumber(7);
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
						ut::GetPartialCollection(Tables);
						system("pause");
						break;
					case 2:
						ut::GetPartialCollection(Employees);
						system("pause");
						break;
					case 3:
						ut::GetPartialCollection(Reservations);
						system("pause");
						break;
					case 4:
						ut::GetPartialCollection(Deliveries);
						system("pause");
						break;
					case 5:
						SaveDetailedDataReport();
						break;
					case 6:
						SavePartialDataReport();
						break;
					case 7:
						ChooseDistinctReport();
						break;
					default:
						break;
					}
				}
			} while (loop);
		}

		template<typename T>
		void HandleModify(const std::vector<T>& vec, int mode)
		{
			std::string inputHandler;
			bool loop;
			int option;

			do
			{

				system("cls");
				std::cout << "Modify:\n";
				std::cout << "Type q or Q to quit\n";
				ut::GetPartialCollection(vec);
				inputHandler = ut::MenuInputter();

				if (inputHandler == "-1")
					loop = 0;
				else
					loop = 1;

				if (loop)
				{
					option = std::stoi(inputHandler);
					if (ut::CheckIfExist(option, vec))
					{
						switch (mode)
						{

						case 1:
						{
							ent::Table& t = ut::GetById(option, Tables);
							mod::ModifyTable(t);
							break;
						}
						case 2:
						{
							ent::Employee& e = ut::GetById(option, Employees);
							mod::ModifyEmployee(e);
							break;
						}
						case 3:
						{
							ent::Reservation& r = ut::GetById(option, Reservations);
							mod::ModifyReservation(r, Reservations, Tables);
							break;
						}
						case 4:
						{
							ent::Delivery& d = ut::GetById(option, Deliveries);
							mod::ModifyDelivery(d);
							break;
						}
						default:
							break;
						}
					}
				}
			} while (loop);
		}


		void Modify()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "What to modify? Type q to quit\n";
				ut::DisplayInfoNumber(1);
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
					{
						HandleModify(Tables, 1);
						break;
					}
					case 2:
					{
						HandleModify(Employees, 2);
						break;
					}
					case 3:
					{
						HandleModify(Reservations, 3);
						break;
					}
					case 4:
					{
						HandleModify(Deliveries, 4);
						break;
					}
					}
				}
			} while (loop);
		}

		void Create()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "What to create, press q to quit\n";
				ut::DisplayInfoNumber(1);
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
						AddTable();
						break;
					case 2:
						AddEmployee();
						break;
					case 3:
						AddReservation();
						break;
					case 4:
						AddDelivery();
						break;
					default:
						break;
					}
				}
			} while (loop);

		}

		template<typename T>
		void HandleRemove(const std::vector<T>& vec, int mode)
		{
			int option;
			std::string inputHandler;
			bool loop;

			do
			{

				system("cls");
				std::cout << "Remove:\n";
				std::cout << "Type q or Q to quit\n";
				ut::GetPartialCollection(vec);
				inputHandler = ut::MenuInputter();

				if (inputHandler == "-1")
					loop = 0;
				else
					loop = 1;

				if (loop)
				{
					option = std::stoi(inputHandler);
					if (ut::CheckIfExist(option, vec))
					{
						std::cout << "Are you sure remove item of Id:" << option << "\nType y to confirm, q to quit\n";
						inputHandler = ut::MenuInputter();
						if (inputHandler == "-3")
						{
							switch (mode)
							{
							case 1:
								RemoveTable(option);
								break;
							case 2:
								RemoveEmployee(option);
								break;
							case 3:
								RemoveReservation(option);
								break;
							case 4:
								RemoveDelivery(option);
								break;
							default:
								break;
							}
						}
						if (inputHandler == "-1")
						{
							break;
						}
					}
				}
			} while (loop);

		}

		void Remove()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "What to remove? Type q to quit\n";
				ut::DisplayInfoNumber(1);
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
						HandleRemove(Tables, 1);
						break;
					case 2:
						HandleRemove(Employees, 2);
						break;
					case 3:
						HandleRemove(Reservations, 3);
						break;
					case 4:
						HandleRemove(Deliveries, 4);
						break;
					default:
						break;
					}
				}
			} while (loop);
		}

		template<typename T>
		void HandleSelect(std::vector<T>& vec, int mode)
		{
			std::string inputHandler;
			bool loop;
			int option;

			do
			{
				system("cls");
				std::cout << "Select:\n";
				std::cout << "Type q or Q to quit\n";
				ut::GetPartialCollection(vec);
				inputHandler = ut::MenuInputter();

				if (inputHandler == "-1")
					loop = 0;
				else
					loop = 1;

				if (loop)
				{
					option = std::stoi(inputHandler);
					if (ut::CheckIfExist(option, vec))
					{
						switch (mode)
						{
						case 1:
						{
							ent::Table& obj = ut::GetById(option, Tables);
							std::cout << obj.GetInfo();
							std::cout << "Type m to modify, random key to leave\n";
							inputHandler = ut::MenuInputter();
							if (inputHandler == "-2")
							{
								mod::ModifyTable(obj);
								break;
							}
							else
							{
								break;
							}
						}
						case 2:
						{
							ent::Employee& obj = ut::GetById(option, Employees);
							std::cout << obj.GetInfo();
							std::cout << "Type m to modify, random key to leave\n";
							inputHandler = ut::MenuInputter();
							if (inputHandler == "-2")
							{
								mod::ModifyEmployee(obj);
								break;
							}
							else
							{
								break;
							}
						}
						case 3:
						{
							ent::Reservation& obj = ut::GetById(option, Reservations);
							std::cout << obj.GetInfo();
							std::cout << "Type m to modify, random key to leave\n";
							inputHandler = ut::MenuInputter();
							if (inputHandler == "-2")
							{
								mod::ModifyReservation(obj, Reservations, Tables);
								break;
							}
							else
							{
								break;
							}
						}
						case 4:
						{
							ent::Delivery& obj = ut::GetById(option, Deliveries);
							std::cout << obj.GetInfo();
							std::cout << "Type m to modify, random key to leave\n";
							inputHandler = ut::MenuInputter();
							if (inputHandler == "-2")
							{
								mod::ModifyDelivery(obj);
								break;
							}
							else
							{
								break;
							}
						}
						}
					}
				}

			} while (loop);
		}

		void Select()
		{
			bool loop;
			std::string inputHandler;

			do
			{
				system("cls");
				std::cout << "What would you like to select? Type q to quit\n";
				ut::DisplayInfoNumber(1);
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
						HandleSelect(Tables, 1);
						break;
					case 2:
						HandleSelect(Employees, 2);
						break;
					case 3:
						HandleSelect(Reservations, 3);
						break;
					case 4:
						HandleSelect(Deliveries, 4);
						break;
					default:
						break;
					}
				}
			} while (loop);
		}
	};
};