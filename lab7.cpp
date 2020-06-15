#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include <ostream>
#include <istream>
#include <locale.h>
#include <list>
#include <string>
#include <iterator>

using namespace std;

string _name, _country;
int _parts, _year, _rate;

struct Element {
	string name;
	string country;
	int parts;
	int year;
	int rate;

	~Element() {
		name = "";
		country = "";
		parts = NULL;
		year = NULL;
		rate = NULL;
	}
};

list <Element> myList;


class Algoritm
{
	list <Element> algList;
	int iter = 0;
public:

	Algoritm(list<Element> _algList) {
		algList = _algList;
	};

	int checkIfInt(string str)
	{
		int a;
		while (!(cin >> a) || a < 1)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << str;
		}
		return a;
	}

	void Enter() {
		cout << "��������: ";
		cin >> _name;
		cout << "������: ";
		cin.clear();
		cin >> _country;
		cout << "�����: ";
		_parts = checkIfInt("��������� ���� (�����): ");
		cout << "���: ";
		_year = checkIfInt("��������� ���� (���): ");
		cout << "�������: ";
		_rate = checkIfInt("��������� ���� (�������): ");
	}

	void Add(string name, string country, int parts, int year, double rate)
	{
		Element newCartoon{ name,  country, parts,  year, rate };
		myList.push_front(newCartoon);
	}

	void Add()
	{
		Enter();
		Element newCartoon{ _name,  _country, _parts,  _year, _rate };
		myList.push_front(newCartoon);
	}

	void Print() {
		int i = 1;
		try {
			list<Element>::iterator it = myList.begin();
			if (it == myList.end())
				throw string("������ ����!");
			for (it; it != myList.end(); ++it) {
				cout << i << ". " << setw(14)
					<< it->name << setw(14)
					<< it->country << setw(14)
					<< it->year << setw(14)
					<< it->parts << setw(14)
					<< it->rate << endl;
				i++;
			}
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void HeadElem() {
		try {
			list<Element>::iterator it = myList.begin();
			if (it == myList.end())
				throw string("������ ����!");
			cout << "�������� �������: ";
			cout << it->name << setw(14)
				<< it->country << setw(14)
				<< it->year << setw(14)
				<< it->parts << setw(14)
				<< it->rate << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Change()
	{
		try {
			int id;
			cout << "����� ����������� �������: ";
			cin >> id;

			if (id <= 0 || id > myList.size())
				throw string("�� �� ������ �������� ���� �������.");

			list<Element>::iterator it = myList.begin();
			advance(it, id-1);

			Enter();
			it->name = _name;
			it->country = _country;
			it->parts = _parts;
			it->year = _year;
			it->rate = _rate;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Remove() {
		try {
			list<Element>::iterator it = myList.begin();
			if (it == myList.end())
				throw string("������ ����!");
			myList.pop_front();
			cout << "������� ��� ������." << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}
	
	void Sort(int props)
	{
		list<Element>::iterator left = myList.begin();
		list<Element>::iterator right = left; right++;
		list<Element>::iterator iEndNext = myList.end(); iEndNext--;
		list<Element>::iterator iEnd = myList.end();
		while (left != iEndNext)
		{
			while (right != iEnd)
			{
				switch (props)
				{
				case 0:
					if (left->name > right->name)
					{
						swap(left, right);
					}
					break;
				case 1:
					if (left->country > right->country)
					{
						swap(left, right);
					}
					break;
				case 2:
					if (left->parts > right->parts)
					{
						swap(left, right);
					}
					break;
				case 3:
					if (left->year > right->year)
					{
						swap(left, right);
					}
					break;
				case 4:
					if (left->rate < right->rate)
					{
						swap(left, right);
					}
					break;
				}
				++right;
			}
			++left;
			right = left; right++;
		}
	}

	void swap(list<Element>::iterator q, list<Element>::iterator p)
	{
		string temp = q->name.substr(0, q->name.size());
		q->name = p->name.substr(0, p->name.size());
		p->name = temp;

		string temp2 = q->country.substr(0, q->country.size());
		q->country = p->country.substr(0, p->country.size());
		p->country = temp2;

		int tempi = q->parts;
		q->parts = p->parts;
		p->parts = tempi;

		int tempi2 = q->year;
		q->year = p->year;
		p->year = tempi2;

		int tempi3 = q->rate;
		q->rate = p->rate;
		p->rate = tempi3;
	}

	void FindElement(string str)
	{
		try {
			list<Element>::iterator it = myList.begin();
			if (it == myList.end())
				throw string("������ ����!");

			bool result = false;
			for (it; result == true, it != myList.end(); ++it) {
				size_t pos = (it->name).find(str);
				if (pos != string::npos)
				{
					cout << "������ ������:" << endl;
					cout << it->name << setw(14)
						<< it->country << setw(14)
						<< it->year << setw(14)
						<< it->parts << setw(14)
						<< it->rate << endl;
					cout << endl;
					result = true;
				}
			}
			if (result == false)
				cout << "������ �� �������" << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void DeleteDuplicates()
	{
		try {
			list<Element>::iterator it = myList.begin();
			if (it == myList.end())
				throw string("������ ����!");
			list<Element>::iterator iEndNext = myList.end(); iEndNext--;
			list<Element>::iterator iEnd = myList.end();
			Sort(0);
			for (it; it != iEndNext && it != iEnd; ++it) {
				list<Element>::iterator itN = it; ++itN;
				if (it->name == itN->name && it->country == itN->country &&
					it->year == itN->year && it->parts == itN->parts)
				{
					//it->next = itN->next;
					myList.erase(itN);
				}
			}
		}
		catch (string str) {
			cout << str << endl;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Algoritm alg(myList);
	alg.Add("����������", "��������", 2, 1982, 8.845);
	alg.Add("���������", "�����", 1, 2000, 9.15);
	alg.Add("�������", "������", 1, 1998, 8.168);
	alg.Add("������������", "�������", 2, 2015, 8.745);
	alg.Add("������������_2", "�������", 2, 2019, 7.900);
	alg.Add("���������", "�������", 1, 2010, 8.55);
	alg.Add("���������", "�������", 1, 2010, 8.55);
	
	int choice;

	cout << "����: \n1 - ��������; 2 - ��������; 3 - �������� �������� �������; \n4 - ��������; 5 - ������� �������;" <<
		"\n6 - ���� �� ��������; 7 - ���� �� ������; 8 - ���� �� ������; 9 - ���� �� ����; 10 - ���� �� �������� \n" <<
		"11 - ����� �� ��������; 12 - ������� ���������; 13 - �����" << endl;
	cout << "\n�����: ";
	cin >> choice;

	while (choice >= 1 & choice <= 12) {
		switch (choice)
		{
		case 1: {
			alg.Add();
			break;
		}
		case 2: {
			alg.Print();
			break;
		}
		case 3: {
			alg.HeadElem();
			break;
		}
		case 4: {
			alg.Change();
			break;
		}
		case 5: {
			alg.Remove();
			break;
		}
		case 6: {
			alg.Sort(0);
			cout << setw(40) << "�� ��������: " << endl;
			cout << endl;
			alg.Print();
			break;
		}
		case 7: {
			alg.Sort(1);
			cout << setw(40) << "�� ������" << endl;
			cout << endl;
			alg.Print();
			break;
		}case 8: {
			alg.Sort(2);
			cout << setw(40) << "�� ������" << endl;
			cout << endl;
			alg.Print();
			break;
		}
		case 9: {
			alg.Sort(3);
			cout << setw(40) << "�� ����" << endl;
			cout << endl;
			alg.Print();
			break;
		}
		case 10: {
			alg.Sort(4);
			cout << setw(40) << "�� ��������" << endl;
			cout << endl;
			alg.Print();
			break;
		}
		case 11: {
			cout << "������� ����� ��������: ";
			string findStr;
			cin >> findStr;
			alg.FindElement(findStr);
			break; }
		case 12: {
			alg.DeleteDuplicates();
			cout << "��������� �������." << endl;
			break; }
		}
		cout << "�����: ";
		cin >> choice;
	}
	system("pause");
	return 0;
}

