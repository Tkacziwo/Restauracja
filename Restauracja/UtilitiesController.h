#pragma once
#include <vector>
#include <string>

namespace ut
{
	template<typename T>
	void GetCollection(const std::vector<T>& vec)
	{
		std::cout << vec[0].DisplayTemplate();
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i].GetInfo() << "\n";
		}
	}

	template<typename T>
	void GetPartialCollection(const std::vector<T>& vec)
	{
		std::cout << vec[0].DisplayPartialTemplate();
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i].GetPartialInfo();
		} 
	}

	template<typename T>
	T& GetById(int id, std::vector<T>& vec)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i].GetEntityId() == id)
			{
				return vec[i];
			}
		}
	}

	template<typename T>
	int GetPositionInVector(int id, std::vector<T> vec)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i].GetEntityId() == id)
			{
				return i;
			}
		}
	}

	template<typename T>
	int FindMaxId(std::vector<T> vec)
	{
		int maxId = vec[0].GetEntityId();
		for (size_t i = 1; i < vec.size(); i++)
		{
			if (maxId < vec[i].GetEntityId())
			{
				maxId = vec[i].GetEntityId();
			}
		}
		return maxId;
	}

	template<typename T>
	bool CheckIfExist(int id, const std::vector<T>& vec)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i].GetEntityId() == id)
			{
				return true;
			}
		}
		std::cout << "Not Found\n";
		system("pause");
		return false;
	}

	void DisplayInfoNumber(int i)
	{
		switch (i)
		{
		case 1:
			std::cout << "1. Tables\n 2. Employees\n 3. Reservations\n 4. Deliveries\n";
			break;
		case 2:
			std::cout << "S - Select, M - Modify, C - Create, R - Remove\n G - Choose collection, Q - Quit, H - Display this info box\n";
			break;
		case 3:
			std::cout << "1. Tables\n 2. Employees\n 3. Reservations\n 4. Deliveries\n 5. Help\n 6. Quit\n 7. Generate Detailed Report\n 8. Generate Partial Report\n>>";
			break;
		case 4:
			std::cout << "1. Cook\n 2. Waiter\n 3. Delivery\n 4. Manager\n 5.Accountant\n";
			break;
		case 5:
			std::cout << "1. Name, 2. Surname 3. Salary, 4. Occupation, 5. Address\n";
			break;
		case 6:
			std::cout << "1. Table, 2. Client, 3. Reservation Time\n";
			break;
		case 7:
			std::cout << "1. Tables\n2. Employees\n3. Reservations\n4. Deliveries\n5. Save Detailed Report\n6. Save Partial Report\n7. Save Distinct Report\n";
			break;
		default:
			break;
		}
	}

	bool IsNumber(const std::string& str)
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]))
			{
				return false;
			}
		}
		return true;
	}

	bool IsFloatNumber(const std::string& str)
	{
		int floatingPoint;
		floatingPoint = str.find(".");
		for (size_t i = 0; i < str.length(); i++)
		{
			if (floatingPoint != i)
			{
				if (!isdigit(str[i]))
				{
					return false;
				}
			}

		}
		return true;
	}

	int IntInputter()
	{
		std::string handler;

		while (true)
		{
			std::cout << ">>";
			std::getline(std::cin >> std::ws, handler);
			if (IsNumber(handler))
				return std::stoi(handler);
			else
				std::cout << "Not a number!\nProvide valid number\n";
		}
	}

	float FloatInputter()
	{
		std::string handler;

		while (true)
		{
			std::cout << ">>";
			std::getline(std::cin >> std::ws, handler);
			if (IsFloatNumber(handler))
				return std::stof(handler);
			else
				std::cout << "Not a valid float number!\n Provide valid number\n";
		}
	}

	std::string StringInputter()
	{
		std::string str;

		while (true)
		{
			std::cout << ">>";
			std::getline(std::cin >> std::ws, str);
			if (!IsNumber(str))
				return str;
			else
				std::cout << "Number detected, provide valid string\n";
		}
	}

	std::string ContactNumberInputter()
	{
		std::string str;

		while (true)
		{
			std::cout << ">>";
			std::getline(std::cin >> std::ws, str);
			if (str.length() != 9 ||   !IsNumber(str))
				std::cout << "Provide valid contact number!\n";
			else
				return str;
		}
	}

	std::string MenuInputter()
	{
		std::string str;

		while (true)
		{
			std::cout << ">>";
			std::getline(std::cin >> std::ws, str);
			if (str != "")
			{
				if (str == "q" || str == "Q")
					return "-1";
				if (str == "m" || str == "M")
					return "-2";
				if (str == "y" || str == "Y")
					return "-3";
				if (IsNumber(str))
					return str;
				else
					std::cout << "Wrong input!\n";
			}
		}
	}

	std::string OccupationSelector()
	{
		bool loop;
		std::string occupation;
		int inputHandler;
		std::cout << "Provide occupation\n>>";
		ut::DisplayInfoNumber(4);
		do
		{
			inputHandler = ut::IntInputter();
			switch (inputHandler)
			{
			case 1:
			{
				occupation = "Cook";
				loop = 0;
				break;
			}
			case 2:
			{
				occupation = "Waiter";
				loop = 0;
				break;
			}
			case 3:
			{
				occupation = "Delivery";
				loop = 0;
				break;
			}
			case 4:
			{
				occupation = "Manager";
				loop = 0;
				break;
			}
			case 5:
			{
				occupation = "Accountant";
				loop = 0;
				break;
			}
			default:
				break;
			}

		} while (loop);
		return occupation;
	}

	Address AddAddress()
	{
		std::string city;
		std::string street;
		std::string postalCode;
		int houseNumber;

		while (true)
		{
			std::cout << "City:\n";
			city = ut::StringInputter();
			if (!city.empty())
			{
				break;
			}
		}

		while (true)
		{
			std::cout << "Street:\n";
			street = ut::StringInputter();
			if (!street.empty())
			{
				break;
			}
		}

		while (true)
		{
			std::cout << "Postal code:\n";
			postalCode = ut::StringInputter();
			if (!postalCode.empty())
			{
				break;
			}
		}

		while (true)
		{
			std::cout << "House number:\n";
			houseNumber = ut::IntInputter();
			if (houseNumber != 0)
			{
				break;
			}
		}

		ut::Address address(city, street, postalCode, houseNumber);
		return address;
	}
}