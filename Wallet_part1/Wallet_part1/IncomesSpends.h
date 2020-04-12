#pragma once
#include<iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

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
	double sum;
	string category;
	string details;
	bool incomeSpend = 1;
	dates date;
};
struct sumAndCat {
	string name;
	double sum = 0;
};


struct curency {
	string name;
	double course=0;
};



void adding(transaction*& actions, sumAndCat* categories, int countCategories, int& actionsCount, curency mainCurency);
void changingSize(bool addDelete, transaction*& actions, int& actionsCount, int indexDel);
void deleting(transaction*& actions, int& actionsCount);
void redact(transaction*& actions, int& actionsCount, sumAndCat* categories, int countCategories, int index, curency& mainCurency);
int adding_category(sumAndCat* categories, int countCategories);
void deletingCategory(sumAndCat* categories, int countCategories, int index);
void gotoxy(int x, int y);
void curencyManager(curency Curency[], curency& mainCurency);