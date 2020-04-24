#pragma once
#include <Windows.h>
#include <iostream>
#include "IncomesSpends.h"
#include <string> 
#include <fstream>
#include "Callend.h"

using namespace std;
const HDC hdc = GetDC(GetConsoleWindow());
const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int font_color = 15;
const int selected_color = 16;
const int hotkeys_color = 8;
const int hotkeys_x = 65;
const int transaction_main_x = 12;
const int transaction_x = 1;
const int menu_x = 40;
const int dates_color = 112;
const int color[countCategories] = { 16776960, 16711680, 16711935, 32768, 128, 65280, 8388608, 32896, 8388736, 255, 8421376, 65535, 6566655, 5963676, 8453888 };

void hotkeys();
void menu_income_and_Spend(transaction*& actions, int& actionsCount, sumAndCat* categories, bool income_Spend, curency& mainCurency, double* sum_income, double* sum_spend);
void transactionsByTime(transaction actions[], int& actionsCount, curency& mainCurency);
void show_balance(COORD coord_zero, double sum_income, double sum_spend, curency& mainCurency);
string double_to_string(double number, curency& mainCurency);
float double_to_float(double number, curency& mainCurency);
