#include <iostream>
#include<string>
#include<fstream>
#include "IncomesSpends.h"
#include <conio.h>
#include "Show.h"
using namespace std;


int actionsCount = 0;


transaction* actions = new transaction[actionsCount];
categor Categories;

int main() {

	Categories.incomeCategories[0] = "Other";
	Categories.incomeCategories[1] = "Premia";
	Categories.spendCategories[0] = "Food";
	Categories.spendCategories[1] = "Other";

	hotkeys();

	string menu_items[] = { "Income","Spend","Settings" };
	int selected_option = 0;
	for (;;)
	{

		//39-61  виводимо остані транзакції
		if (actionsCount)
		{
			dates temp = { 0,0,0,0,0 };
			int count_lines = 10;
			for (int i = actionsCount-1; i >= 0; i--)
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
				cout << actions[i].category << " " << actions[i].sum << "$";
				count_lines++;
				if (i == 15)//15 кількість виводу транзакцій
				{
					break;
				}
			}
			SetConsoleTextAttribute(handle, font_color);
		}

		for (int i = 0; i < size(menu_items); i++)
		{
			gotoxy(60, i);
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
		case 72://(стрілка в верх)
			if (selected_option > 0)
			{
				selected_option--;
			}
			break;
		case 80://(стрілка в низ)
			if (selected_option < size(menu_items) - 1)
			{
				selected_option++;
			}
			break;
		case 13://(Enter)
			system("cls");
					switch (selected_option)
					{
					case 0://доходи					
						menu_income_and_Spend(*&actions, actionsCount, Categories.incomeCategories, countCategories,1);

						break;
					case 1://расходи
						menu_income_and_Spend(*&actions, actionsCount, Categories.spendCategories, countCategories,0);
						//adding(actions, Categories.incomeCategories, countCategories, actionsCount);
						//actions[actionsCount - 1].incomeSpend = 1;
						//adding(actions, Categories.spendCategories, countCategories, actionsCount);
						//actions[actionsCount - 1].incomeSpend = 0;
						break;
					case 2://настройки
						////настойок нема
						break;
					}
				system("cls");
				hotkeys();
			break;
		case 27://(Esc) exit
			return 0;
			break;
		}

		//		deleting(actions, actionsCount);

		//		redact(actions, actionsCount, &Categories, countCategories);



	}
	system("pause");
	return 0;
}