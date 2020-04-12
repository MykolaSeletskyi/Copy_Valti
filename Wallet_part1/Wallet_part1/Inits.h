#pragma once
#include "IncomesSpends.h"

void writing_categories(sumAndCat* categories, bool income_spend);
void reading_categories(sumAndCat* categories, bool income_spend);
void initCurrency(curency Curency[], curency& mainCurency);
void exitInitCurency(curency Curency[], curency& mainCurency);
void initActions(transaction*& actions, int& actionsCount, sumAndCat* categories, sumAndCat* spendcategories);
void exitInitActions(transaction*& actions, int& actionsCount);

