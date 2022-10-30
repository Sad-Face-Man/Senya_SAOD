#include "ClientTree.h"

ClientTree::ClientTree(RentalList* rl)
{
	listOfRent = rl;
	root = nullptr;
}
/*����������� �������� ������*/
void ClientTree::_dltTree(node*& p)
{
	if (p)
	{
		_dltTree(p->left);
		_dltTree(p->right);
		delete p;
		p = nullptr;
	}
	
}
ClientTree::~ClientTree()
{
	if (root)
	{
		_dltTree(root);
	}
}

/*��� �������� ���������� �� ����������� ��������
�����- ������ ������� �������, ������- �� ������� �������*/
/*����� ����� ��������*/
node* ClientTree::srl(node** curRoot)
{
	node* newRoot = (*curRoot)->right;
	(*curRoot)->right = newRoot->left;
	newRoot->left = (*curRoot);

	height_upd(*curRoot);
	height_upd(newRoot);

	return newRoot;
}
/*����� ������ ��������*/
node* ClientTree::srr(node** curRoot)
{
	node* newRoot = (*curRoot)->left;
	(*curRoot)->left = newRoot->right;
	newRoot->right = (*curRoot);

	height_upd(*curRoot);
	height_upd(newRoot);

	return newRoot;
}
/*������� ����� ��������*/
node* ClientTree::brl(node** curRoot)
{
	node* newRoot = nullptr;

	(*curRoot)->right = srr(&(*curRoot)->right);
	newRoot = srl(curRoot);
	return newRoot;
}
/*������� ������ ��������*/
node* ClientTree::brr(node** curRoot)
{
	node* newRoot = nullptr;

	(*curRoot)->left = srl(&(*curRoot)->left);
	newRoot = srr(curRoot);
	return newRoot;
}

/*�������, ����������� ����������� �������, ���� ��� ����������
���������� ��������� �� ����� �������, ����������� �� ����� "�������"*/
node* ClientTree::balance(node* p)
{
	height_upd(p);
	switch (bFactor(p))
	{
		/*������� ����� - ������ �������*/
	case(-2):
		/*������ ��������� ������- ������� �������,
			������ �������- �������*/
		return (bFactor(p->left) > 0) ? brr(&p) : srr(&p);
		/*������� ������ - ������ �������*/
	case(2):
		/*������ ��������� ������- ������� �������,
			����� �������- �������*/
		return (bFactor(p->right) < 0) ? brl(&p) : srl(&p);
		/*������������ �� �����*/
	default:
		return p;
	}
}

///*��������� ����� ��� ����� ���� ������ � ����������� ��� �������*/
//node* ClientTree::getNewNode(node::DATA value, node* l, node* r)
//{
//	node* newnode = new node(value, l, r);
//
//	/*��������� ������ ��������� ������*/
//	if (!newnode)
//	{
//		std::cerr << "������ ��������� ������!" << endl;
//		exit(1);
//	}
//	else
//	{
//		return newnode;
//	}
//}

/*��� �������- �������� ������ ������ �� �������� �������� �
���������� ������������*/
node* ClientTree::add(node*& curRoot, node::DATA newNode)
{
	/*������������ ����������� �������� ������ ��� ��� ������, � ��
	�������� �� ��������, �.�. ����� �� �������� ����� ������ ���-�������.
	�������� ��� ������ ������ ������������ � ������ �������.

	� �����  ��������� ������������ �������� < ����������������
	� ������ ��������� ������������ �������� > ����������������.*/

	/*curRoot-����, � ������� ��� ��������� � ������ ������*/
	//node* tempP(nullptr);

	/*����� ����� ��� �������*/
	if (!curRoot)
	{
		/*�������������� ����� �������*/
		node* root = new node(newNode);
		curRoot = root;
		curRoot->height = 1;
		return curRoot;
	}
	/*���������� ����*/
	/*����� � ����� ���������*/
	if (newNode < curRoot->data)
		add(curRoot->left, newNode);
	else
		/*����� � ������ ���������*/
		if (newNode > curRoot->data)
			add(curRoot->right, newNode);
		else
			/*����� ������� ��� ��� � ������- ������ �� ���������*/
			return curRoot;
	/*������������ ����, ��� ���������� �����������*/
	curRoot = balance(curRoot);
	return curRoot;
}

