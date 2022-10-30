#pragma once

#include "node.h"
#include "RentalList.h"

/*Элементы сортируются по номеру водительского удостоверения (licenseNum)*/
class ClientTree
{
	//node* root;

	/*повороты дерева*/
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
	/*Работа с пользователем для ввода информации о новом клиенте*/
	node::DATA createForm(bool*);

public:
	node* root; //"корень дерева"
	RentalList* listOfRent; //переменна для просмотра списка аренды

	ClientTree(RentalList*);
	~ClientTree();
	node* findBy_licNum(node*, const string, int* err);
	node* findBy_passportID(node*, const string, int* err);
	void findBy_SN(node*, const string, list<node>*);
	node* remove(node*, const string, bool&);
	bool isCorrect_licenseNum(string);
	bool isCorrect_passportID(string, int*);
	void display_tree(node* R, int l = 0);
	/*Вывод клиента,  при поиске по водительскому удостоверению*/
	void display_elem(node R);
	RentalListNode* display_elem_wCar(node R);
	/*вывод ВТОРОЙ ЧАСТИ ДЛЯ ПОИСКА В ТАБЛИЦЕ*/
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

