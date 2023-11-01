#include <iostream>
#include "RestaurantController.h"
#include <stdlib.h>

void MainMenu(rest::Restaurant& rest)
{
	char userHandler;
	do
	{
		system("CLS");
		std::cout << "Welcome to main menu, press H to get help\n>>";
		std::cin >> userHandler;
		switch (userHandler)
		{
		case 'S':
		case 's':
		{
			system("CLS");
			rest.Select();
			userHandler = 0;
			break;
		}

		case 'C':
		case 'c':
		{
			system("CLS");
			rest.Create();
			userHandler = 0;
			break;
		}

		case 'R':
		case 'r':
		{
			system("CLS");
			rest.Remove();
			userHandler = 0;
			break;
		}
		case 'G':
		case 'g':
		{
			system("CLS");
			rest.ChooseCollection();
			userHandler = 0;
			break;
		}
		case 'M':
		case 'm':
		{
			rest.Modify();
			userHandler = 0;
			break;
		}
		case 'H':
		case 'h':
		{
			system("CLS");
			ut::DisplayInfoNumber(2);
			system("pause");
			userHandler = 0;
			break;
		}
		default:
		{
			system("CLS");
			break;
		}
		}


	} while (userHandler != 'q');
}

int main()
{
	rest::Restaurant rest;

	rest.FetchDatabase("database.txt");
	MainMenu(rest);

	rest.SaveDatabase("database2.txt");

	return 0;
}