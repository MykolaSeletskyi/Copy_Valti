#pragma once
#include<iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#define GREEN SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define RED SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
#define BLUE SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

using std::cout;
using std::cin;
using std::endl;
using std::string;


const int countCategories = 15;
struct dates {
	int year;
	int mon;
	int day;
	int hour;
	int min;
};
struct transaction {
	float sum;
	string category;
	string details;
	bool incomeSpend = 1;
	dates date;
};
struct sumAndCat {
	string name;
	int sum=0;
};
struct categor {
	sumAndCat incomeCategories[countCategories];
	sumAndCat spendCategories[countCategories];
};

struct curency {
	string name;
	float course;
};



void adding(transaction*& actions, sumAndCat* categories, int countCategories, int& actionsCount, curency mainCurency);
void changingSize(bool addDelete, transaction*& actions, int& actionsCount, int indexDel);
void showActions(bool mode, transaction*& actions, int& actionsCount, curency mainCurency);
void deleting(transaction*& actions, int& actionsCount);
void redact(transaction*& actions, int& actionsCount, sumAndCat* categories, int countCategories, int index, curency& mainCurency);
int adding_category(sumAndCat* categories, int countCategories);
void deletingCategory(sumAndCat* categories, int countCategories, int index);
void gotoxy(int x, int y);
void curencyManager(curency Curency[], curency& mainCurency);
