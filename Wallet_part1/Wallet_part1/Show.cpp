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
	gotoxy(hotkeys_x, 5);
	cout << "(F1) Open calculator";
	gotoxy(hotkeys_x, 6);
	cout << "(F11) Callendary";
	SetConsoleTextAttribute(handle, font_color);
}

void action_manager(transaction*& actions, int& actionsCount, sumAndCat* categories, int index, curency& mainCurency, double* sum_categor)
{
	BOOL selected_option = true;
	for (;;)
	{
		int count_lines = 5;
		system("cls");
		hotkeys();
		gotoxy(0, 0);
		cout << (actions[index].date.hour < 10 ? "0" : "");
		cout << actions[index].date.hour << ':';
		cout << (actions[index].date.min < 10 ? "0" : "");
		cout << actions[index].date.min << ' ';
		cout << actions[index].category << " " << double_to_string(actions[index].sum, mainCurency) << " " << mainCurency.name << "\n";
		cout << actions[index].details << "\n";
		gotoxy(0, count_lines++);
		if (selected_option) {
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
		case 72:
			selected_option = true;
			break;
		case 80:
			selected_option = false;
			break;
		case 13://(Enter)
			if (selected_option)
			{
				redact(actions, actionsCount, categories, countCategories, index, mainCurency);
			}
			else
			{
				for (int i = 0; i < countCategories; i++) {
					if (categories[i].name == actions[index].category) {
						categories[i].sum -= actions[index].sum;
						*sum_categor -= actions[index].sum;
						break;
					}
				}
				changingSize(0, actions, actionsCount, index);
				return;
			}
			break;
		case 133: 
			CalendMenu();
			break;
		case 59:
			system("start calc");
			break;
		case 27://(Esc) exit
			return;
			break;
		}
	}
}
void diagram_categories(transaction*& actions, int& actionsCount, sumAndCat* categories, COORD coord_diagram, int size_diagram) {
	Sleep(50);
	int size_c = size_diagram / 9;//size circle
	int distance_c = size_diagram / 6.5;//distance circle
	float temp_sum = 0;
	for (int i = 0; i < countCategories; i++)
	{
		if (categories[i].name == "")break;
		temp_sum += categories[i].sum;
	}
	temp_sum = 360 / temp_sum;
	int r = size_diagram / 2;
	COORD end = { coord_diagram.X + size_diagram,coord_diagram.Y + r };
	COORD center = { coord_diagram.X + r, coord_diagram.Y + r };
	int temp_angle = 0;
	SetTextAlign(hdc, NULL);
	SetBkMode(hdc, NULL);
	SetTextColor(hdc, RGB(255, 255, 255));
	for (int i = 0; i < countCategories; i++)
	{
		if (categories[i].name=="")break;
		if (categories[i].sum)
		{
			SelectObject(hdc, CreateSolidBrush(color[i]));
			Ellipse(hdc, coord_diagram.X + size_diagram, coord_diagram.Y + distance_c * i, coord_diagram.X + size_diagram + size_c, size_c + coord_diagram.Y + distance_c * i);
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
void menu_income_and_Spend(transaction*& actions, int& actionsCount, sumAndCat* categories, bool income_Spend, curency& mainCurency, double* sum_categor)
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
				if (temp.year != actions[i].date.year || temp.mon != actions[i].date.mon || temp.day != actions[i].date.day)
				{
					SetConsoleTextAttribute(handle, dates_color);
					temp = actions[i].date;
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
				cout << actions[i].category << " " << double_to_string(actions[i].sum, mainCurency) << " " << mainCurency.name;
			}
		}
		SetConsoleTextAttribute(handle, font_color);
		gotoxy(0, 0);
		diagram_categories(actions, actionsCount, categories, coord_diagram, size_diagram);
		switch (_getch())
		{
		case 72:
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
		case 80:
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
		case 59:
			system("start calc");
			break;
		case 13://(Enter)
			for (int i = 0; i < 40; i++) {
				for (int j = 0; j < 20; j++)cout << "\t";
			}
			system("cls");

			if (selected_option == actionsCount)
			{
				adding(actions, categories, countCategories, actionsCount, mainCurency);
				actions[actionsCount - 1].incomeSpend = income_Spend;
				*sum_categor += actions[actionsCount - 1].sum;
			}
			else
			{
				action_manager(*&actions, actionsCount, categories, selected_option, mainCurency, sum_categor);
			}
			system("cls");
			selected_option = actionsCount;
			hotkeys();
			break;
		case 27://(Esc) exit


			system("cls");
			return;
			break;
		}
	}
}
void show_transactionsByTime(COORD a, string* str, string* numbers, int* color) {
	SetTextColor(hdc, RGB(0, 0, 0));
	SetTextAlign(hdc, TA_CENTER);
	SetBkMode(hdc, 0);
	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			a.Y = a.Y + 40;
			a.X = a.X - 120 * (i - 1);
		}
		else if (i != 0)
		{
			a.X = a.X + 120;
		}
		SelectObject(hdc, CreateSolidBrush(color[i]));
		Rectangle(hdc, a.X, a.Y, a.X + 120, a.Y + 40);
		TextOutA(hdc, a.X + 60, a.Y, str[i].c_str(), str[i].size());
		TextOutA(hdc, a.X + 60, a.Y + 20, numbers[i].c_str(), numbers[i].size());
		SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
	}
}
void transactionsByTime(transaction actions[], int& actionsCount, curency& mainCurency)
{
	Sleep(50);
	SYSTEMTIME stime;
	FILETIME ltime;
	FILETIME ftTimeStamp;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetSystemTimeAsFileTime(&ftTimeStamp);
	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);
	FileTimeToSystemTime(&ltime, &stime);
	double income[4] = { 0 };
	double spend[4] = { 0 };
	int i = actionsCount - 1;

	while (actions[i].date.day == stime.wDay) {
		if (i < 0)break;
		actions[i].incomeSpend ? income[0] += actions[i].sum : spend[0] += actions[i].sum;
		i--;
	}

	while (actions[i].date.day >= stime.wDay - (stime.wDayOfWeek == 0 ? 7 : stime.wDayOfWeek)) { // неділя == 0, тому треба переводити, інакше не порахує
		if (i < 0)break;																		// транзакції за неділю
		actions[i].incomeSpend ? income[1] += actions[i].sum : spend[1] += actions[i].sum;
		i--;
	}

	while (actions[i].date.mon == stime.wMonth) {
		if (i < 0)break;
		actions[i].incomeSpend ? income[2] += actions[i].sum : spend[2] += actions[i].sum;
		i--;
	}

	while (actions[i].date.year == stime.wYear) {
		if (i < 0)break;
		actions[i].incomeSpend ? income[3] += actions[i].sum : spend[3] += actions[i].sum;
		i--;
	}

	income[1] += income[0];   income[2] += income[1];   income[3] += income[2];
	spend[1] += spend[0];   spend[2] += spend[1];     spend[3] += spend[2];

	string str[4] = { "today" ,"by year" ,"by week" ," by mounth" };
	string income_str[4];
	string spend_str[4];
	int color_income[4] = { 6091105, 2944305, 1233175, 958739 };
	int color_spend[4] = { 9076469, 6180338, 3218670, 2035653 };
	for (int i = 0; i < 4; i++)
	{
		income_str[i] = double_to_string(income[i], mainCurency);
		spend_str[i] = double_to_string(spend[i], mainCurency);
 	}
	show_transactionsByTime({ 250, 90 }, str, income_str, color_income);
	show_transactionsByTime({ 250, 190 }, str, spend_str, color_spend);
}

