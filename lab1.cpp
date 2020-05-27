
//Проверить обработку исключительных ситуаций. 
//Реализовать двунаправленный стек с использованием быстрой сортировки.

#include "stdafx.h"
#include "string.h"
#include "math.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX = 5;
class Stack
{

public:
	int elements[MAX];
	int top;

	class SearchEx {};

	Stack() { top = -1; }
	~Stack() {}

	void In(int val) {
		if (top >= MAX - 1) 
			throw string("В стеке слишком много элементов!");
		elements[++top] = val;
	}

	int TopElem() {
		if (top < 0)
			throw string("Стек пуст!");
		return elements[top];
	}

	void Out() {
		if (top < 0)
		{
			throw string("Стек пуст!");
		}
		elements[top] = NULL;
		top--;
	}

	string Search(int a) {
		for (int elem : elements) {
			if (elem == a)
				return "Элемент найден";
		}
		throw SearchEx();
	}
	
	void Print() {
		if (top < 0)
			throw string("Стек пуст!");
		for (int i = 0; i <= top; i++)
		{
			cout.setf(ios::dec); 
			cout.setf(ios::showpos);
			cout << elements[i] << ' ';
		}
		cout << endl;
	}

	void Quicksort(int * mas, int first, int last)
	{
		int mid, temp;
		int f = first, l = last;
		mid = mas[(f + l) / 2];
		do
		{
			while (mas[f]<mid) f++;
			while (mas[l]>mid) l--;
			if (f <= l)
			{
				temp = mas[f];
				mas[f] = mas[l];
				mas[l] = temp;
				f++;
				l--;
			}
		} while (f<l);
		if (first<l) Quicksort(mas, first, l);
		if (f<last) Quicksort(mas, f, last);
	};

};
std::istream& operator >> (std::istream &in, Stack &i) {
	
	in >> i.elements[++i.top];
	return in;
}
std::istream& operator << (std::istream &out, string s) {
	out << s;
	return out;
}
int main()
{
	setlocale(LC_ALL, "Russian");

	Stack st;
	cin >> setw(3) >> st;
	st.In(3);
	st.In(2);
	st.In(1);
	try
	{
		cout.setf(ios::left);
		cout << "Стек: ";
		st.Print();
		cout.unsetf(ios::left);		
		cout << "Поиск элемента 2: " << st.Search(2) << endl;	
		int first = 0, last = st.top;
		st.Quicksort(st.elements, first, last);
		cout.width(30); 
		cout.setf(ios::right);
		cout << "Сортированный: ";
		cout.unsetf(ios::right);
		st.Print();
		cout << "Крайний элемент: " << st.TopElem() << endl;
		cout << "Убираем крайний элемент" << endl;
		st.Out();
		cout.setf(ios::right);
		cout << "Стек: ";
		st.Print();
		cout << "Крайний элемент: " << st.TopElem() << endl;
		cout << "Убираем крайний элемент" << endl;
		st.Out();
		cout << "Стек: ";
		st.Print();
		cout << "Крайний элемент: " << st.TopElem() << endl;
		cout << "Убираем крайний элемент" << endl;
		st.Out();
		cout << "Стек: ";
		st.Print();
		cout << "Крайний элемент: " << st.TopElem() << endl;
		cout << "Убираем крайний элемент" << endl;
		st.Out();
		cout << "Стек: ";
		st.Print();

	}
	catch (const string& e)
	{
		cout << e << endl;
	}

	catch (Stack::SearchEx) {
		cout << "Элемента в стеке нет!" << endl;
	}

	system("pause");
	return 0;
}

