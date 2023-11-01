#pragma once

namespace ent {
	class Table : public Entity {
		int NumberOfSeats;
		bool IsTaken = 0;
	public:

		Table(const std::string& str)
		{
			std::stringstream ss(str);
			ss >> Id
				>> NumberOfSeats
				>> IsTaken;
		}

		Table(int id, int numberOfSeats) : Entity(id), NumberOfSeats(numberOfSeats) {};

		void ReserveTable()
		{
			IsTaken = true;
		}

		void ReleaseTable()
		{
			IsTaken = false;
		}

		bool IsTableFree()
		{
			if (IsTaken == true)
				return false;
			return true;
		}

		std::string DisplayTemplate() const noexcept
		{
			std::stringstream ss;
			ss << std::setw(3) << std::setfill(' ') << "Id:" 
				<< std::setw(15) << std::setfill(' ') << "NumberOfSeats:" 
				<< std::setw(10) << std::setfill(' ') << "IsTaken:" << "\n";
			return ss.str();
		}

		std::string DisplayPartialTemplate() const noexcept
		{
			return DisplayTemplate();
		}

		std::string GetInfo() const noexcept
		{
			std::string text;
			std::stringstream ss;
			if (IsTaken == true)
				text = "True";
			else
				text = "False";

			ss << std::setw(7) << std::setfill(' ') << std::left << std::to_string(Id)
				<< std::setw(15) << std::setfill(' ') << std::to_string(NumberOfSeats)
				<< std::setw(10) << std::setfill(' ') << text << "\n";

			return ss.str();
		}

		std::string GetPartialInfo() const noexcept
		{
			return GetInfo();
		}

		std::string GetSaveString() const noexcept
		{
			std::string text;
			if (IsTaken == true)
				text = "True";
			else
				text = "False";
			return std::to_string(Id) + " " + std::to_string(NumberOfSeats) + " " + text + "\n";
		}

		void PatchNumberOfSeats(int numberOfSeats)
		{
			NumberOfSeats = numberOfSeats;
		}

		void PatchIsTaken(bool isTaken)
		{
			IsTaken = isTaken;
		}
	};
	std::ostream& operator << (std::ostream& output, const Table& t)
	{
		output << t.GetSaveString();
		return output;
	}
}