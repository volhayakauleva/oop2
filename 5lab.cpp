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
			try{
				if (!currNode)
					throw string("Достигнут конец списка!");
				currNode = currNode->next;
			}
			catch (string str) {
				cout << str << endl;
			}
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
		cout << "Название: ";
		cin >> _name;
		cout << "Страна: ";
		cin.clear();
		cin >> _country;
		cout << "Части: ";
		_parts = checkIfInt("Повторите ввод (Части): ");
		cout << "Год: ";
		_year = checkIfInt("Повторите ввод (Год): ");
		cout << "Рейтинг: ";
		_rate = checkIfInt("Повторите ввод (Рейтинг): ");
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
			cout << "Номер изменяемого объекта: ";
			cin >> id;

			if (id == 0 || id > Size())
				throw string("Вы не можете изменить этот элемент.");

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
				throw string("Список пуст!");
			Head = it.nextNode();
			delete *it;
			cout << "Элемент был удален." << endl;
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
				throw string("Список пуст!");
			cout << "Головной элемент: ";
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

	class Algoritm {																																																																																																											};

	public:
	void Sort(int props)
	{
		List::Iterator left = List::begin();
		List::Iterator right = left.nextNode();

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

	void swap(List::Iterator q, List::Iterator p)
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
			List::Iterator it = List::begin();
			if (it == end())
				throw string("Список пуст!");

			bool result = false;
			for (it = List::begin(); result == true, it != List::end(); ++it) {
				size_t pos = ((*it)->name).find(str);
				if (pos != string::npos)
				{					
					cout << "Запрос найден:" << endl;
					it.CurrShow();
					cout << endl;
					result = true;
				}
			}
			if (result == false)
				cout << "Ничего не найдено" << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void DeleteDuplicates()
	{
		try {		
			List::Iterator it = List::begin();
			if (it == end())
				throw string("Список пуст!");
			Sort(0);
			for (it = List::begin(); it.nextNode()!=NULL && it != List::end(); ++it) {
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

};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	List example;
	example.Add("Белоснежка", "Германия", 2, 1982, 8.845);
	example.Add("Русалочка", "Дания", 1, 2000, 9.15);
	example.Add("Колобок", "Россия", 1, 1998, 8.168);
	example.Add("Суперсемейка", "Америка", 2, 2015, 8.745);
	example.Add("Суперсемейка_2", "Америка", 2, 2019, 7.900);
	example.Add("Рапунцель", "Америка", 1, 2010, 8.55);
	example.Add("Рапунцель", "Америка", 1, 2010, 8.55);

	int choice;

	cout << "Меню: \n1 - Добавить; 2 - Показать; 3 - Показать головной элемент; \n4 - Изменить; 5 - Удалить элемент;" <<
		"\n6 - Сорт по названию; 7 - Сорт по стране; 8 - Сорт по частям; 9 - Сорт по году; 10 - Сорт по рейтингу \n" <<
		"11 - Поиск по названию; 12 - Удалить дубликаты; 13 - Выход" << endl;
	cout << "\nВыбор: ";
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
			cout << setw(40) << "По названию: " << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 7: {
			example.Sort(1);
			cout << setw(40) << "По стране" << endl;
			cout << endl;
			example.Print();
			break;
		}case 8: {
			example.Sort(2);
			cout << setw(40) << "По частям" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 9: {
			example.Sort(3);
			cout << setw(40) << "По году" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 10: {
			example.Sort(4);
			cout << setw(40) << "По рейтингу" << endl;
			cout << endl;
			example.Print();
			break; 
		}
		case 11: {
			cout << "Введите часть названия: ";
			string findStr;
			cin >> findStr;
			example.FindElement(findStr);
			break; }
		case 12: {
			example.DeleteDuplicates();
			cout << "Дубликаты удалены." << endl;
			break; }
		}
		cout << "Выбор: ";
		cin >> choice;
	}
	system("pause");
}
