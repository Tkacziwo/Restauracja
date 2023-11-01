#pragma once
#include <sstream>
#include "Entity.h"
#include "Client.h"
#include "ReservationTime.h"
#include <iomanip>

namespace ent
{
	class Reservation : public Entity {
	public:

		int TableId;
		ent::Client Client;
		td::ReservationTime ReservationTime;

		Reservation(const int id, int tableId, const td::ReservationTime& t, const ent::Client& c) :
			Entity(id),
			TableId(tableId),
			ReservationTime(t),
			Client(c) {};

		Reservation(const std::string& res)
		{
			std::string timeHandler;
			std::string clientHandler;
			int pos;
			std::stringstream ss(res);
			ss >> Id
				>> TableId;
			std::getline(ss, timeHandler);
			pos = timeHandler.find("#");
			clientHandler = timeHandler.substr(pos + 1);
			timeHandler = timeHandler.substr(1, pos - 2);
			Client = ent::Client(clientHandler);
			ReservationTime = td::ReservationTime(timeHandler);
		}

		std::string DisplayTemplate() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << "Id:"
				<< std::setw(15) << std::setfill(' ') << std::left << "TableId:"
				<< std::setw(20) << std::setfill(' ') << std::left << "ReservationTime:"
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
			ss << std::setw(15) << std::setfill(' ') << std::left << "TableId:"
				<< std::setw(20) << std::setfill(' ') << std::left << "ReservationTime:"
				<< std::setw(60) << std::setfill(' ') << std::left << "ClientInfo:" << "\n"
				<< std::setw(15) << std::setfill(' ') << std::left << std::to_string(TableId)
				<< std::setw(20) << std::setfill(' ') << std::left << ReservationTime.GetTimeInfo()
				<< std::setw(60) << std::setfill(' ') << std::left << Client.GetClientInfo() << "\n";

			return ss.str();
		}

		std::string GetPartialInfo() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(7) << std::setfill(' ') << std::left << std::to_string(Id)
				<< std::setw(15) << std::setfill(' ') << std::left << std::to_string(TableId)
				<< std::setw(20) << std::setfill(' ') << std::left << ReservationTime.GetTimeInfo()
				<< std::setw(60) << std::setfill(' ') << std::left << Client.GetClientInfo() << "\n";

			return ss.str();
		}

		std::string GetSaveString() const noexcept
		{
			return std::to_string(Id) + " " + std::to_string(TableId) + " " + ReservationTime.GetSaveString() + " #" + Client.GetClientInfo() + "\n";
		}

		void PatchReservationTime(const td::ReservationTime& t)
		{
			ReservationTime = t;
		}

		void PatchClient(const ent::Client& c)
		{
			Client = c;
		}

		void PatchTableId(int tableId)
		{
			TableId = tableId;
		}

	};

	std::ostream& operator << (std::ostream& output, const ent::Reservation& res)
	{
		output << res.GetSaveString();
		return output;
	}
}
