#include "IncomesSpends.h"
SYSTEMTIME stime;
FILETIME ltime;
FILETIME ftTimeStamp;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool control = 1;
int balance = 0;
void changingSize(bool addDelete, transaction*& actions, int& actionsCount, int indexDel)
{
	int difference;
	if (addDelete) difference = 1;
	else  difference = -1;
	if (actionsCount == 0) {
		actions = new transaction[actionsCount + difference];
		actionsCount++;
		return;
	}
	transaction* temp = new transaction[actionsCount + difference];
	for (int i = 0; i < actionsCount; i++) {
		if (!addDelete && i >= indexDel) {
			if (i == actionsCount - 1)break;
			temp[i] = actions[i + 1];
			continue;
		}
		else temp[i] = actions[i];
	}
	actions = new transaction[actionsCount + difference];
	actionsCount += difference;
	for (int i = 0; i < actionsCount; i++) {
		actions[i] = temp[i];
	}

	delete[]temp;
}

void deletingCategory(sumAndCat* categories, int countCategories, int index) {
	for (int i = 0; i < countCategories; i++) {
		if (i >= index) {
			if (i == countCategories - 1) {
				categories[i].name == "";
				break;
			}
			categories[i] = categories[i + 1];
		}
	}
}

int adding_category(sumAndCat* categories, int countCategories)
{
	system("cls");
	string bufer = "";
	cout << "Enter name of new category: ";
	cin.ignore();
	getline(cin, bufer);
	for (int i = 0; i < countCategories; i++) {
		if (categories[i].name == "") {
			categories[i].name = bufer;
			return i;
		}
	}
}


int choising_category(sumAndCat categories[], int countCategories) {
	int bufer = 0, y = 2, i = 0;
	char choise = 0;
	cout << "choise the category" << endl;
	for (i = 0; i < countCategories; i++) {
		cout << i + 1 << " " << categories[i].name << endl;
		if (categories[i + 1].name == "")break;
	}
	cout << "\nAdd new category\n";
	gotoxy(0, y);
	do {
		choise = _getch();
		switch (choise) {
		case 72: {
			if (y > 2)y--;
			gotoxy(0, y);
			break;
		}
		case 80: {
			y++;
			gotoxy(0, y);
			break;
		}
		case'\r': {
			if (y <= i + 2)return (y - 2);
			else return adding_category(categories, countCategories);
		}
		}

	} while (choise != 27);


	do {
		cin >> bufer;
		if (bufer <= 0 || bufer > countCategories)cout << "Wrong choise!" << endl;
	} while (bufer <= 0 || bufer > countCategories);
	return (bufer - 1);
}

void adding(transaction*& actions, sumAndCat* categories, int countCategories, int& actionsCount, curency mainCurency)
{
	control = 1;

	GetSystemTimeAsFileTime(&ftTimeStamp);
	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);
	FileTimeToSystemTime(&ltime, &stime);
	int bufer, index = 0;
	int index_selected_category;
	transaction temp;
	changingSize(1, actions, actionsCount, 0);

	cout << "Enter sum of transaction: ";
	do {
		cin >> temp.sum;
		if (temp.sum <= 0)cout << "Wrong sum, write the sum bigger than zero: ";
	} while (temp.sum <= 0);
	temp.sum /= mainCurency.course;
	index_selected_category = choising_category(categories, countCategories);
	temp.category = categories[index_selected_category].name;
	categories[index_selected_category].sum += temp.sum;
	system("cls");
	cout << "Details: ";
	if (control)cin.ignore();
	getline(cin, temp.details);

	temp.date.year = stime.wYear; temp.date.mon = stime.wMonth; temp.date.day = stime.wDay;
	temp.date.hour = stime.wHour; temp.date.min = stime.wMinute;

	actions[actionsCount - 1] = temp;
}
void showActions(bool mode, transaction*& actions, int& actionsCount, curency mainCurency)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	BLUE
		cout << "\t\t\t\t\tBALANCE: " << balance << endl;
	WHITE
		for (int i = actionsCount - 1; i >= 0; i--) {
			cout << "# " << actionsCount - i << "  " << actions[i].date.day << "." << actions[i].date.mon << "." << actions[i].date.year;
			actions[i].date.hour < 10 ? cout << "   0" << actions[i].date.hour << ":" : cout << "    " << actions[i].date.hour << ":";
			actions[i].date.min < 10 ? cout << "0" << actions[i].date.min << endl : cout << actions[i].date.min << endl;
			if (actions[i].incomeSpend) {
				GREEN
					cout << "\t+ ";
			}
			else {
				RED;
				cout << "\t- ";
			}
			cout << actions[i].sum * mainCurency.course << " " << mainCurency.name << endl;
			cout << "\t" << actions[i].category << endl;
			cout << "\t" << actions[i].details << endl << endl;
			WHITE
		}
}

