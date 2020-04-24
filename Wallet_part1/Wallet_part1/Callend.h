#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include "IncomesSpends.h"



using std::cout;
using std::cin;
using std::endl;
using std::string;

struct event {
	string name;
	dates date;
	string description;
	int importance = 1;
};

struct posision {
	int x;
	int y;
};

int show_calend(int &, int&, int&, int&, int&);
void controling_dates(int &, int&, int&, int&, int&);
void getxy(int &x, int& y);
void CalendMenu();