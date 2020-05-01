#include "Callend.h"
#include <Windows.h>

template <typename mytype>

void gotopaint(int a, int b, mytype name, bool paint) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(a, b);
    if (paint)SetConsoleTextAttribute(handle, 64);
    cout << name;
    SetConsoleTextAttribute(handle, 15);
}
int show_calend(int& today, int& days, int& year, int& mon, int& week_day)
{


    posision arr[31];
    system("cls");

    RECT rect; // äåñêðèïòîð îêíà
    HWND hwnd = GetConsoleWindow();  // çàïîëíåíèå ïîëåé äåñêðèïòîðà ýêðàíà
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);   // äåñêðèïòîð ñòàíäàðòíîãî ïîòîêà âûâîäà è åãî çàïîëíåíèå


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
    gotopaint(arr[pos].x, arr[pos].y, pos, 1);

    char move = 0;
    bool prev = 0, next = 0;
    gotopaint(5, 17, "PREVIOUS", 0);
    gotopaint(25, 17, "NEXT", 0);

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;   // äåñêðèïòîð èíôîðìàöèè î áóôåðå ýêðàíà (âûñîòà, øèðèíà ...)
    for (;;) {
        POINT P;
        GetCursorPos(&P);
        GetWindowRect(hwnd, &rect);
        P.x = (P.x - rect.left) / 8.19;
        P.y = (((P.y - rect.top) - 40) / 13.5);
        int back = pos;
        if (P.x % 8 < 4 && P.y % 2 == 0 && P.x > 0 && P.y > 0) {
            int iter2 = 0;
            for (int i = pos;; i++) {
                if (iter2 > 31)break;

                if (back < 0)back = days - 1;
                if (i > days - 1)i = 0;
                if (abs(P.x - arr[back].x) < 4 && abs(P.y - arr[back].y) < 2) i = back;

                if (abs(P.x - arr[i].x) < 4 && abs(P.y - arr[i].y) < 2) {

                    if (i == pos)break;
                    gotoxy(arr[pos].x, arr[pos].y);
                    cout << pos + 1;
                    gotopaint(arr[i].x, arr[i].y, i + 1, 1);

                    pos = i;
                    break;
                }
                back--;
                iter2++;
            }

        }
        if (prev) {
            if ((abs(P.y - 17) > 0) || P.x < 5 || P.x > 14) {
                gotoxy(5, 17);     cout << "PREVIOUS";
                prev = 0;
            }
        }
        if (next) {
            if ((abs(P.y - 17) > 0) || P.x < 24 || P.x > 29) {
                gotoxy(25, 17);    cout << "NEXT";
                next = 0;
            }
        }
        if (abs(P.y - 17) <= 1) {
            if (P.x >= 5 && P.x <= 14) {
                if (prev)goto base;
                gotoxy(arr[pos].x, arr[pos].y);   cout << pos + 1;
                gotopaint(5, 17, "PREVIOUS", 1);
                prev = 1;
            }
            if (P.x >= 24 && P.x <= 29) {
                if (next)goto base;
                if (!next && !prev) { gotoxy(arr[pos].x, arr[pos].y);  cout << pos + 1; }
                gotopaint(25, 17, "NEXT", 1);
                next = 1;
            }
        }
    base:
        if (GetKeyState(VK_LBUTTON) & 0x8000) {
            Sleep(100);
            if (prev)return 0;
            if (next)return 1;

        }
    }

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
	int size_event = 0;
	event* events = new event[size_event];
	//add_an_event_to_an_array(events, &size_event, create_event("сюди передати структуру з теперішньою датою")); //визов функції добавленя
	//delete_event(events, &size_event, index - 1);//це видалення (index - 1, бо масив від 0 йде)
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
			delete[] events;
			system("cls");
			return;
		}
		}
	}
}

