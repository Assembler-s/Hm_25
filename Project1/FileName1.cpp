#include <iostream>
#include <windows.h>

using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

	bool isLeap() const
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;

		return false;
	}

	int daysInMonth() const
	{
		if (month == 2)
		{
			if (isLeap())
			{
				return 29;
			}
			return 28;
		}

		if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;
		else
		{
			return 31;
		}
	}

	void nextDay()
	{
		if (day + 1 > daysInMonth())
		{
			day = 1;

			if (month + 1 > 12)
			{
				month = 1;
				year++;
			}
			else
			{
				month++;
			}
		}
		else
		{
			day++;
		}
	}

	void lastDay()
	{
		if (day == 1 && month == 1 && year == 1)
			return;

		if (day - 1 < 1)
		{
			if (month - 1 < 1)
			{
				month = 12;
				year--;
			}
			else month--;
			day = daysInMonth();
		}
		else day--;
	}

public:
	Date(int day_, int month_, int year_) : day(day_), month(month_), year(year_)
	{
		if (month_ < 1 || month_ > 12)
			month = 1;

		if (year_< 1)
			year = 1;

		if (day_ < 1 || day_ > daysInMonth())
			day = 1;
	}

	void print() const
	{
		if (day / 10 == 0)
			cout << "0";
		cout << day << ".";

		if (month / 10 == 0)
			cout << "0";
		cout << month << ".";

		cout << year << endl;
	}

	Date& operator ++ ()
	{
		nextDay();
		return *this;
	}

	Date operator ++ (int) 
	{
		Date temp(*this);
		nextDay();
		return temp;
	}

	Date& operator -- ()
	{
		lastDay();
		return *this;
	}

	Date operator -- (int)
	{
		Date temp = *this;

		lastDay();
		return temp;
	}

	Date& operator -= (int days)
	{
		if (days <= 0)
			return *this;

		for (int i = 0; i < days; i++)
		{
			--(*this);
		}

		return *this;
	}

	Date operator-(int days)
	{
		Date temp(*this);
		return temp -= days;
	}

	int operator-(const Date& other) const
	{
		int step = 0;
		if (*this < other)
		{
			return -(other - *this);
		}
		else
		{
			Date copy(other);
			while (copy < *this)
			{
				copy++;
				step++;
			}
		}

		return step;
	}

	Date& operator += (int days)
	{
		if (days <= 0)
			return *this;

		for (int i = 0; i < days; i++)
			++(*this);

		return *this;
	}

	Date operator + (int days)
	{
		Date temp(*this);
		return temp += days;
	}

	bool operator == (const Date& rVal) const
	{
		if (year == rVal.year && month == rVal.month && day == rVal.day)
			return true;

		return false;
	}

	bool operator < (const Date& rVal) const
	{
		if (year < rVal.year)
			return true;
		else if (year == rVal.year)
		{
			if (month < rVal.month)
				return true;
			else if (month == rVal.month)
			{
				if (day < rVal.day)
					return true;
			}
		}

		return false;
	}

	bool operator != (const Date& rVal) const
	{
		if (*this == rVal)
			return false;

		return true;
	}

	bool operator > (const Date& rVal) const
	{
		if (*this < rVal || *this == rVal)
			return false;

		return true;
	}

	bool operator <= (const Date& rVal) const
	{
		if (*this > rVal)
			return false;

		return true;
	}

	bool operator >= (const Date& rVal) const
	{
		if (*this < rVal)
			return false;

		return true;
	}
};


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	//Уровень 1
	Date d{ 28, 2, 2026 };
	d.print();
	d++;
	d.print();

	cout << endl;
	
	////////////////
	Date e{ 31, 12, 2026 };
	Date old = e++;
	e.print();
	old.print();
	/*После Date old = e++; old будет копией e{ 31, 12, 2026 } 
	поскольку e++ возвращает старое значение а затем увеличивает е на 1 день.
	Следовательно, old получит возвращённое старое значение.*/
	///////////////

	(Date{ 17,10,2026 } + 41).print();

	Date arr[3] = {
		{ 13, 9, 2002 },
		{ 11, 7, 2023 },
		{ 2, 1, 2000 }
	};

	Date min_date(arr[0]);

	for (int i = 1; i < 3; i++)
	{
		if (min_date > arr[i])
			min_date = arr[i];
	}
	cout << "Самая ранняя дата: ";
	min_date.print();

	Date f{ 1,2,3 };
	((f += 5) += 2).print();

	Date(31, 4, 2026).print();
	//////////////////////////


	// Уровень 2
	(Date{ 1,1,2027 } - 1).print();
	cout << Date{ 27,11,2026 } - Date{ 24, 10, 2026 } << endl;
	cout << Date{ 1,1,2027 } - Date{ 24, 10, 2026 } << endl;
	/////////////////////////

	//Уровень 3
	(++Date{ 28,02,2028 }).print();
	Date(29, 2, 2100).print();
	////////////////////////



	return 0;
}

/*1) Префиксный ++ возвращает Date& потому-что необходимо чтоб операнд увеличился и продолжилась 
работа с новым значением, поэтому возврвщается ссылка на объект. Постфиксный ++ работает иначе, сначала
обрабатывается старое значение, но оно уже увеличено, поэтому ++ возвращает копию старого значения а 
сам объект уже увеличен. Если бы возвращалась ссылка, то мы бы получили уже новый объект, а не копию старого,*/

/*2) Параметр int нужен, чтобы компилятор отличал постфиксный ++ от префиксного. Префиксный ++date не принимает
параметров, а постфиксный date++ принимает фиктивный параметр int, который не используется внутри метода.*/

/*3) operator+ не изменяет текущую дату, а создаёт новую, поэтому он константный. operator+= изменяет текущую дату,
сдвигая её на сколько-то дней вперёд, поэтому он не может быть константным.*/

/*4) Так не нужно писать отдельную логику для каждого оператора. Достаточно правильно реализовать == и <, а 
остальные операторы сделать через них. Так код короче и меньше вероятность допустить ошибку.*/

/*5) Компилятор смотрит на типы аргументов. d - 5 — вызывается operator-(int), потому что 5 — целое число.
d - other — вызывается operator-(const Date& other), потому что other — объект типа Date.*/

/*6) Date + int — к дате можно прибавить количество дней, чтобы получить новую дату.
Date - Date — можно вычислить количество дней между двумя датами.
Date + Date — не имеет очевидного смысла, непонятно, что должна означать сумма двух дат.
Перегружают операторы так, чтобы они отражали логичные действия с объектами.*/