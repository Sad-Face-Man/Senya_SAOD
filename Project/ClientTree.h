#pragma once

#include "node.h"
#include "RentalList.h"

/*�������� ����������� �� ������ ������������� ������������� (licenseNum)*/
class ClientTree
{
	//node* root;

	/*�������� ������*/
	node* srl(node**);
	node* brl(node**);
	node* srr(node**);
	node* brr(node**);

	/*node* getNewNode(node::DATA val,
		node* l = nullptr,
		node* r = nullptr);*/

	node* balance(node*);
	int get_height(node*);
	void height_upd(node*);
	int bFactor(node*);
	
	node* find_min(node*&);
	node* remove_min(node*&);
	/*������ � ������������� ��� ����� ���������� � ����� �������*/
	node::DATA createForm(bool*);

public:
	node* root; //"������ ������"
	RentalList* listOfRent; //��������� ��� ��������� ������ ������

	ClientTree(RentalList*);
	~ClientTree();
	node* findBy_licNum(node*, const string, int* err);
	node* findBy_passportID(node*, const string, int* err);
	void findBy_SN(node*, const string, list<node>*);
	node* remove(node*, const string, bool&);
	bool isCorrect_licenseNum(string);
	bool isCorrect_passportID(string, int*);
	void display_tree(node* R, int l = 0);
	/*����� �������,  ��� ������ �� ������������� �������������*/
	void display_elem(node R);
	RentalListNode* display_elem_wCar(node R);
	/*����� ������ ����� ��� ������ � �������*/
	void display_treeScnd(RentalListNode*);

	void display_set(list<node>);
	bool isEmpty();
	node* add(node*& r, node::DATA n);

	void _dltTree(node*&);

	node* _get_root() { return root; };

	void add_ui();
	void display_ui();
	void del_ui();
	void clear_ui();
};