///*���������� ��������� ������, �� ������� ��������� ������*/
//int ClientTree::Height(node* root)
//{
//	/*�������� ����� ������*/
//	if (!root)
//		return 0;
//	int hLeft = Height(root->left);		//������������ ������ ������ ���������
//	int hRight = Height(root->right);	//������������ ������ ������� ���������
//
//	/*����������� ������ ����������� ��������� + 1 �� ���� ���������������� ����*/
//	return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
//}

/*���������� ������ ������*/
int ClientTree::get_height(node* p)
{
	/*������, ����� �������� ���� � �������� �����������*/
	return p ? p->height : 0;
}

/*������������� � ���������� ������ ������*/
int ClientTree::bFactor(node* p)
{
	/*�������� ��� ���������� ������� ��������*/
	return get_height(p->right) - get_height(p->left);
}

/*��������� ������ ����*/
void ClientTree::height_upd(node* p)
{
	/*�������� � ����������� �������� ��������*/
	if (p)
	{
		int h_1 = get_height(p->left);
		int h_2 = get_height(p->right);

		p->height = (h_1 > h_2) ? h_1 + 1 : h_2 + 1;
	}
}

/*����� ������������ ��������, ������� � ����������� ����*/
node* ClientTree::find_min(node*& curNode)
{
	return curNode->left ? find_min(curNode->left) : curNode;
}
/*�������� ������������ �������� �� ������ ��� ��� �������� �� ������*/
node* ClientTree::remove_min(node*& value)
{
	/*� ������������ �������� �� �������� ����� ���� ������ 1 ������ ��� �� ���� ������*/
	/*����� �����������*/
	if (!value->left)
		return value->right;
	value->left = remove_min(value->left);
	return balance(value);

}
/*�������� �������� �� ������*/
node* ClientTree::remove(node* R, const string val, bool& del) {

	if (!R) return 0;
	if (val < R->data.licenseNum)
		R->left = remove(R->left, val, del);
	else if (val > R->data.licenseNum)
		R->right = remove(R->right, val, del);
	else {
		node* l = R->left;
		node* r = R->right;
		delete R;
		R = nullptr;
		del = true;
		if (r == NULL) return l;
		node* min = find_min(r);
		min->right = remove_min(r);
		min->left = l;
		return balance(min);
	}
	return balance(R);
}
//node* ClientTree::remove(node* root, node::DATA value)
//{
//	if (!root)
//		return nullptr;
//	/*����������� �����*/
//	/*� ���� ���������*/
//	if (value < root->data)
//		root->left = remove(root->left, value);
//	/*� ������ ���������*/
//	else if (value > root->data)
//		root->right = remove(root->right, value);
//	else //����� �������
//	{
//		/*��������� ��������*/
//		node* l = root->left;
//		node* r = root->right;
//		delete root;
//
//		if (!r)
//			return l;
//		node* min = find_min(r);
//		min->right = remove_min(r);
//		min->left = l;
//
//		return balance(min);
//	}
//	/*��������� ������������� ���� ����� ������� �� ��������*/
//	return balance(root);
//
//}

