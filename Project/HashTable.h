#pragma once
/*Хеш-таблица автомобилей компании- арендодателя*/

#include "TableNode.h"
#include "RentalList.h"
#include <cstring>
#include <iomanip>
#include <fstream>
#include <windows.h>
#undef max

/*Организация хеш-таблицы*/
class HashTable {

	const int m = 9; //длина ключа
	const int m1 = m+1; //длина ключа +1
	const int tour = 6; //кол-во итераций поиска
	// константа, используемая во второй хеш-функции (обязательное простое число)
	const int PRIME = 7;
	/*Размер хеш таблицы*/
	int _size;
	/*сама хеш таблица
	Хрранит указатели на структуры данных авто.*/
	TableNode* table;

	int keyTo_int(string);
	int hash_1(string);
	int hash_2(string);
	void resize();

	bool set_repair(string inRN, bool rep_stat);

public:
	HashTable(RentalList*);
	~HashTable();

	RentalList* listOfRent;

	/*Очищает данные таблицы*/
	void clear();
	/*Проверяет,находятся ли элементы в таблице*/
	bool isEmpty();
	/*Ввод данных для регистрации авто*/
	TableNode createForm(bool* retTMen);
	/*Добавлени элемента в таблицу*/
	bool add(TableNode);
	/*Работа с пользователем для регистрации авто*/
	void add_ui(bool* retTMen);
	/*Работа с пользователем для удалении авто с площадки*/
	void del_ui();
	/*Удаление из таблицы*/
	bool del(string);

	void clear_ui();
	/*вывод всей таблицы*/
	void display();
	/*Вывод одного авто, при поиске по рег. номеру*/
	RentalListNode* display(TableNode elem);
	/*Выыод элемента*/
	void display_elem(TableNode);
	/*вывод ВТОРОЙ ЧАСТИ ДЛЯ ПОИСДЕРЕВЕ*/
	void display_hashScnd(RentalListNode* l);
	/*Вывод списка авто, при поиске по марке*/
	void display(list<TableNode>);
	short findBy_regNum(string);
	TableNode findBy_regNum_elem(string);
	list<TableNode>* findBy_brand(string);

	/*Регистрация авто в ремонт*/
	void repair_login_ui(RentalList* r);
	/*Регистрация авто в ремонт*/
	void repair_logout_ui(RentalList* r);

	bool isStateRegNumCorrect(string);
};