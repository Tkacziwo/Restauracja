#pragma once

namespace ent
{
	class Delivery : public Entity
	{
	protected:
		int EmployeeId = 0;
		std::string Order;
		ut::Address Address;
		ent::Client Client;
	public:

		Delivery(std::string& str)
		{
			std::string clientName;
			std::string clientSurname;
			std::string clientContactNumber;
			int pos;
			std::stringstream ss(str);
			ss >> Id >> EmployeeId;
			str = str.substr(4);
			pos = str.find("$");
			Order = str.substr(0, pos - 1);
			str = str.substr(pos + 1);
			std::stringstream ss1(str);
			ss1 >> clientName >> clientSurname >> clientContactNumber;
			ent::Person p(clientName, clientSurname);
			Client = ent::Client(p, clientContactNumber);
			std::string addressHandler;
			int addressPos = str.find("#");
			addressHandler = str.substr(addressPos + 1);
			Address = ut::Address(addressHandler);
		}

		Delivery(int id, int employeeId, ent::Client& client, const std::string& order) :
			Entity(id),
			EmployeeId(employeeId),
			Client(client),
			Order(order) {};

		std::string DisplayTemplate() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << "Id:"
				<< std::setw(15) << std::setfill(' ') << std::left << "EmployeeId:"
				<< std::setw(40) << std::setfill(' ') << std::left << "DeliveryAddress:"
				<< std::setw(60) << std::setfill(' ') << std::left << "ClientInfo:" << "\n";
			return ss.str();
		}

		std::string DisplayPartialTemplate() const noexcept
		{
			return DisplayTemplate();
		}

		std::string GetInfo() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << std::to_string(Id)
				<< std::setw(15) << std::setfill(' ') << std::left << std::to_string(EmployeeId)
				<< std::setw(40) << std::setfill(' ') << std::left << Address.GetAddress()
				<< std::setw(60) << std::setfill(' ') << std::left << Client.GetClientInfo() << "\n";

			return ss.str();
		}

		std::string GetPartialInfo() const noexcept
		{
			return GetInfo();
		}

		std::string GetSaveString() const noexcept
		{
			return std::to_string(Id) + " " + std::to_string(EmployeeId) + " " + Order + " $" + Client.GetClientInfo() + "#" + Address.GetSaveString() + "\n";
		}

		void PatchOrder(const std::string& o)
		{
			Order = o;
		}

		void PatchClient(const ent::Client c)
		{
			Client = c;
		}

		void PatchEmployeeId(int employeeId)
		{
			EmployeeId = employeeId;
		}

	};

	std::ostream& operator << (std::ostream& output, const ent::Delivery& del)
	{
		output << del.GetSaveString();
		return output;
	}
}
