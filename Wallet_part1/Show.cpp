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

void action_manager(transaction*& actions, int& actionsCount, sumAndCat* categories, int index, curency& mainCurency)
{
	int selected_option = 0;
	for (;;)
	{
		int count_lines = 5;
		system("cls");
		hotkeys();
		cout << (actions[index].date.hour < 10 ? "0" : "");
		cout << actions[index].date.hour << ':';
		cout << (actions[index].date.min < 10 ? "0" : "");
		cout << actions[index].date.min << ' ';
		cout << actions[index].category << " " << floor(actions[index].sum * mainCurency.course * 100) / 100 << " " << mainCurency.name;
		gotoxy(0, count_lines++);
		if (selected_option == 0) {
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
			if (selected_option > 0)
			{
				selected_option--;
			}
			break;
		case 80://(стрілка в низ)
			if (selected_option < actionsCount)
			{
				selected_option++;
			}
			break;
		case 13://(Enter)
			if (selected_option == 0)
			{
				redact(actions, actionsCount, categories, countCategories, index, mainCurency);
			}
			else
			{
				changingSize(0, actions, actionsCount, selected_option - 1);
			}
		case 27://(Esc) exit
			return;
			break;
		}
	}
}
void diagram_categories(transaction*& actions, int& actionsCount, sumAndCat* categories, COORD coord_diagram, int size_diagram) {
	int size_c = size_diagram / 9;//size circle
	int distance_c = size_diagram / 6.5;//distance circle
	float temp_sum = 0;
	for (int i = 0; i < countCategories; i++)
	{
		temp_sum += categories[i].sum;
	}
	temp_sum = 360 / temp_sum;
	int r = size_diagram / 2;
	COORD end = { coord_diagram.X + size_diagram,coord_diagram.Y + r };
	COORD center = { coord_diagram.X + r, coord_diagram.Y + r };
	int temp_angle = 0;
	for (int i = 0; i < countCategories; i++)
	{
		if (categories[i].sum)
		{
			SelectObject(hdc, CreateSolidBrush(color[i]));
			Ellipse(hdc, coord_diagram.X + size_diagram, coord_diagram.Y + distance_c * i, coord_diagram.X + size_diagram + size_c, size_c + coord_diagram.Y + distance_c * i);
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, 0);
			TextOutA(hdc, coord_diagram.X + size_diagram + size_c, coord_diagram.Y + distance_c * i, categories[i].name.c_str(), categories[i].name.size());
			temp_angle += (categories[i].sum * temp_sum);
			double rad = temp_angle * 3.14 / 180;
			COORD beg = { (r * cos(rad) + center.X),(r * sin(rad) + center.Y) };
			SelectObject(hdc, CreateSolidBrush(color[i]));
			Pie(hdc, coord_diagram.X, coord_diagram.Y, coord_diagram.X + size_diagram, coord_diagram.Y + size_diagram, beg.X, beg.Y, end.X, end.Y);
			end = beg;
		}
	}
}
void menu_income_and_Spend(transaction*& actions, int& actionsCount, sumAndCat* categories, bool income_Spend, curency& mainCurency)
{
	COORD coord_diagram = { 300,70 };
	int size_diagram = 100;
	int selected_option = actionsCount;
	hotkeys();
	for (;;)
	{
		int count_lines = transaction_x - 1;
		gotoxy(0, count_lines++);
		if (selected_option == actionsCount) {
			SetConsoleTextAttribute(handle, selected_color);
			cout << "Add transaction";
			SetConsoleTextAttribute(handle, font_color);
		}
		else
		{
			cout << "Add transaction";
		}
		dates temp = { 0,0,0,0,0 };
		for (int i = actionsCount - 1; i >= 0; i--)
		{
			if (actions[i].incomeSpend == income_Spend)
			{
				if (temp.year != actions[i].date.year && temp.mon != actions[i].date.mon && temp.day != actions[i].date.day)
				{
					SetConsoleTextAttribute(handle, dates_color);
					temp = actions->date;
					gotoxy(10, count_lines++);
					cout << actions[i].date.year << '.' << actions[i].date.mon << '.' << actions[i].date.day;
					SetConsoleTextAttribute(handle, font_color);
				}
				gotoxy(0, count_lines++);
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
				cout << actions[i].category << " " << floor(actions[i].sum * mainCurency.course * 100) / 100 << " " << mainCurency.name;
			}
		}
		SetConsoleTextAttribute(handle, font_color);
		gotoxy(0, 0);
		diagram_categories(actions, actionsCount, categories, coord_diagram, size_diagram);
		switch (_getch())
		{
		case 72://(стрілка в верх)

			if (selected_option < actionsCount)
			{
				for (int i = selected_option; i < actionsCount; i++)
				{
					if (i + 1 == actionsCount)
					{
						selected_option = i + 1;
						break;
					}
					if (actions[i + 1].incomeSpend == income_Spend)
					{
						selected_option = i + 1;
						break;
					}
				}
			}
			break;
		case 80://(стрілка в низ)

			if (selected_option > 0)
			{
				for (int i = selected_option; i > 0; i--)
				{
					if (actions[i - 1].incomeSpend == income_Spend)
					{
						selected_option = i - 1;
						break;
					}
				}
			}
			break;
		case 13://(Enter)
			system("cls");
			if (selected_option == actionsCount)
			{
				adding(actions, categories, countCategories, actionsCount, mainCurency);
				actions[actionsCount - 1].incomeSpend = income_Spend;
			}
			else
			{
				action_manager(*&actions, actionsCount, categories, selected_option, mainCurency);
			}
			system("cls");
			selected_option = actionsCount;
			hotkeys();
			break;
		case 27://(Esc) exit
			return;
			break;
		}
	}
}
void transactionsByTime(transaction actions[], int& actionsCount, curency& mainCurency)
{
	SYSTEMTIME stime;
	FILETIME ltime;
	FILETIME ftTimeStamp;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetSystemTimeAsFileTime(&ftTimeStamp);
	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);
	FileTimeToSystemTime(&ltime, &stime);

	float dayIncome = 0, IncomeByweek = 0, IncomeByMon = 0, IncomeByYear = 0,
		spendByDay = 0, spendByWeek = 0, spendByMon = 0, spendByYear = 0;
	int i = 0;

	while (actions[i].date.day == stime.wDay) {
		if (actions[i].category == "")break;
		actions[i].incomeSpend ? dayIncome += actions[i].sum : spendByDay += actions[i].sum;
		i++;
	}

	while (actions[i].date.day >= stime.wDay - stime.wDayOfWeek) {
		if (i >= actionsCount)break;
		actions[i].incomeSpend ? IncomeByweek += actions[i].sum : spendByWeek += actions[i].sum;
		i++;
	}

	while (actions[i].date.mon == stime.wMonth) {
		if (i >= actionsCount)break;
		actions[i].incomeSpend ? IncomeByMon += actions[i].sum : spendByMon += actions[i].sum;
		i++;
	}

	while (actions[i].date.year == stime.wYear) {
		if (i >= actionsCount)break;
		actions[i].incomeSpend ? IncomeByYear += actions[i].sum : spendByYear += actions[i].sum;
		i++;
	}

	IncomeByweek += dayIncome;
	spendByWeek += spendByDay;
	IncomeByMon += IncomeByweek;
	spendByMon += spendByWeek;
	IncomeByYear += IncomeByMon;
	spendByYear += spendByMon;

	unsigned char block = 176;
	system("cls");
	for (i = 0; i <= 12; i++) {
		for (int j = 0; j <= 40; j++) {
			if (i == 0 || i == 12 || i == 6 || j == 0 || j == 20 || j == 40) {
				GREEN
					cout << block;
				WHITE
			}
			else cout << " ";

		}
		cout << endl;
	}

	gotoxy(3, 2);
	cout << "Incomes today";
	gotoxy(4, 4);
	cout << floor(dayIncome * mainCurency.course * 100) / 100;

	gotoxy(22, 2);
	cout << "Incomes by week";
	gotoxy(23, 4);
	cout << floor(IncomeByweek * mainCurency.course * 100) / 100;

	gotoxy(2, 8);
	cout << "Incomes by mounth";
	gotoxy(4, 10);
	cout << floor(IncomeByMon * mainCurency.course * 100) / 100;

	gotoxy(22, 8);
	cout << "Incomes by year";
	gotoxy(23, 10);
	cout << floor(IncomeByYear * mainCurency.course * 100) / 100;

	gotoxy(0, 20);
}
