#pragma once
#include "UtilitiesController.h"
#include "Date.h"
#include "ReservationTime.h"
#include <ctime>
#include <iostream>

namespace td
{
	int GetDaysInMonth(int year, int month)
	{
		int a1[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int a2[12]{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (year % 4 == 0)
			return a2[month - 1];
		else
			return a1[month - 1];
	}
	
	Date& AddEmployeeDateOfBirth()
	{
		int day, month, year, daysInMonth;
		std::cout << "Provide year of birth\n";
		while (true)
		{
			year = ut::IntInputter();
			if (year < 0)
				std::cout << "Invalid input!\n";
			else
				break;
		}
		std::cout << "Provide month\n";
		while (true)
		{

			month = ut::IntInputter();
			if (month > 12 || month < 0)
				std::cout << "Invalid input!\n";
			else
				break;
		}
		std::cout << "Provide day\n";
		while (true)
		{
			daysInMonth = GetDaysInMonth(year, month);
			day = ut::IntInputter();
			if (day > daysInMonth || day < 0)
				std::cout << "Invalid input!\n";
			else
				break;
		}
		Date d(day, month, year);
		return d;
	}

	Date& AddDate()
	{
		struct tm newTime;
		int day, month, year, daysInMonth;
		time_t now = time(0);
		localtime_s(&newTime, &now);

		year = 1900 + newTime.tm_year;
		std::cout << "Provide month\n";
		while (true)
		{

			month = ut::IntInputter();
			if (month > 12 || month < 0)
				std::cout << "Invalid input!\n";
			else
				break;
		}
		std::cout << "Provide day\n";
		while (true)
		{
			daysInMonth = GetDaysInMonth(year, month);
			day = ut::IntInputter();
			if (day > daysInMonth || day < 0)
				std::cout << "Invalid input!\n";
			else
				break;
		}
		Date d(day, month, year);
		return d;
	}

	ReservationTime AddReservationTime()
	{
		int hour, minute;
		Date date = AddDate();
		std::cout << "Provide hour\n";
		while (true)
		{
			hour = ut::IntInputter();
			if (hour > 24 || hour < 0)
				std::cout << "Invalid input!\n>>";
			else
				break;
		}

		std::cout << "Provide minute\n";
		while (true)
		{
			minute = ut::IntInputter();
			if (minute > 60 || minute < 0)
				std::cout << "Invalid input!\n>>";
			else
				break;
		}

		ReservationTime t(date, hour, minute);
		return t;
	}
}
