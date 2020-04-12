#include <iostream>
#include<string>
#include<fstream>
#include "IncomesSpends.h"
#include "Inits.h"
#include "Show.h"
#include <conio.h>
#include <cmath>
using namespace std;
int main() {
	int actionsCount = 0;

	transaction* actions = new transaction[actionsCount];

	/*int com = 2320, spe = 600, ccom = 0, cspe = 0;
	if (com > spe) {
		ccom = 10;
		cspe = float(10 / (float(com) / spe));
	}
	else {
		cspe = 10;
		ccom= float(10 / (float(spe) / com));
	}
	for (int i = 10; i >= 0; i--) {
		if (i <= ccom) {
			SetConsoleTextAttribute(handle, 35);
			cout << " ";
			SetConsoleTextAttribute(handle, 15);
		}
		else cout << " ";
		cout << "  ";
		if (i <= cspe) {
			SetConsoleTextAttribute(handle, 64);
			cout << " ";
			SetConsoleTextAttribute(handle, 15);
		}
		else cout << " ";
		cout << "\n";

		system("pause");
	}*/

	
	
	curency Curency[15];
	Curency[0].name = "dol";
	Curency[0].course = 1;

	sumAndCat incomeCategories[countCategories];
	sumAndCat spendCategories[countCategories];


	curency mainCurency = Curency[0];

	initCurrency(Curency,mainCurency);
	initActions(actions, actionsCount,incomeCategories,spendCategories);
	reading_categories(incomeCategories, 1);
	reading_categories(spendCategories, 0);

	string menu_items[] = { "Income","Spend","Settings" }; 
	int selected_option = 0;
	BOOL refresh = true;
	for (;;)
	{
		if (actionsCount&& refresh)
		{
			dates temp = { 0,0,0,0,0 };
			int count_lines = transaction_x;
			for (int i = actionsCount - 1; i >= 0; i--)
			{
				if (temp.year != actions[i].date.year || temp.mon != actions[i].date.mon || temp.day != actions[i].date.day)
				{
					SetConsoleTextAttribute(handle, dates_color);
					temp = actions[i].date;
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
		hotkeys();
		gotoxy(48, 2);
		SetConsoleTextAttribute(handle, font_color);
		transactionsByTime(actions, actionsCount, mainCurency); 
		refresh = false;
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

				menu_income_and_Spend(*&actions, actionsCount,incomeCategories, 1, mainCurency);
				refresh = true;
				break;
			case 1:
				menu_income_and_Spend(*&actions, actionsCount,spendCategories, 0, mainCurency);
				refresh = true;
				break;
			case 2:
				char choise = 0;
				int index = 0;
				do {
					system("cls");
					cout << "1. Delete cat\t\t\t\t(esc) exit\n2. Course\n3. COncole color\n";
					choise = _getch();
					switch (choise) {
					case 49: {
						cout << "1-Incomes categories 0-Spends categories: ";
						cin >> index;
						if (index) {
							for (int i = 0; i < countCategories; i++) {
								if (incomeCategories[i].name != "")cout << "# " << i + 1 << " " << incomeCategories[i].name << endl;
							}
							do {
								cout << "Enter number of action: ";
								cin >> index;
								if (index <= 0 || index > countCategories)cout << "Wrong choise!" << endl;
							} while (index <= 0 || index > countCategories);
							deletingCategory(incomeCategories, countCategories, index - 1);
						}
						else {
							for (int i = 0; i < countCategories; i++) {
								if (spendCategories[i].name != "")cout << "# " << i + 1 << spendCategories[i].name << endl;
							}
							do {
								cout << "Enter number of action: ";
								cin >> index;
								if (index <= 0 || index > countCategories)cout << "Wrong choise!" << endl;
							} while (index <= 0 || index > countCategories);
							deletingCategory(spendCategories, countCategories, index - 1);
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
				refresh = true;
					break;
			}
			system("cls");
			hotkeys();
			break;
		case 27://(Esc) exit
			writing_categories(incomeCategories, 1);
			writing_categories(spendCategories, 0);
			exitInitCurency(Curency, mainCurency);
			exitInitActions(actions, actionsCount);
			return 0;
			break;
		}
	}
	delete[] actions;
	system("pause");
	return 0;
}