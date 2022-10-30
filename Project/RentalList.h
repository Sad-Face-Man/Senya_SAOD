#pragma once

#include "RentalListNode.h"

/*Список с информацией о прокате авто*/
class RentalList
{
	/*хранение данных*/
	RentalListNode* head; //указатель на голову списка
	int _size;	 //кол-во элементов в списке. ипользуется в сортировке.

public:
	RentalList();
	~RentalList();

	int getSize() { return _size; };

	bool emplace_front(string lic
		, string regN
		, string start
		, string end);
	bool remove(RentalListNode*&);
	void sort(int, int);
	void out();
	bool isEmpty() { return (head) ? false : true; };

	void add_ui();

	RentalListNode* findBy_licNum(string);
	RentalListNode* findBy_regNum(string);
	/*Вывод шапки таблицы на экран*/
	void display_firstLine();
	/*Вывод строки с одним элементом на экран.*/
	void display_elem(RentalListNode*);
	/*Вывод списка на экран*/
	void display_all();

	void swap(RentalListNode*, RentalListNode*);

	RentalListNode* operator [] (int);
};