/*����� �� ������������� ������������*/
node* ClientTree::findBy_licNum(node* curRoot, const string value, int* err)
{
	node* res(nullptr), * temp(nullptr);
	/*err- ���������� ����� ������*/
	if (!this->root)
	{
		*err = 1002;//�� ������� ����
		return nullptr;
	}
	if (!isCorrect_licenseNum(value))
	{
		*err = 1003; //�����������  ������ ��� ������
		return nullptr;
	}
	if (curRoot)
	{
		if (value < curRoot->data.licenseNum)
		{
			temp = findBy_licNum(curRoot->left, value, err);
			if (temp)
				res = temp;
		}
		if (value > curRoot->data.licenseNum)
		{
			temp = findBy_licNum(curRoot->right, value, err);
			if (temp)
				res = temp;
		}
	}
	if (curRoot)
	{
		/*���� ����� ���������� ����- ��������� ��� � ��������� � ����������*/
		if (value == curRoot->data.licenseNum)
			return curRoot;
	}
	/*���������� ���������� �������� ���� ����� ��� ������� ��������*/
	return res;
}
/*����� �� ������ ��������*/
node* ClientTree::findBy_passportID(node* curRoot, const string value, int* err)
{
	node* res(nullptr), * temp(nullptr);
	if (curRoot)
	{
		temp = findBy_passportID(curRoot->left, value, err);
		if (temp)
			res = temp;
		temp = findBy_passportID(curRoot->right, value, err);
		if (temp)
			res = temp;
		/*���� ����� ���������� ����- ��������� ��� � ��������� � ����������*/
		if (value == curRoot->data.passportID)
			return curRoot;
		/*���������� ���������� �������� ���� ����� ��� ������� ��������*/
	}
	return res;
}
/*����� �� ���*/
void ClientTree::findBy_SN(node* curRoot, const string value, list<node>* res)
{
	if (curRoot)
	{
		findBy_SN(curRoot->left, value, res);
		findBy_SN(curRoot->right, value, res);

		if (findInText(curRoot->data.fullName, value) != -1)
			res->push_back(*curRoot);
	}
}

/*�������� �� ������������ ������ ������ ������������� �������������*/
bool ClientTree::isCorrect_licenseNum(string str)
{/*������ ������ licenseNum: RR AA NNNNNN*/
/*RR- ��� ������� (�����); */
/*AA � ����� (����� �� ���������� ���������:
	�, �, �, �, �, �, �, �, �, �, �, �);*/
	/*NNNNNN � ���������� ����� ������������� (�����).*/

	/*����������� �������*/
	const string allowedCheracters = "������������-";
	if (str.length() != 10)
		return false;
	if (!isdigit(str[0]) || !isdigit(str[1]))
		return false;
	if (int(allowedCheracters.find(str[2])) == -1
		|| int(allowedCheracters.find(str[3])) == -1)
		return false;
	/*�������� ������� ������ ����������� ��������*/
	for (int i(4); i < str.length(); i++)
		if (!isdigit(str[i]))
			return false;
	return true;
}
/*�������� �� ������������ ������ ��������*/
bool ClientTree::isCorrect_passportID(string num, int* err)
{/*10 ���� ��� ��������*/
	if (num.length() != 10)
	{
		*err = 1312;
		return false;
	}
	for (int i(0); i < num.length(); i++)
	{
		if (!isdigit(num[i]))
		{
			*err = 1312;
			return false;
		}
	}
	return true;
}

/*����� ������ �� �����*/
void ClientTree::display_tree(node* R, int l) {
	if (R)
	{
		display_tree(R->right, l + 11);
		for (int i = 1; i <= l; i++) cout << " ";
		cout << R->data.licenseNum << endl; //������� ������ ������������� �������������
		display_tree(R->left, l + 11);
	}
}
void ClientTree::display_ui()
{
	if(root)	display_tree(this->root);
	else		cout << errorName(1001) << endl;
}
/*����� �������, ��� ������ �� ������������� �������������.*/
RentalListNode* ClientTree::display_elem_wCar(node elem)
{
	RentalListNode* foundElem(nullptr);
	string regNum(""); //����� ����.

	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "����� ������������ �������������:\t" << elem.data.licenseNum << endl
		<< "���:\t\t\t\t" << elem.data.fullName << endl
		<< "����� ����������:\t\t" << elem.data.adress<< endl;

	foundElem = listOfRent->findBy_licNum(elem.data.licenseNum);

	return foundElem;


	

}
/*����� ������ ����� ��� ������ � �������*/
void ClientTree::display_treeScnd(RentalListNode* l)
{
	node* client(nullptr);
	int err;
	if (l)
	{
		/*���� ���������� � ������*/
		client = findBy_licNum(root, l->clientLicenseNum, &err);
		/*��� ��� (� ������, ��������� � ��� ���� => ������)*/
		if (!client)
		{
			cout << errorName(1007) << endl;
			exit(1);
		}
		cout << "����������:" << endl
			<< "\t���:\t\t" << client->data.fullName << endl
			<< "\t����� ������������� �������������:\t" << client->data.licenseNum << endl;
	}
	else
		cout << errorName(1109) << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}

