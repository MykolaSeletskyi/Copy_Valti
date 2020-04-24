#include "Callend.h"
#include <Windows.h>


int show_calend(int &today, int &days, int &year, int &mon, int &week_day)
{
	



	posision arr[31];
	system("cls");
	bool chek = 0;

	HWND hwnd; // дескриптор ЭКРАНА
	RECT rect; // дескриптор окна
	hwnd = GetConsoleWindow();  // заполнение полей дескриптора экрана	POINT P;   // тип точка (х, у)
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);   // дескриптор стандартного потока вывода и его заполнение
	
	
	
	

	cout << "\t\t    Year  " << year << "  Mounth " << mon << endl << endl;
	cout << "Mon\tTue\tWed\tThu\tFri\tSut\tSun" << endl << endl;

	for (int i = 0; i < week_day; i++) {
		cout << " \t";
	}
	for (int i = 1; i <= days; i++) {
		if (week_day % 7 == 0) {
			cout << endl << endl;
			week_day = 0;
		}
		getxy(arr[i - 1].x, arr[i - 1].y);
		cout << i << "\t";
		week_day++;
	}

	int pos = 17, col = 64;
	gotoxy(arr[pos].x, arr[pos].y);
	SetConsoleTextAttribute(handle, col);
	cout << pos;
	SetConsoleTextAttribute(handle, 15);
	
	char move = 0;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;   // дескриптор информации о буфере экрана (высота, ширина ...)
	for (;;) {
		bool click = 0;
		POINT P;
		GetCursorPos(&P);
		GetWindowRect(hwnd, &rect);
		P.x = (P.x - rect.left) / 10;
		P.y = (((P.y - rect.top) - 40) / 14) + 1;
		P.x /= 0.82;
		if (P.x % 8 <5 && P.y % 2 == 0) {
			
				for (int i = 0; i < 30; i++) {

					if (abs(P.x - arr[i].x) < 4 && abs(P.y - arr[i].y) < 2) {

						if (i == pos)break;
						gotoxy(arr[pos].x, arr[pos].y);
						cout << pos+1;
						gotoxy(arr[i].x, arr[i].y);
						SetConsoleTextAttribute(handle, col);
						cout <<i+1;
						SetConsoleTextAttribute(handle, 15);
						pos = i;
						click = 1;
						break;
					}

				}
		}
		SHORT state = GetAsyncKeyState(VK_LBUTTON);
		if (state & 0x8000) {
			gotoxy(15, 15);
			cout << pos + 1 << " clocked!";
		}
	}

	/*do {
		move = _getch();
		switch (move) {

		case 72: {
			pos >= 10 ? cout << "\b\b" << pos : cout << "\b" << pos;
			if (pos - 7 >= 1)pos -= 7;
			gotoxy(arr[pos - 1].x, arr[pos - 1].y);
			SetConsoleTextAttribute(handle, col);
			cout << pos;

			SetConsoleTextAttribute(handle, 15);
			break;
		}
		case 80: {
			pos >= 10 ? cout << "\b\b" << pos : cout << "\b" << pos;
			if (pos + 7 <= days)pos += 7;
			gotoxy(arr[pos - 1].x, arr[pos - 1].y);
			SetConsoleTextAttribute(handle, col);
			cout << pos;
			SetConsoleTextAttribute(handle, 15);
			break;
		}
		case 77: {
			pos >= 10 ? cout << "\b\b" << pos : cout << "\b" << pos;
			pos++;
			if (pos > days)return 1;
			gotoxy(arr[pos - 1].x, arr[pos - 1].y);
			SetConsoleTextAttribute(handle, col);
			cout << pos;
			SetConsoleTextAttribute(handle, 15);
			break;
		}
		case 75: {
			if (pos < 2)return 0;
			pos >= 10 ? cout << "\b\b" << pos : cout << "\b" << pos;
			pos--;
			gotoxy(arr[pos - 1].x, arr[pos - 1].y);
			SetConsoleTextAttribute(handle, col);
			cout << pos;
			SetConsoleTextAttribute(handle, 15);
			break;
		}
		case 27: {
			return 27;
		}
		}


	} while (move);*/
	return false;
}

void controling_dates(int &today, int &days, int &year, int &mon, int &week_day)
{
	if (mon == 13) {
		mon = 1;
		year++;
	}
	if (mon == 0) {
		mon = 12;
		year--;
	}
	if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)days = 31;
	else if ((year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0)) && mon == 2) {
		days = 29;
	}
	else if (mon == 2)days = 28;
	else days = 30;
}

void getxy(int & x, int & y)
{
	
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	x = csbiInfo.dwCursorPosition.X;
	y = csbiInfo.dwCursorPosition.Y;
}

void CalendMenu()
{
	SYSTEMTIME stime;
	FILETIME ltime;
	FILETIME ftTimeStamp;
	{
		
		for (int i = 0; i < 30; i++) {
			
			cout << "\t\t\t\t\t\t\t\t\t\t\n";
		}
		
	}
	gotoxy(65, 0);
	cout << "(ESC) Exit\n";

	int days = 0, today = 0, returned = 0;

	GetSystemTimeAsFileTime(&ftTimeStamp);
	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);
	FileTimeToSystemTime(&ltime, &stime);
	int year = stime.wYear;
	int mon = stime.wMonth;
	int week_day = stime.wDayOfWeek;
	if (week_day == 0)week_day = 7;
	controling_dates(today, days, year, mon, week_day);
	week_day = 7 - ((stime.wDay - (week_day)) % 7);



	for (;;) {
		returned = show_calend(today, days, year, mon, week_day);

		switch (returned) {
		case 1: {
			mon++;
			controling_dates(today, days, year, mon, week_day);
			break;
		}
		case 0: {
			week_day = 7 - ((days - (week_day)) % 7);
			mon--;
			controling_dates(today, days, year, mon, week_day);
			week_day = 7 - ((days - (week_day)) % 7);
			break;
		}
		case 27: {
			system("cls");
			return;
		}
		}
	}
}

