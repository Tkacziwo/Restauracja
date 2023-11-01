#pragma once
#include <string>
#include <sstream>
#include <iomanip>

namespace td
{
	class Date
	{
	protected:
		int Day = 0;
		int Month = 0;
		int Year = 0;
	public:

		Date() {};

		Date(int d, int m, int y) : Day(d), Month(m), Year(y) {};

		Date(std::string& str)
		{
			int pos;
			pos = str.find("-");
			Day = std::stoi(str.substr(0, pos));
			str = str.substr(pos + 1);
			pos = str.find("-");
			Month = std::stoi(str.substr(0, pos));
			str = str.substr(pos + 1);
			Year = std::stoi(str);
		}

		std::string GetDate() const noexcept
		{
			std::string year;
			std::stringstream ss;
			if (Year == 0)
				year = "0000";
			else
				year = std::to_string(Year);

			ss << std::setw(2) << std::setfill('0') << std::to_string(Day) << "-"
				<< std::setw(2) << std::setfill('0') << std::to_string(Month) << "-"
				<< std::setw(4) << std::setfill('0') << year;
			return ss.str();
		}

		std::string GetSaveString() const noexcept
		{
			return std::to_string(Day) + "-" + std::to_string(Month) + "-" + std::to_string(Year);
		}

	};
	std::ostream& operator << (std::ostream& output, const Date& date)
	{
		output << date.GetSaveString();
		return output;
	}
}
