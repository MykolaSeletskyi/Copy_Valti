#pragma once
#include <Windows.h>
#include <iostream>
#include "IncomesSpends.h"
using namespace std;
const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int font_color = 15;// колір шрифту
const int selected_color = 16;// колір вибраної дії
const int hotkeys_color = 8;//колір гарячих клавиш
const int dates_color = 112;// колір дати
const int hotkeys_x = 100;
void hotkeys();
void menu_income_and_Spend(transaction*& actions, int& actionsCount, string* categories, int countCategories,bool income_Spend);