void deleting(transaction*& actions, int& actionsCount)
{
	int bufer = 0;


	cout << "Enter number of action: ";
	do {
		cin >> bufer;
		if (bufer <= 0 || bufer > actionsCount)cout << "Wrong choise!" << endl;
	} while (bufer <= 0 || bufer > actionsCount);

	changingSize(0, actions, actionsCount, actionsCount - bufer);
}


void redact(transaction*& actions, int& actionsCount, sumAndCat* categories, int countCategories, int index, curency& mainCurency)
{
	int bufer = 0;
	do {
		system("cls");


		cout << "1. " << actions[index].sum << endl << "2. " << actions[index].category << endl << "3. " << actions[index].details;
		actions[index].incomeSpend ? cout << "\n4. " << "Income\t\t\t(0-exit)\n" : cout << "\n4. " << "Spend\t\t\t(0-exit)\n";
		cout << "Punkt: ";
		cin >> bufer;
		switch (bufer) {
		case 1: {
			gotoxy(3, 0);
			do {
				if (actions[index].sum <= 0)cout << "Wrong sum! Write the sum bigger than zero: ";
				cin >> actions[index].sum;
			} while (actions[index].sum <= 0);
			break;
		}
		case 2: {
			gotoxy(3, 1);
			system("cls");
			actions[index].category = choising_category(categories, countCategories);
			break;
		}
		case 3: {
			gotoxy(3, 2);
			cin.ignore();
			getline(cin, actions[index].details);
			break;
		}
		case 4: {
			actions[index].incomeSpend = !actions[index].incomeSpend;
			break;
		}
		}
		if (bufer)gotoxy(7, 5);
	} while (bufer);
	system("cls");
}

void curencyManager(curency Curency[], curency& mainCurency)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	int y = 0, i = 0;
	char choise = 0;

	curency temp;
	for (i; i < 20; i++) {
		if (Curency[i].name == "")break;
		cout << "# " << i + 1 << "\t" << Curency[i].name << " (" << Curency[i].course << ")\n";
	}
	BLUE
		cout << " Add new curency\n";
	WHITE
		gotoxy(1, y);
	do {
		choise = _getch();
		switch (choise) {
		case 72: {
			if (y > 0)y--;
			gotoxy(1, y);
			break;
		}
		case 80: {
			if (y < i)y++;
			gotoxy(1, y);
			break;
		}
		case 13: {
			if (y <= i - 1)mainCurency = Curency[y];
			else {
				system("cls");
				cout << "Enter name curency: ";
				cin >> temp.name;
				cout << "Write a course: 1$ =       " << temp.name[0] << temp.name[1] << temp.name[2] << endl;
				gotoxy(21, 1);
				cin >> temp.course;
				mainCurency = temp;
				for (int i = 0; i < 20; i++) {
					if (Curency[i].name == "") {
						Curency[i] = temp;
						break;
					}
				}
			}
		}
		}

	} while (choise != 27 && choise != 13);
	system("cls");
}
