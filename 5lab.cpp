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
#include <forward_list>
#include <iterator>
#include<string.h>

using namespace std;

class List {
private:
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

		struct Element* next;
	};

	int Count;
	Element* Head;
	string _name, _country;
	int _parts, _year, _rate;

public:
	class Iterator {
	private:
		Element* currNode;
		//List* currList;
	public:
		Iterator(Element * node) {
			currNode = node;
		}

		bool operator==(const Iterator& other) const {
			if (this == &other) {
				return true;
			}
			return currNode == other.currNode;
		}

		bool operator!=(const Iterator& other) const {
			return !operator==(other);
		}

		Element* operator*() const {
			return currNode;
		}

		void operator++() {
			if (currNode) {
				currNode = currNode->next;
			}
			else cout << "��������� ����� ������!" << endl;
		}

		Element* nextNode() {
			return currNode->next;
		}

		void addElement(Element* node)
		{
			Element* temp = currNode;
			currNode = node;
			currNode->next = temp;
		}

		void changeElement(string name, string country, int parts, int year, double rate)
		{
			currNode->name = name;
			currNode->country = country;
			currNode->parts = parts;
			currNode->year = year;
			currNode->rate = rate;
		}

		void CurrShow() {
			cout << setw(14) << currNode->name << setw(14)
				<< currNode->country << setw(14)
				<< currNode->year << setw(14)
				<< currNode->parts << setw(14)
				<< currNode->rate << endl;
		}

		//		Element* ReturnHead() { return currList->Head; }
	};

	Iterator begin() const {
		return Iterator(Head);
	}
	Iterator end() const {
		return Iterator(NULL);
	}

	List() {
		Head = nullptr;
		Count = 0;
	}

	~List() {
		while (Head) {
			Remove();
		}
	}

	void Enter() {
		cout << "��������: ";
		cin >> _name;
		cout << "������: ";
		cin.clear();
		cin >> _country;
		cout << "�����: ";
		cin >> _parts;
		cout << "���: ";
		cin >> _year;
		cout << "�������: ";
		cin >> _rate;
	}

	int GetCount() {
		return Count;
	};

	void Add(string name, string country, int parts, int year, double rate)
	{
		Iterator it = begin();
		Element* newCartoon = new Element;
		newCartoon->name = name;
		newCartoon->country = country;
		newCartoon->year = year;
		newCartoon->parts = parts;
		newCartoon->rate = rate;

		it.addElement(newCartoon);
		Head = *it;
		Count++;
	}

	void Add()
	{
		Enter();
		Iterator it = begin();
		Element* newCartoon = new Element;
		newCartoon->name = _name;
		newCartoon->country = _country;
		newCartoon->year = _year;
		newCartoon->parts = _parts;
		newCartoon->rate = _rate;

		it.addElement(newCartoon);
		Head = *it;
		Count++;
	}

	void Change()
	{
		try {
			int id;
			cout << "����� ����������� �������: ";
			cin >> id;

			if (id == 0 || id > Size())
				throw string("�� �� ������ �������� ���� �������.");

			Iterator it = begin();
			for (int i = 1; i < id; i++)
				++it;

			Enter();
			it.changeElement(_name, _country, _parts, _year, _rate);
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Remove() {
		try {
			Iterator it = begin();
			if (it == end())
				throw string("������ ����!");
			Head = it.nextNode();
			delete *it;
			cout << "������� ��� ������." << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Clear()
	{
		while (Head) {
			Remove();
		}
	}

	void HeadElem() {
		try {
			Iterator it = begin();
			if (it == end())
				throw string("������ ����!");
			cout << "�������� �������: ";
			it.CurrShow();
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Print() {
		int i = 1;
		for (Iterator it = begin(); it != end(); ++it) {
			cout << i << ". ";
			it.CurrShow();
			i++;
		}
	};

	int Size() const {
		int s = 0;
		for (Iterator it = begin(); it != end(); ++it) {
			s++;
		}
		return s;
	}

	/*class Algoritm {
	public:
		Element* curr;
		List::Iterator it = List::Iterator(List::Head);
		it = List::begin();*/


	void Sort(int props)
	{
		Iterator left = begin();
		Iterator right = left.nextNode();
		//Element* left = this->Head;
		//Element* right = this->Head->next;

		while (left.nextNode())
		{
			while (*right)
			{
				switch (props)
				{
				case 0:
					if ((*left)->name > (*right)->name)
					{
						swap(left, right);
					}
					break;
				case 1:
					if ((*left)->country > (*right)->country)
					{
						swap(left, right);
					}
					break;
				case 2:
					if ((*left)->parts > (*right)->parts)
					{
						swap(left, right);
					}
					break;
				case 3:
					if ((*left)->year > (*right)->year)
					{
						swap(left, right);
					}
					break;
				case 4:
					if ((*left)->rate < (*right)->rate)
					{
						swap(left, right);
					}
					break;
				}
				right = right.nextNode();
			}
			left = left.nextNode();
			right = left.nextNode();
		}
	}

	void swap(Iterator q, Iterator p)
	{
		string temp = (*q)->name.substr(0, (*q)->name.size());
		(*q)->name = (*p)->name.substr(0, (*p)->name.size());
		(*p)->name = temp;

		string temp2 = (*q)->country.substr(0, (*q)->country.size());
		(*q)->country = (*p)->country.substr(0, (*p)->country.size());
		(*p)->country = temp2;

		int tempi = (*q)->parts;
		(*q)->parts = (*p)->parts;
		(*p)->parts = tempi;

		int tempi2 = (*q)->year;
		(*q)->year = (*p)->year;
		(*p)->year = tempi2;

		int tempi3 = (*q)->rate;
		(*q)->rate = (*p)->rate;
		(*p)->rate = tempi3;
	}

	void FindElement(string str)
	{
		try {
			Iterator it = begin();
			if (it == end())
				throw string("������ ����!");

			bool result = false;
			for (it = begin(); result == true, it != end(); ++it) {
				size_t pos = ((*it)->name).find(str);
				if (pos != string::npos)
				{					
					cout << "������ ������:" << endl;
					it.CurrShow();
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
			Iterator it = begin();
			if (it == end())
				throw string("������ ����!");
			Sort(0);
			for (it = begin(); it.nextNode()!=NULL && it != end(); ++it) {
				Iterator itN = it.nextNode();
				if ((*it)->name == (*itN)->name && (*it)->country == (*itN)->country &&
					(*it)->year == (*itN)->year && (*it)->parts == (*itN)->parts)
				{
					(*it)->next = (*itN)->next;
					delete (*itN);
				}
			}
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	//};
};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	List example;
	example.Add("����������", "��������", 2, 1982, 8.845);
	example.Add("���������", "�����", 1, 2000, 9.15);
	example.Add("�������", "������", 1, 1998, 8.168);
	example.Add("������������", "�������", 2, 2015, 8.745);
	example.Add("������������_2", "�������", 2, 2019, 7.900);
	example.Add("���������", "�������", 1, 2010, 8.55);
	example.Add("���������", "�������", 1, 2010, 8.55);
	

	cout << "������ ������: " << example.Size() << endl;
	example.HeadElem();
	

	example.Print();

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
			example.Add();
			break;
		}
		case 2: {
			example.Print();
			break;
		}
		case 3: {
			example.HeadElem();
			break;
		}
		case 4: {
			example.Change();
			break;
		}
		case 5: {
			example.Change();
			break; 
		}
		case 6: {
			example.Sort(0);
			cout << setw(40) << "�� ��������: " << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 7: {
			example.Sort(1);
			cout << setw(40) << "�� ������" << endl;
			cout << endl;
			example.Print();
			break;
		}case 8: {
			example.Sort(2);
			cout << setw(40) << "�� ������" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 9: {
			example.Sort(3);
			cout << setw(40) << "�� ����" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 10: {
			example.Sort(4);
			cout << setw(40) << "�� ��������" << endl;
			cout << endl;
			example.Print();
			break; 
		}
		case 11: {
			cout << "������� ����� ��������: ";
			string findStr;
			cin >> findStr;
			example.FindElement(findStr);
			break; }
		case 12: {
			example.DeleteDuplicates();
			cout << "��������� �������." << endl;
			break; }
		}
		cout << "�����: ";
		cin >> choice;
	}
	system("pause");
}