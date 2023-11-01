#pragma once
#include <iomanip>
#include "Usings.h"
#include "Date.h"
#include "Time.h"

namespace td {
	class ReservationTime {

		td::Date Date;
		//Utilities::Time Time;
		int Hour;
		int Minute;
	public:

		ReservationTime() {}

		ReservationTime(const td::Date& d, int hour, int minute) : Date(d), Hour(hour), Minute(minute) {};

		ReservationTime(const std::string& str)
		{
			std::string handler;
			std::stringstream ss(str);
			ss >> Hour
				>> Minute;
			std::getline(ss, handler);
			Date = td::Date(handler);
		}

		std::string GetTimeInfo() const noexcept
		{
			std::string minute;
			std::stringstream ss;
			if (Minute == 0)
				minute = "00";
			else
				minute = std::to_string(Minute);

			ss << std::setw(2) << std::setfill('0') << std::to_string(Hour) << ":"
				<< std::setw(2) << std::setfill('0') << minute << " " << Date.GetDate();

			return	 ss.str();
		}

		std::string GetSaveString() const noexcept
		{
			std::string minute;
			if (Minute == 0)
				minute = "00";
			else
				minute = std::to_string(Minute);
			return	 std::to_string(Hour) + " " + minute + " " + Date.GetDate();
		}

		bool IsTimeFree()
		{
			return true;
		}
	};
	std::ostream& operator <<(std::ostream& output, ReservationTime t)
	{
		output << t.GetTimeInfo();
		return output;
	}
}