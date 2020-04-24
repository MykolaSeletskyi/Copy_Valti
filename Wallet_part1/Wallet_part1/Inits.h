#pragma once
#include "IncomesSpends.h"

void writing_categories(sumAndCat* categories, bool income_spend);
void reading_categories(sumAndCat* categories, bool income_spend);
void initCurrency(curency Curency[], curency& mainCurency);
void exitInitCurency(curency Curency[], curency& mainCurency);
void initActions(transaction*& actions, int& actionsCount, sumAndCat* categories, sumAndCat* spendcategories, double* sum_income, double* sum_spend);
void exitInitActions(transaction*& actions, int& actionsCount, double* sum_income, double* sum_spend);