/*����� �������, ��� ������ �� �����.*/
void ClientTree::display_elem(node elem)
{

	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "����� ������������ �������������:\t" << elem.data.licenseNum << endl
		<< "���:\t\t\t\t\t" << elem.data.fullName << endl
		<< "����� ����������:\t\t\t" << elem.data.adress << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}
/*����� ������ ��������, ��� ������ �� ���.*/
void ClientTree::display_set(list<node> set)
{
	list<node>::iterator it;
	if (!set.empty())
	{
		for (it = set.begin(); it != set.end(); it++)
		{
			display_elem(*it);
			cout << endl;
		}
	}
}

/*���� �� �������� � ������*/
bool ClientTree::isEmpty()
{
	return (root) ? false : true;
}

/*���� ���������� � ����� �������*/
node::DATA ClientTree::createForm(bool* returnToMenu)
{
	node::DATA person;
	node* tempP(nullptr);
	int errorKey(0); // ��� ������ ��� ������ ������ ���� �-���.
	short int choice; //����� ������, ���������� ������������� � �������� ������.
	lopos variants;
	*returnToMenu = false;

	/*���*/
	while (!*returnToMenu)
	{
		cout << askName(1001) << ' ';
		getline(cin, person.fullName, '\n');
		/*��������� �����*/
		if (person.fullName == "0")
		{
			*returnToMenu = true;
			cout << warningName(9901) << endl;
		}
		/*����� ���*/
		else
		{
			if (!isNameCorrect(person.fullName, &errorKey))
			{
				cout << errorName(errorKey) << "\n��������� ����!\n\n";
				continue;
			}
			cout << endl;
		}
		break;
	}
	/*������������ �������������*/
	while (!*returnToMenu)
	{
		cout << warningName(1001) << endl
			<< askName(1002) << ' ';
		getline(cin, person.licenseNum, '\n');
		/*�������� �����*/
		if (person.licenseNum == "0")
		{
			variants.emplace_back("�", ", ����� ����� � ����");
			variants.emplace_back("�", ", ����� ���������� ����");
			choice = chooseDoing(warningName(9903), variants);
			variants.clear();   //������� ������ ���������

			if (!choice) //����� ����� � ����.
			{
				*returnToMenu = true;
				cout << warningName(9901) << "\n\n";
			}
			else
			{
				*returnToMenu = false;
				cout << warningName(9902) << endl << endl;
				continue;
			}
		}
		/*����� ����� �����. �������.*/
		else
		{
			if (!isCorrect_licenseNum(person.licenseNum))
			{
				cout << errorName(1302) << "\n��������� ����.\n\n";
				continue;
			}
			/*�������� �� ������������*/
			if (this->findBy_licNum(this->root, person.licenseNum, &errorKey))
			{
				cout << errorName(1004) << "\n��������� ����.\n\n";
				continue;
			}
		}
		break;
	}
	/*����� ��������*/
	while (!*returnToMenu)
	{
		cout << warningName(1002) << endl
			<< askName(1003) << ' ';
		getline(cin, person.passportID, '\n');
		/*�������� �����*/
		if (person.passportID == "0")
		{
			variants.emplace_back("�", ", ����� ����� � ����");
			variants.emplace_back("�", ", ����� ���������� ����");
			choice = chooseDoing(warningName(9903), variants);
			variants.clear();   //������� ������ ���������

			if (!choice) //����� ����� � ����.
			{
				*returnToMenu = true;
				cout << warningName(9901) << "\n\n";
			}
			else
			{
				*returnToMenu = false;
				cout << warningName(9902) << endl << endl;
				continue;
			}
		}
		/*����� ����� ��������*/
		else
		{
			if (!isCorrect_passportID(person.passportID, &errorKey))
			{
				cout << errorName(errorKey) << "\n��������� ����.\n\n";
				continue;
			}
			else
			{
				/*�������� �� ������������*/
				if (this->findBy_passportID(this->root, person.passportID, &errorKey))
				{
					cout << errorName(1005) << "\n��������� ����.\n\n";
					continue;
				}
			}
		}
		break;
	}
	/*����� ����������*/
	while (!*returnToMenu)
	{
		cout << askName(1004) << ' ';
		getline(cin, person.adress, '\n');
		/*�������� �����*/
		if (person.adress == "0")
		{
			variants.emplace_back("�", ", ����� ����� � ����");
			variants.emplace_back("�", ", ����� ���������� ����");
			choice = chooseDoing(warningName(9903), variants);
			variants.clear();   //������� ������ ���������

			if (!choice) //����� ����� � ����.
			{
				*returnToMenu = true;
				cout << warningName(9901) << "\n\n";
			}
			else
			{
				*returnToMenu = false;
				cout << warningName(9902) << endl << endl;
				continue;
			}
		}
		break;
	}
	if (*returnToMenu)
		person.clear();
	return person;
}

