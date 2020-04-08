#include "Show.h"

void hotkeys() {
	SetConsoleTextAttribute(handle, hotkeys_color);
	gotoxy(hotkeys_x, 0);
	cout << "(ENTER) select";
	gotoxy(hotkeys_x, 1);
	cout << "(▲) UP";
	gotoxy(hotkeys_x, 2);
	cout << "(▼) DOWN";
	gotoxy(hotkeys_x, 3);
	cout << "(ESC) EXIT";
	gotoxy(0, 0);
	SetConsoleTextAttribute(handle, font_color);
}

void action_manager(transaction*& actions, int& actionsCount, string* categories, int countCategories,int index)
{
	int selected_option = 0;
	for (;;)
	{
		int count_lines = 10;
		system("cls");
		hotkeys();
		cout << (actions[index].date.hour < 10 ? "0" : "");
		cout << actions[index].date.hour << ':';
		cout << (actions[index].date.min < 10 ? "0" : "");
		cout << actions[index].date.min << ' ';
		cout << actions[index].details << " " << actions[index].category << " " << actions[index].sum << "$";
		gotoxy(0, count_lines++);
		if (selected_option == -1) {
			SetConsoleTextAttribute(handle, selected_color);
			cout << "Redact" << endl;
			SetConsoleTextAttribute(handle, font_color);
			cout << "Delete";
		}
		else
		{
			cout << "Redact" << endl;
			SetConsoleTextAttribute(handle, selected_color);
			cout << "Delete";
			SetConsoleTextAttribute(handle, font_color);
		}
		switch (_getch())
		{
		case 72://(стрілка в верх)
			if (selected_option >= 0)
			{
				selected_option--;
			}
			break;
		case 80://(стрілка в низ)
			if (selected_option < actionsCount - 1)
			{
				selected_option++;
			}
			break;
		case 13://(Enter)
			if (selected_option == 0)
			{
			//		redact(actions, actionsCount, &Categories, countCategories);
			}
			else
			{
				//		deleting(actions, actionsCount);
			}
		}
	}
}

void menu_income_and_Spend(transaction*& actions, int& actionsCount, string* categories, int countCategories, bool income_Spend)
{
	int selected_option = -1;
	for (;;)
	{
		int count_lines = 10;
		gotoxy(0, count_lines++);
		if (selected_option == -1) {
			SetConsoleTextAttribute(handle, selected_color);
			cout << "Add transaction";
			SetConsoleTextAttribute(handle, font_color);
		}
		else
		{
			cout << "Add transaction";
		}
		dates temp = { 0,0,0,0,0 };
		for (int i = 0; i < actionsCount; i++)
		{
			if (actions[i].incomeSpend==income_Spend)
			{
				if (temp.year != actions[i].date.year && temp.mon != actions[i].date.mon && temp.day != actions[i].date.day)
				{
					SetConsoleTextAttribute(handle, dates_color);
					temp = actions->date;
					gotoxy(10, count_lines);
					cout << actions[i].date.year << '.' << actions[i].date.mon << '.' << actions[i].date.day;
					count_lines++;
					SetConsoleTextAttribute(handle, font_color);
				}
				gotoxy(0, count_lines);
				if (i == selected_option)
				{
					SetConsoleTextAttribute(handle, selected_color);
				}
				else
				{
					SetConsoleTextAttribute(handle, font_color);
				}
				cout << (actions[i].date.hour < 10 ? "0" : "");
				cout << actions[i].date.hour << ':';
				cout << (actions[i].date.min < 10 ? "0" : "");
				cout << actions[i].date.min << ' ';
				cout << actions[i].category << " " << actions[i].sum << "$";
				count_lines++;
			}
		}
		SetConsoleTextAttribute(handle, font_color);
		gotoxy(0, 0);
		switch (_getch())
		{
		case 72://(стрілка в верх)
			if (selected_option >= 0)
			{
				selected_option--;
			}
			break;
		case 80://(стрілка в низ)
			if (selected_option < actionsCount - 1)
			{
				selected_option++;
			}
			break;
		case 13://(Enter)
			system("cls");
			if (selected_option==-1)
			{
				adding(actions, categories, countCategories, actionsCount);
				actions[actionsCount - 1].incomeSpend = income_Spend;
			}
			else
			{
				action_manager(*&actions, actionsCount, categories, countCategories, selected_option);
			}
			break;
		case 27://(Esc) exit
			return;
			break;

		}
		system("cls");
		hotkeys();
	}
}
