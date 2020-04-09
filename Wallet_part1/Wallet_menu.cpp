#include <iostream>
#include<string>
#include<fstream>
#include "IncomesSpends.h"
#include <conio.h>
#include "Show.h"
#include <cmath>
using namespace std;
int main() {
	int actionsCount = 0;

	transaction* actions = new transaction[actionsCount];


	categor Categories;
	curency Curency[20];
	Curency[0].name = "dol";
	Curency[0].course = 1;

	Categories.incomeCategories[0].name = "Other";
	Categories.incomeCategories[1].name = "Premia";
	Categories.spendCategories[0].name = "Food";
	Categories.spendCategories[1].name = "Other";

	curency mainCurency = Curency[0];



	hotkeys();

	string menu_items[] = { "Income","Spend","Settings" };
	int selected_option = 0;
	for (;;)
	{
		if (actionsCount)
		{
			dates temp = { 0,0,0,0,0 };
			int count_lines = transaction_x;
			for (int i = actionsCount - 1; i >= 0; i--)
			{
				if (temp.year != actions[i].date.year && temp.mon != actions[i].date.mon && temp.day != actions[i].date.day)
				{
					SetConsoleTextAttribute(handle, dates_color);
					temp = actions->date;
					gotoxy(10, count_lines);
					cout << actions[i].date.year << '.' << actions[i].date.mon << '.' << actions[i].date.day;
					count_lines++;
				}
				gotoxy(0, count_lines);
				SetConsoleTextAttribute(handle, (actions[i].incomeSpend ? 32 : 64));
				cout << (actions[i].date.hour < 10 ? "0" : "");
				cout << actions[i].date.hour << ':';
				cout << (actions[i].date.min < 10 ? "0" : "");
				cout << actions[i].date.min << ' ';
				cout << actions[i].category << " " << floor(actions[i].sum * mainCurency.course * 100) / 100 << " " << mainCurency.name;
				count_lines++;
				if (i == 15)
				{
					break;
				}
			}
			SetConsoleTextAttribute(handle, font_color);
		}

		for (int i = 0; i < size(menu_items); i++)
		{
			gotoxy(menu_x, i);
			if (selected_option == i)
			{
				SetConsoleTextAttribute(handle, selected_color);
				cout << menu_items[i];
				SetConsoleTextAttribute(handle, font_color);
			}
			else
			{
				cout << menu_items[i];
			}
		}
		gotoxy(0, 0);
		switch (_getch())
		{
		case 72://up
			if (selected_option > 0)
			{
				selected_option--;
			}
			break;
		case 80://down
			if (selected_option < size(menu_items) - 1)
			{
				selected_option++;
			}
			break;
		case 13://(Enter)
			system("cls");
			switch (selected_option)
			{
			case 0:			
				menu_income_and_Spend(*&actions, actionsCount, Categories.incomeCategories, 1, mainCurency);

				break;
			case 1:
				menu_income_and_Spend(*&actions, actionsCount, Categories.spendCategories, 0, mainCurency);
				break;
			case 2: {
				char choise = 0;
				int index = 0;
				do {
					system("cls");
					transactionsByTime(actions, actionsCount, mainCurency);
					cout << "1. Delete cat\t\t\t\t(esc) exit\n2. Course\n";
					choise = _getch();
					switch (choise) {
					case 49: {
						cout << "1-Incomes categories 0-Spends categories: ";
						cin >> index;
						if (index) {
							for (int i = 0; i < countCategories; i++) {
								if (Categories.incomeCategories[i].name != "")cout << "# " << i + 1 << " " << Categories.incomeCategories[i].name << endl;
							}
							do {
								cout << "Enter number of action: ";
								cin >> index;
								if (index <= 0 || index > countCategories)cout << "Wrong choise!" << endl;
							} while (index <= 0 || index > countCategories);
							deletingCategory(Categories.incomeCategories, countCategories, index - 1);
						}
						else {
							for (int i = 0; i < countCategories; i++) {
								if (Categories.spendCategories[i].name != "")cout << "# " << i + 1 << Categories.spendCategories[i].name << endl;
							}
							do {
								cout << "Enter number of action: ";
								cin >> index;
								if (index <= 0 || index > countCategories)cout << "Wrong choise!" << endl;
							} while (index <= 0 || index > countCategories);
							deletingCategory(Categories.spendCategories, countCategories, index - 1);
						}
						break;
					}
					case 50: {
						curencyManager(Curency, mainCurency);
						break;
					}

					}
					cout << "\n\n";
				} while (choise != 27);
				choise = 0;
				system("cls");
			}
				  break;
			}
			system("cls");
			hotkeys();
			break;
		case 27://(Esc) exit
			return 0;
			break;
		}
	}

	system("pause");
	return 0;
}