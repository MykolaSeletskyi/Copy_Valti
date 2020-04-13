#include "Inits.h"
#include <fstream>
void writing_categories(sumAndCat *categories,bool income_spend)
{
	std::ofstream fout;
	if (income_spend)
	{
		fout.open("Categories_income.txt");
	}
	else
	{
		fout.open("Categories_spend.txt");
	}
	for (int i = 0; i < countCategories; i++)
	{
		fout << categories[i].name << " ";
		fout << categories[i].sum;
		if (categories[i+1].sum == 0)
		{
			fout.close();
			return;
		}
			fout << endl;	
	}
	fout.close();
}
void reading_categories(sumAndCat* categories, bool income_spend)
{
	std::ifstream fin;
	if (income_spend)
	{
		fin.open("Categories_income.txt");
	}
	else
	{
		fin.open("Categories_spend.txt");
	}
	if (!fin.is_open()) {
		cout << "Error: File not opend!" << endl;
		system("pause");
		return;
	}
	int count = 0;
	while (!fin.eof())
	{
		fin >> categories[count].name;
		fin >> categories[count].sum;
		count++;
	}
}
void initCurrency(curency Curency[], curency& mainCurency)
{
	std::fstream cur("curenc.txt");
	int i = 0;
	while (!cur.eof()) {
		if (i == 0) {
			cur >> mainCurency.name;
			cur >> mainCurency.course;
			Curency[i].name = mainCurency.name;
			Curency[i].course = mainCurency.course;
		}
		else {
			cur >> Curency[i].name;
			cur >> Curency[i].course;
		}
		i++;
	}
	cur.close();
}

void exitInitCurency(curency Curency[], curency & mainCurency)
{
	
	std::fstream cur("curenc.txt",std::ios::app);
	std::fstream("curenc.txt", std::fstream::out);
	cur << mainCurency.name << endl;
	cur << mainCurency.course << endl;
	for (int i = 0; i < 15; i++) {
		if (Curency[i].course == 0)break;
		if (Curency[i].name == mainCurency.name)continue;
			cur << Curency[i].name << endl;
			cur << Curency[i].course << endl;
	}
	cur.close();
}

void initActions(transaction*& actions, int& actionsCount, sumAndCat* categories, sumAndCat* spendcategories) {
	int i = 0;
	string bufer = "";
	char sym = 0;
	std::fstream act("actions.txt");
	act >> actionsCount;
	actions = new transaction[actionsCount];
	while (!act.eof()) {
		if (i >= actionsCount)break;
		act.get(sym);     // ������� ���� ����� �� ������� ���� �������� ���������� � �������� ���
		for (;;) {
			act.get(sym);
			if (sym == '\n')break;
			else actions[i].category += sym;
		}
		act>> actions[i].date.year;
		act>> actions[i].date.mon;
		act>> actions[i].date.day;
		act>> actions[i].date.hour;
		act>> actions[i].date.min ;
		act.get(sym);
		for (;;) {
			act.get(sym);
			if (sym == '\n')break;
			else actions[i].details += sym;
		}
		act>> actions[i].incomeSpend;
		act>> actions[i].sum;
		for (int j = 0; j < 15; j++) {
			if (actions[i].category == categories[j].name &&actions[i].incomeSpend)categories[j].sum += actions[i].sum;
			else if (spendcategories[j].name == actions[i].category && !actions[i].incomeSpend)spendcategories[j].sum += actions[i].sum;
		}
		i++;
	}


	act.close();

}

void exitInitActions(transaction*& actions, int& actionsCount) {
	std::fstream act("actions.txt");
	std::fstream("actions.txt",std::ios::out);
	act << actionsCount << endl;
	for (int i = 0; i < actionsCount; i++) {
		act<<actions[i].category<<endl;
		act << actions[i].date.year << ' ';
		act << actions[i].date.mon << ' ';
		act << actions[i].date.day << ' ';
		act << actions[i].date.hour << ' ';
		act << actions[i].date.min<<endl;
		act << actions[i].details<<endl;
		act << actions[i].incomeSpend << ' ';
		act << actions[i].sum<<endl;
	}
	act.close();
}