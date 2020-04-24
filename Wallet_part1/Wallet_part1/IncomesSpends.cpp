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

double inputSecure() {
	bool control = 1;  // informs about which digit is inputing now( integer or fraction)
	char partSum = 0;  // bufer for numbers, reads only 0-9 / enter / dot
	int numberFraction = 0;  // if control=0 we write a fraction number, for delete we have count posision of curently fraction number
	double fractionSum = 0, sum=0;  // for countin and assamble digit
	sum = 0;
	do {
		partSum = _getch();
		if (partSum == 8) { // pressed backscape 
			cout << "\b \b";  // correct output by cursor posisin
			control ? sum = int(sum / 10) : fractionSum = int(fractionSum / 10); // reducing integer or fraction by one rank
			if (!control)numberFraction--;  //if cursor is on fractions we're reducin posision 
			if (!numberFraction)control = 1;  // if posision of fractions cursor is 0, return to countin integer
		}
		if (partSum >= 48 && partSum<= 57 || (partSum == 46&&control))cout << partSum;  // show only numbers or dot (dot shows only 1 time)

		if (partSum >= 48 && partSum <= 57) {
			if (control) sum = sum * 10 + partSum - 48;
			else {
				fractionSum = fractionSum * 10 + partSum - 48;
				numberFraction++;  // increase currently fraction posision
			}
		}

		if (partSum == 46 && control) {  // if before press "dot" digit was integer, change digit on fraction
			control = 0;
			numberFraction++;
		}
	} while (partSum != '\r' || sum <= 0 && fractionSum <= 0);
	while (fractionSum >= 1) {// example : fractionSum was integer 324. after reduce become 0.324
		fractionSum /= 10;
	}
	sum += fractionSum;
	return sum;
}