void show_balance(COORD coord_zero, double sum_income, double sum_spend, curency& mainCurency)
{
	int ratio;
	ratio = (int(sum_income*100) > int(sum_spend * 100) ? 0 : (int(sum_income * 100) < int(sum_spend * 100) ? 1 : 2));
	string name_file;
	if (ratio != 2)
	{
		name_file = "weigh.txt";
	}
	else
	{
		name_file = "weigh_equal.txt";
	}
	ifstream fin(name_file);
	if (!fin.is_open()) {
		cout << "Error: File not opend!" << " (" << name_file << ")" << endl;
		system("pause");
		system("cls");
		return;
	}

	int count_x = 0;
	int count_y = 0;
	string str_temp;
	fin >> str_temp;
	int size_str = str_temp.size() + 1;

	//draws weigh 
	while (!fin.eof())
	{
		if (fin.get() == '0')
		{
			SetPixel(hdc, count_x + coord_zero.X, count_y + coord_zero.Y, (count_y > 124 ? RGB(0, 0, 192) : RGB(128, 128, 128)));
		}
		if (ratio == 0)
		{
			if (count_x == 0)
			{
				count_x = size_str;
				count_y++;
			}
			count_x--;
		}
		if (ratio == 1 || ratio == 2)
		{
			if (count_x == size_str)
			{
				count_x = 0;
				count_y++;
			}
			count_x++;
		}
	}

	COORD coord[2][3] = { {{25, 67},{25, 44},{25, 56}}, {{117, 45},{117, 66},{120, 56}} };//coordinates for displaying the balance

	SetTextAlign(hdc, TA_CENTER);
	SetBkMode(hdc, 1);
	SetTextColor(hdc, RGB(100, 255, 0));

	str_temp = double_to_string(sum_income, mainCurency);
	TextOutA(hdc, coord[0][ratio].X + coord_zero.X, coord[0][ratio].Y + coord_zero.Y, str_temp.c_str(), str_temp.size());//reflects income
	SetTextColor(hdc, RGB(255, 0, 100));

	str_temp = double_to_string(sum_spend, mainCurency);
	TextOutA(hdc, coord[1][ratio].X + coord_zero.X, coord[1][ratio].Y + coord_zero.Y, str_temp.c_str(), str_temp.size());//reflects spend

	//reflects balance
	switch (ratio)//reflects balance
	{
	case 0:
		SetTextColor(hdc, RGB(100, 255, 0));

		break;
	case 1:
		SetTextColor(hdc, RGB(255, 0, 100));
		break;
	case 2:
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOutA(hdc, 73 + coord_zero.X, 140 + coord_zero.Y, "ZERO", 4);
		SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
		return;
	}
	str_temp = double_to_string(double(sum_income - sum_spend), mainCurency);
	TextOutA(hdc, 73 + coord_zero.X, 140 + coord_zero.Y, str_temp.c_str(), str_temp.size());
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
}
string double_to_string(double number, curency& mainCurency)
{
	string res;
	res += to_string(int(number * mainCurency.course * 100) / 100);
	res += '.';
	res += to_string(abs(int((number * mainCurency.course - (int(number * mainCurency.course))) * 100)));
	return res;
}