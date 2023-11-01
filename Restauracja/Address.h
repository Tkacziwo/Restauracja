#pragma once
#include <string>
#include <sstream>

namespace ut
{
	class Address
	{
	protected:
		std::string City = "";
		std::string Street = "";
		std::string PostalCode = "";
		int HouseNumber = 0;
	public:

		Address() {};

		Address(std::string& a)
		{
			int position;
			position = a.find("%");

			City = a.substr(0, position);
			a = a.substr(position + 1);
			std::stringstream ss(a);
			ss	>> Street
				>> PostalCode
				>> HouseNumber;
		}

		Address(const std::string& city, const std::string& street, const std::string& postalCode, int houseNumber) :
			City(city),
			Street(street),
			PostalCode(postalCode),
			HouseNumber(houseNumber) {};

		std::string GetAddress() const noexcept
		{
			return City + " " + Street + " " + PostalCode + " " + std::to_string(HouseNumber);
		}

		std::string GetSaveString() const noexcept
		{
			return City + " %" + Street + " " + PostalCode + " " + std::to_string(HouseNumber);
		}

		void PatchCity(const std::string& city)
		{
			City = city;
		}

		void PatchStreet(const std::string& street)
		{
			Street = street;
		}

		void PatchPostalCode(const std::string& pc)
		{
			PostalCode = pc;
		}

		void PatchHouseNumber(int houseNumber)
		{
			HouseNumber = houseNumber;
		}
	};

	std::ostream& operator << (std::ostream& output, const Address& a)
	{
		output << a.GetSaveString() << "\n";
		return output;
	}
}