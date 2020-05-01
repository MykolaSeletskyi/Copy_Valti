#include "functional_Callend.h"
#include "Callend.h"
event create_event(dates currently) {
	COORD position = { 20,20 };
	event res;
	res.date = currently;
	int temp = 0;

	gotoxy(position.X, position.Y++);
	cout << "name = ";
	cin >> res.name;

	gotoxy(position.X, position.Y++);
	cout << "description = ";
	cin >> res.description;

	gotoxy(position.X, position.Y++);
	cout << "hour = ";
	cin >> temp;
	res.date.hour = temp;

	gotoxy(position.X, position.Y++);
	cout << "min = ";
	cin >> temp;
	res.date.min = temp;

	gotoxy(position.X, position.Y++);
	cout << "importance (1-3) = ";
	cin >> res.importance;

	return res;
}
void delete_event(event*& events, int* size_arr, int index)
{
	event* temp = new event[(*size_arr) - 1];
	for (int i = 0; i < *size_arr - 1; i++)
	{
		if (index <= i)
		{
			temp[i] = events[i + 1];
		}
		else
		{
			temp[i] = events[i];
		}
	}
	delete[] events;
	events = temp;
	(*size_arr)--;
}
void add_an_event_to_an_array(event*& events, int* size_arr, event new_event)
{
	int index_of_new_item = *size_arr;
	if (*size_arr)
	{
		dates temp;
		for (int i = *size_arr - 1; i >= 0; i--)
		{
			cout << new_event.date.full_date() << endl;
			cout << events[i].date.full_date() << endl;
			system("pause");
			if (new_event.date.full_date() >= events[i].date.full_date())
			{
				index_of_new_item = i + 1;
				break;
			}
			index_of_new_item--;
		}
	}
	event* temp = new event[(*size_arr) + 1];
	for (int i = 0; i < *size_arr; i++)
	{
		if (index_of_new_item <= i)
		{
			temp[i + 1] = events[i];
		}
		else
		{
			temp[i] = events[i];
		}
	}
	temp[index_of_new_item] = new_event;
	delete[] events;
	events = temp;
	(*size_arr)++;
}