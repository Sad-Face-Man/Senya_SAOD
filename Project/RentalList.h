#pragma once

#include "RentalListNode.h"

/*������ � ����������� � ������� ����*/
class RentalList
{
	/*�������� ������*/
	RentalListNode* head; //��������� �� ������ ������
	int _size;	 //���-�� ��������� � ������. ����������� � ����������.

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
	/*����� ����� ������� �� �����*/
	void display_firstLine();
	/*����� ������ � ����� ��������� �� �����.*/
	void display_elem(RentalListNode*);
	/*����� ������ �� �����*/
	void display_all();

	void swap(RentalListNode*, RentalListNode*);

	RentalListNode* operator [] (int);
};

