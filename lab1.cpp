
//��������� ��������� �������������� ��������. 
//����������� ��������������� ���� � �������������� ������� ����������.

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
			throw string("� ����� ������� ����� ���������!");
		elements[++top] = val;
	}

	int TopElem() {
		if (top < 0)
			throw string("���� ����!");
		return elements[top];
	}

	void Out() {
		if (top < 0)
		{
			throw string("���� ����!");
		}
		elements[top] = NULL;
		top--;
	}

	string Search(int a) {
		for (int elem : elements) {
			if (elem == a)
				return "������� ������";
		}
		throw SearchEx();
	}
	
	void Print() {
		if (top < 0)
			throw string("���� ����!");
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
		cout << "����: ";
		st.Print();
		cout.unsetf(ios::left);		
		cout << "����� �������� 2: " << st.Search(2) << endl;	
		int first = 0, last = st.top;
		st.Quicksort(st.elements, first, last);
		cout.width(30); 
		cout.setf(ios::right);
		cout << "�������������: ";
		cout.unsetf(ios::right);
		st.Print();
		cout << "������� �������: " << st.TopElem() << endl;
		cout << "������� ������� �������" << endl;
		st.Out();
		cout.setf(ios::right);
		cout << "����: ";
		st.Print();
		cout << "������� �������: " << st.TopElem() << endl;
		cout << "������� ������� �������" << endl;
		st.Out();
		cout << "����: ";
		st.Print();
		cout << "������� �������: " << st.TopElem() << endl;
		cout << "������� ������� �������" << endl;
		st.Out();
		cout << "����: ";
		st.Print();
		cout << "������� �������: " << st.TopElem() << endl;
		cout << "������� ������� �������" << endl;
		st.Out();
		cout << "����: ";
		st.Print();

	}
	catch (const string& e)
	{
		cout << e << endl;
	}

	catch (Stack::SearchEx) {
		cout << "�������� � ����� ���!" << endl;
	}

	system("pause");
	return 0;
}

