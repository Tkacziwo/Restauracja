#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace ut
{
	template<typename T>
	void GetSingleCategory(std::fstream& db, std::vector<T>& v, int noofrows)
	{
		for (size_t i = 0; i < noofrows; i++)
		{
			std::string handler;
			std::getline(db, handler);
			T e(handler);
			v.push_back(e);
		}
	}

	template<typename T>
	void SaveSingleCategory(std::ofstream& db, const std::vector<T>& v, const std::string& name)
	{
		int vecSize = v.size();
		std::string handler = name + " " + std::to_string(vecSize);
		db << handler << "\n";
		for (size_t i = 0; i < vecSize; i++)
		{
			db << v[i];
		}
	}

	template<typename T>
	void SaveSingleReport(const std::vector<T>& vec, std::vector<ent::Entity*>& DataReport)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			DataReport.push_back(new T(vec[i]));
		}
	}
}