/*������ � ������������� ��� ����������� ������� ��������*/
void ClientTree::add_ui()
{
	bool returnTMenu(false);
	node::DATA newPerson = createForm(&returnTMenu);
	if (!returnTMenu)
	{
		add(this->root, newPerson);
		cout << "����������� ������� ������ �������." << endl;
	}
}

/*������ � ������������� ��� �������� ������������*/
void ClientTree::del_ui()
{
	int plug;
	bool deleted(false);
	if (this->root)
	{
		string strTDel;
		cout << warningName(1001) << endl
			<< askName(1002) << ' ';
		getline(cin, strTDel, '\n');
		/*��������� �����*/
		if (strTDel == "0")
			cout << warningName(9901) << endl;
		else
			if (isCorrect_licenseNum(strTDel))
			{
				if (findBy_licNum(root, strTDel, &plug))
				{
					if (listOfRent->findBy_licNum(strTDel))
					{
						cout << errorName(1207) << endl;
						return;
					}
					else
					{
						this->root = remove(this->root, strTDel, deleted);
						if (deleted)
							cout << "�������� ������ �������." << endl;
						else
							cout << "�� ������� �������� ��� ��������." << endl;
					}
				}
				else
					cout << "�� ������� �������� ��� ��������." << endl;
			}
			else
				cout << "�������� �� ���� �����������" << endl;
	}
	else
		cout << errorName(1001) << endl;
}
void ClientTree::clear_ui()
{
	lopos variants;
	int choice;

	if (!this->isEmpty())
	{
		//variants.clear();
		variants.emplace_back("�", "- �������");
		variants.emplace_back("�", "- ������");
		choice = chooseDoing(askName(1101), variants);
		variants.clear();

		if (choice)
		{
			cout << warningName(9901) << endl;
		}
		else
		{
			if (listOfRent->isEmpty())
			{
				this->_dltTree(this->root);
				cout << "��� ������� ���� ������� �������.\n";
			}
			else
			{
				cout << errorName(1208) << endl;
			}
		}
	}
	else
		cout << errorName(1101) << endl;
}
