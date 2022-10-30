#pragma once
/*���-������� ����������� ��������- ������������*/

#include "TableNode.h"
#include "RentalList.h"
#include <cstring>
#include <iomanip>
#include <fstream>
#include <windows.h>
#undef max

/*����������� ���-�������*/
class HashTable {

	const int m = 9; //����� �����
	const int m1 = m+1; //����� ����� +1
	const int tour = 6; //���-�� �������� ������
	// ���������, ������������ �� ������ ���-������� (������������ ������� �����)
	const int PRIME = 7;
	/*������ ��� �������*/
	int _size;
	/*���� ��� �������
	������� ��������� �� ��������� ������ ����.*/
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

	/*������� ������ �������*/
	void clear();
	/*���������,��������� �� �������� � �������*/
	bool isEmpty();
	/*���� ������ ��� ����������� ����*/
	TableNode createForm(bool* retTMen);
	/*��������� �������� � �������*/
	bool add(TableNode);
	/*������ � ������������� ��� ����������� ����*/
	void add_ui(bool* retTMen);
	/*������ � ������������� ��� �������� ���� � ��������*/
	void del_ui();
	/*�������� �� �������*/
	bool del(string);

	void clear_ui();
	/*����� ���� �������*/
	void display();
	/*����� ������ ����, ��� ������ �� ���. ������*/
	RentalListNode* display(TableNode elem);
	/*����� ��������*/
	void display_elem(TableNode);
	/*����� ������ ����� ��� ����������*/
	void display_hashScnd(RentalListNode* l);
	/*����� ������ ����, ��� ������ �� �����*/
	void display(list<TableNode>);
	short findBy_regNum(string);
	TableNode findBy_regNum_elem(string);
	list<TableNode>* findBy_brand(string);

	/*����������� ���� � ������*/
	void repair_login_ui(RentalList* r);
	/*����������� ���� � ������*/
	void repair_logout_ui(RentalList* r);

	bool isStateRegNumCorrect(string);
};