void changingSize(bool addDelete,transaction*& actions, int& actionsCount,int indexDel)
{
	int difference;     //  Variable for chanching size of array, we can increase array (1) and vice-versa (-1), depends by addDelete
	if(addDelete) difference = 1;
	else  difference = -1;
	if (actionsCount == 0) {
		actions = new transaction [actionsCount +difference];
		actionsCount++;
		return;   // if we have no one action, we should stop a function, because of if we'll put variables of non existing
				// array application will break up
	}
	transaction* temp = new transaction[actionsCount + difference];
	for (int i = 0; i < actionsCount; i++) {
		if (!addDelete && i >= indexDel) {  // loop for keepin last variavles
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
	
	getline(cin, bufer);
	control = 0;
	for (int i = 0; i < countCategories; i++) {
		if (categories[i].name == bufer)return i; //if category already exist we use it and aren't creatin a new arrays element
		if (categories[i].name == "") {  // lookin for first free place, if it is push there our new category
			categories[i].name = bufer;
			return i;
		}
	}
}


int choising_category(sumAndCat categories[], int countCategories) {
	int bufer = 0, y = 1, i = 0;
	char choise = 0;
	cout << "choise the category" << endl;
	for (i = 0; i < countCategories; i++) {   //  show all categories
		cout << i + 1 << " " << categories[i].name << endl;
		if (categories[i + 1].name == "")break;
	}
	cout << "\nAdd new category\n";
	gotoxy(0, y);
	do {
		choise = _getch();			//moving by screen
		switch (choise) {
		case 72: {
			if (y > 1)y--;
			gotoxy(0, y);
			break;
		}
		case 80: {
			y++;
			gotoxy(0, y);
			break;
		}
		case'\r': {  // enter , call adding_category with index of categories array
			if (y <= i + 1)return (y - 1);
			else return adding_category(categories, countCategories);
		}
		}

	} while (choise != 27);  // moving till not esc

}

void adding(transaction*& actions, sumAndCat* categories, int countCategories, int& actionsCount, curency mainCurency)
{
	control = 1;

	GetSystemTimeAsFileTime(&ftTimeStamp); // including a time classes
	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);
	FileTimeToSystemTime(&ltime, &stime);
	int bufer, index = 0;
	int index_selected_category;
	transaction temp;
	changingSize(1, actions, actionsCount, 0); // increase size of array by one

	cout << "Enter sum of transaction: ";  // cheking a wrong value, cuz we gotta devide course on this digit (line 124)


	temp.sum = inputSecure();
	temp.sum /= mainCurency.course;

	index_selected_category = choising_category(categories, countCategories);
	temp.category = categories[index_selected_category].name;  
	categories[index_selected_category].sum += temp.sum;  // conting sum to category for manage statistic
	system("cls");
	cout << "Details: ";
	/*if (control)cin.ignore();*/
	getline(cin, temp.details);

	temp.date.year = stime.wYear; temp.date.mon = stime.wMonth; temp.date.day = stime.wDay;
	temp.date.hour = stime.wHour; temp.date.min = stime.wMinute;

	actions[actionsCount - 1] = temp;
}

void deleting(transaction*& actions, int& actionsCount)
{
	int bufer = 0;


	cout << "Enter number of action: ";  
	do {									// loop for check wrong value of array
		cin >> bufer;
		if (bufer <= 0 || bufer > actionsCount)cout << "Wrong choise!" << endl;
	} while (bufer <= 0 || bufer > actionsCount);

	changingSize(0, actions, actionsCount, actionsCount - bufer); // reducing size of array
}


void redact(transaction*& actions, int& actionsCount, sumAndCat* categories, int countCategories, int index, curency& mainCurency)
{
	int bufer = 0;
	do {
		system("cls");


		cout << "1. " << actions[index].sum*mainCurency.course << endl << "2. " << actions[index].category << endl << "3. " << actions[index].details;
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
			actions[index].sum /= mainCurency.course;
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
	int y = 0, i = 0;
	char choise = 0;
	curency temp;	
		gotoxy(0, y);
	do {
	system("cls");		
		gotoxy(0, 0);
		for (i = 0; i < 20; i++) {
			if (Curency[i].course == 0)break;
			if (i == y)SetConsoleTextAttribute(handle, 18); // paint curency if it is on currently possision
			cout << "# " << i + 1 << "    " << Curency[i].name << " (" << Curency[i].course << ")\n";
			SetConsoleTextAttribute(handle, 15);   // return to common color
		}
		if(y>=i)SetConsoleTextAttribute(handle, 18); // if cursor is lower than count of all currencies- paint a line in blue
		cout << " Add new curency\n";
		SetConsoleTextAttribute(handle, 15); // return to a common console color
		
		choise = _getch();  // movin by screen
		switch (choise) {
			
		case 72: {
			if (y > 0)y--;  // prevent a mivin cursor lower than zero or higher than currecyCount+1 
			gotoxy(0, y);
			break;
		}

		case 80: {
			if (y < i+1)y++;
			gotoxy(0, y);
			break;
		}


		case 13: {
			if (y <= i-1) {
				bool reverse = 1;  // we have only two strings -delete/choise, thats why we chanching bool and paint one of strings
				system("cls");
				do {
					gotoxy(0, 0);
					if(reverse)SetConsoleTextAttribute(handle, 18);
					cout << "Choise\n";
					SetConsoleTextAttribute(handle, 15);
					if(!reverse)SetConsoleTextAttribute(handle, 18);
					cout << "Delete currency\n";
					SetConsoleTextAttribute(handle, 15);
					choise = _getch();
					if(choise==72 || choise==80)reverse = !reverse;  // if pressed up button or down buttun we change a bool
				} while (choise != 13);
				choise = 0;
				if(reverse)mainCurency = Curency[y];  //if pressed "choise", mainCurrency takes a pressed currently index of courses
				else {
					for (int j = 0; j < 15; j++) {  //deleting loop
						if (Curency[j + 1].course == 0) { Curency[j].course = 0;  break; } // clear last valid element
						if (j >= y&&Curency[j+1].course!=0)Curency[j] = Curency[j + 1];
					}
				}

			}
			else {				//	 addind a new currency
				system("cls");
				cout << "Enter name curency: ";
				cin >> temp.name;
				cout << "Write a course: 1$ =         " << temp.name[0] << temp.name[1] << temp.name[2] << endl;
				gotoxy(21, 1);
				temp.course=inputSecure();
				mainCurency = temp;
				for (int i = 0; i < 20; i++) {
					if (Curency[i].course == 0) { // look a first free place and put there a new currency
						Curency[i] = temp;
						break;
					}
				}
			}
		}
		}

	} while (choise != 27 && choise != 13); // moving by loop till (ENTER) or (ESC)
	system("cls");
}
