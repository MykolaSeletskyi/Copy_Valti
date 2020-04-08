#include "IncomesSpends.h"

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

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

string adding_category(string* categories, int countCategories)
{
	system("cls");
	string bufer = "";
	cout << "Enter name of new category: ";
	cin.ignore();
	getline(cin, bufer);
	for (int i = 0; i < countCategories; i++) {
		if (categories[i] == "") {
			categories[i] = bufer;
			return bufer;
		}
	}
}


string choising_category(string categories[], int countCategories) {
	int bufer = 0, y = 2, i = 0;
	char choise = 0;
	cout << "choise the category" << endl;
	for (i = 0; i < countCategories; i++) {
		cout << i + 1 << " " << categories[i] << endl;
		if (categories[i + 1] == "")break;
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
			if (y <= i + 2)return categories[y - 2];
			else return adding_category(categories, countCategories);
		}
		}

	} while (choise != 27);


	do {
		cin >> bufer;
		if (bufer <= 0 || bufer > countCategories)cout << "Wrong choise!" << endl;
	} while (bufer <= 0 || bufer > countCategories);
	return categories[bufer - 1];
}

void adding(transaction*& actions, string* categories, int countCategories, int& actionsCount)
{
	SYSTEMTIME stime;
	FILETIME ltime;
	FILETIME ftTimeStamp;

	GetSystemTimeAsFileTime(&ftTimeStamp);
	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);
	FileTimeToSystemTime(&ltime, &stime);

	int bufer, index = 0;
	transaction temp;
	changingSize(1, actions, actionsCount, 0);

	cout << "Enter sum of transaction: ";
	do {
		cin >> temp.sum;
		if (temp.sum <= 0)cout << "Wrong sum, write the sum bigger than zero: ";
	} while (temp.sum <= 0);

	temp.category = choising_category(categories, countCategories);
	system("cls");
	cout << "Details: ";
	cin.ignore();
	getline(cin, temp.details);

	temp.date.year = stime.wYear; temp.date.mon = stime.wMonth; temp.date.day = stime.wDay;
	temp.date.hour = stime.wHour; temp.date.min = stime.wMinute;

	actions[actionsCount - 1] = temp;
}



void showActions(bool mode, transaction*& actions, int& actionsCount)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < actionsCount; i++) {
		cout << "# " << i + 1 << "  " << actions[i].date.day << "." << actions[i].date.mon << "." << actions[i].date.year;
		cout << "   " << actions[i].date.hour << ":" << actions[i].date.min << endl;
		if (actions[i].incomeSpend)GREEN
		else RED;
		cout << "\t" << actions[i].sum << endl;
		cout << "\t" << actions[i].category << endl;
		cout << "\t" << actions[i].details << endl << endl;
		WHITE
	}
}

void deleting(transaction*& actions, int& actionsCount)
{
	int bufer = 0;

	showActions(1, actions, actionsCount);
	cout << "Enter number of action: ";
	do {
		cin >> bufer;
		if (bufer <= 0 || bufer > actionsCount)cout << "Wrong choise!" << endl;
	} while (bufer <= 0 || bufer > actionsCount);

	changingSize(0, actions, actionsCount, bufer - 1);
}


void redact(transaction*& actions, int& actionsCount, categor* categories, int countCategories, int index)
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
			if (actions[index].incomeSpend)actions[index].category = choising_category(categories->incomeCategories, countCategories);
			else actions[index].category = choising_category(categories->spendCategories, countCategories);
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