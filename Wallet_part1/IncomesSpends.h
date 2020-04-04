#pragma once
#include<iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#define GREEN SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define RED SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

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
	bool incomeSpend;
	dates date;
};

struct categor {
	string incomeCategories[countCategories];
	string spendCategories[countCategories];
};

void gotoxy(int x, int y);
void adding(transaction*& actions, string* categories,int countCategories, int&actionsCount);
void changingSize(bool addDelete,transaction*& actions, int& actionsCount,int indexDel);
void showActions(bool mode, transaction*& actions, int& actionsCount);
void deleting(transaction*& actions, int& actionsCount);
void redact(transaction *& actions, int & actionsCount, categor *categories, int countCategories);
string adding_category(string* categories,int countCategories);