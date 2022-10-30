#include "HashTable.h"

HashTable::HashTable(RentalList* rl)
{
	listOfRent = rl;
	_size = 5000;
	table = new TableNode [_size];
}
HashTable::~HashTable()
{
	if (table)
		delete[] table;
}


/*������� ����� � �����*/
int HashTable::keyTo_int(string key) {
	/*����� ����� �������� (������ "-" �� ���������)*/
	int res(0);
	/*���������� ������ ��������*/
	/*�� ������ "-"*/
	for (int i(0); i < 7; i++)
		res += (int)key[i];
	/*����� ������� "-"*/
	res += (int)key[7] + (int)key[8];
	return res;
}
///*������ ���-�������*/
//int HashTable::hash_1(string key_char) {
//	long index = 0;
//	for (int i = 0; i < m1; i++) {
//		index += (int)key_char[i] * (int)key_char[i];
//	}
//	index %= _size;
//	return index;
//}
/*������ ���-�������*/
int HashTable::hash_1(string key)
{
	long index = 0;
	for (int i(0); i < key.length(); i++)
	{
		index += key[i] * pow(PRIME, i);
	}
	return index;
}
/*������ ���-�������*/
int HashTable::hash_2(string key_char) 	// ������ ���-�-���
{
	int key = keyTo_int(key_char);
	return (PRIME - (key % PRIME));
}

/*�������� ������� � ���-�������*/
bool HashTable::add(TableNode car) {
	int index1, index2, newIndex;
	index1 = hash_1(car.car_number);
	index2 = hash_2(car.car_number);
	for (int i = 0; i < tour; i++) {
		newIndex = (index1 + i * index2) % _size;
		/*����� �������*/
		if ((table[newIndex].car_number == "\0") || (table[newIndex].deleted)) {
			table[newIndex] = car;
			return true;
		}
	}
	return false;
	/*resize();
	return add(key);*/
}

/*��������� ������ �� ������������ ����� ���. ������ ����.*/
bool HashTable::isStateRegNumCorrect(string str)
{/*ANNNAA-NN*/
	const string allowedCheracters = "������������"; //������. �������
	const int m = 9; //����� �����
	if (str.length() != m)
		return false;
	/*�������� �� �����*/
	if (int(allowedCheracters.find(str[0])) == -1
		|| int(allowedCheracters.find(str[4])) == -1
		|| int(allowedCheracters.find(str[5])) == -1
		|| str[6] != '-')
		return false;
	/*�������� �� �����*/
	for (int i(1); i < 3; i++)
		if (!isdigit(str[i]))
			return false;
	if (!isdigit(str[7])
		|| !isdigit(str[8]))
		return false;

	return true;
}

/*����� �������� �� �����*/
short HashTable::findBy_regNum(string k) {
	int index1, index2, newIndex;
	index1 = hash_1(k);
	index2 = hash_2(k);
	/*�������� ������� tour ���*/
	for (unsigned long i(0); i < _size * tour; i++) {
		newIndex = (index1 + i * index2) % _size;
		/*������ ������- �������� ���*/
		if (table[newIndex].car_number == "\0")
			return -1;
		/*������ ��������- ��� ������*/
		if (table[newIndex].deleted)
			continue;
		/*����� �������- ����������*/
		if (table[newIndex].car_number == k)
			return newIndex;
	}
	/*������ �� � �� �����*/
	return -1;
}
/*����� �������� �� �����*/
TableNode HashTable::findBy_regNum_elem(string k) {
	TableNode emptyNode;
	int index1, index2, newIndex;
	index1 = hash_1(k);
	index2 = hash_2(k);
	/*�������� ������� tour ���*/
	for (unsigned long i(0); i < _size * tour; i++) {
		newIndex = (index1 + i * index2) % _size;
		/*������ ������- �������� ���*/
		if (table[newIndex].car_number == "\0")
			return emptyNode;
		/*������ ��������- ��� ������*/
		if (table[newIndex].deleted)
			continue;
		/*����� �������- ����������*/
		if (table[newIndex].car_number == k)
			return table[newIndex];
	}
	/*������ �� � �� �����*/
	return emptyNode;
}
list<TableNode>* HashTable::findBy_brand(string k)
{
	list<TableNode>* result = new list<TableNode>;
	result->clear();
	/*�������� �������*/
	for (int i(0); i < _size; i++)
		if (table[i].car_number != "\0")
			if (findInText(table[i].brand, k) != -1)
				result->emplace_back(table[i]);

	return result;
}

/*�������� �������� �� �������*/
bool HashTable::del(string k) {
	short index = findBy_regNum(k);
	if (index == -1)
		return false;
	table[index].deleted = true;
	table[index].car_number = "\0";
	table[index].brand.clear();
	table[index].yearOfManufacture = 0;
	table[index].color.clear();
	table[index].status = false;
	return true;
}

/*������� ������� �� �����*/
void HashTable::display() {
	if (this->isEmpty())
		cout << errorName(1101) << "\n\n";
	for (int i = 0; i < _size; i++)
	{
		//cout << i << ": ";
		bool is_deleted = false;
		if ((table[i].car_number == "d") && (table[i].car_number == "\0"))
			is_deleted = true;
		else
			is_deleted = false;
		/*if (table[i].car_number == "\0" || is_deleted)
		{
			cout << "-\n";
		}
		else if (table[i].car_number == "\0")
		{
			cout << "-\n";
		}
		else
			cout << table[i].car_number << endl;*/
		if (table[i].car_number != "\0")
			cout << i << ":\t" << table[i].car_number << endl;

	}
}
/*����� ��������*/
void HashTable::display_elem(TableNode elem)
{
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "�����:\t" << elem.car_number << endl
		<< "�����: \t" << elem.brand << endl
		<< "����:\t" << elem.color << endl
		<< "� �������: " << ((elem.repair) ? "��" : "���") << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}
/*����� ������ ����, ��� ������ �� ���. ������*/
RentalListNode*  HashTable::display(TableNode elem)
{/*���������� ����� ���. �������. ��� ���������� ���������*/
	RentalListNode* foundElem(nullptr);
	string licensNum(""); //����� �����. �������. ����������
	int err(0);

	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "�����:\t" << elem.car_number << endl
		<< "�����: \t" << elem.brand << endl
		<< "����:\t" << elem.color << endl
		<< "� �������: " << ((elem.repair) ? "��" : "���") << endl;
	foundElem = listOfRent->findBy_regNum(elem.car_number);

	return foundElem;
}
/*����� ������ ����� ��� ����������*/
void HashTable::display_hashScnd(RentalListNode* l)
{
	TableNode car;
	if (l)
	{
		/*���� ���������� � ������*/
		car = findBy_regNum_elem(l->stateRegNum);
		/*��� ���*/
		if (car.car_number == "\0")
		{
			cout << errorName(1007) << endl;
			exit(1);
		}
		cout << "������:" << endl
			<< "\t���. ����� ����.:\t\t" << car.car_number << endl;
	}
	else
		cout << errorName(1008) << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}
/*����� �� ����� ����*/
void HashTable::display(list<TableNode> lst)
{
	/*����� �����*/
	/*����� ��������� ������ � ����� �������*/
	list<TableNode>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++)
	{
		display_elem(*it);
		cout << endl;
	}

}

/*������� �������*/
void HashTable::clear()
{
	TableNode* a = new TableNode;
	if (table)
		for (int i(0); i < _size; i++)
			if(!listOfRent->findBy_regNum(table[i].car_number))
				table[i].clear();
}
/*���������, ��������� �� �������� � �������*/
bool HashTable::isEmpty()
{
	for (int i(0); i < _size; i++)
		if (table[i].car_number != "\0")
			return false;
	return true;
}
/*����������� ������ ���-������� � 2 ����
� ��������� ������ � ����������� �������.*/
void HashTable::resize()
{
	int prevSize(_size);
	_size *= 2;
	TableNode* newTable = new TableNode[_size];
	//void swap(table, newTable);

	/*��������� ������ �� ������ ������� � �����*/
	for (int i(0); i < prevSize; i++)
	{
		if (newTable[i].car_number != "\0")
			add(newTable[i]);
	}
}

/*���� ������ ��� ����������� ����*/
TableNode HashTable::createForm(bool* returnToMenu)
{
	TableNode newCar;
	int errorKey(0); // ��� ������ ��� ������ ������ ���� �-���.
	short int choice; //����� ������, ���������� ������������� � �������� ������.
	lopos variants;
	/*��� ��������� �������� ����*/
	time_t seconds = time(nullptr);
	tm* timeInfo = localtime(&seconds);
	unsigned int curYear(1900 + timeInfo->tm_year);
	*returnToMenu = false;

	/*���� ���������������� ������.
	�����- ����������*/
	while (!*returnToMenu)
	{
		cout << warningName(1101) << endl
			<< askName(1101) << ' ';
		getline(cin, newCar.car_number, '\n');
		/*��������� �����*/
		if (newCar.car_number == "0")
		{
			*returnToMenu = true;
			cout << warningName(9901) << endl;
		}
		/*��� ����� �����.*/
		else
		{
			if (!isStateRegNumCorrect(newCar.car_number))
			{
				cout << errorName(1103) << "\n��������� ����!\n\n";
				continue;
			}
			/*�������� �� ������������*/
			if (this->findBy_regNum(newCar.car_number) != -1)
			{
				cout << errorName(1104) << "\n��������� ����.\n\n";
				continue;
			}
			cout << endl;
			break;
		}

	}
	/*���� �����.*/
	while (!*returnToMenu)
	{
		cout << askName(1102) << ' ';
		getline(cin, newCar.brand, '\n');
		/*��������� �����*/
		if (newCar.brand == "0")
		{
			/*�������� ��� ������*/
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
		/*���� ������� �����.*/
		else
		{
			if (!isStrCorrect(newCar.brand, &errorKey))
			{
				cout << errorName(errorKey) << "\n��������� ����!\n\n";
				continue;
			}
			cout << endl;
			break;
		}
	}
	/*���� �����.*/
	while (!*returnToMenu)
	{
		cout << askName(1103) << ' ';
		getline(cin, newCar.color, '\n');
		/*��������� �����*/
		if (newCar.color == "0")
		{
			/*�������� ��� ������*/
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
		/*��� ����� �����.*/
		else
		{
			if (!isStrCorrect(newCar.color, &errorKey))
			{
				cout << errorName(errorKey) << "\n��������� ����!\n\n";
				continue;
			}
			cout << endl;
			break;
		}
	}
	/*���� ���� �������.*/
	while (!*returnToMenu)
	{
		newCar.yearOfManufacture = inputAndCheck_int(askName(1104));
		if (newCar.yearOfManufacture == 0)
		{
			/*�������� ��� ������*/
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
		/*��� ����� ��� ������������*/
		else
		{
			/*���� ��� ������������ <0 ��� ���� ������ �������� ����.*/
			if (newCar.yearOfManufacture < 0
				|| newCar.yearOfManufacture > curYear)
			{
				cout << errorName(1306) << "\n��������� ����!\n\n";
				continue;
			}
			break;
		}
	}
	if (*returnToMenu)
		newCar.clear();
	else
	{
		newCar.status = true;
		newCar.deleted = false;
	}
	return newCar;
}

/*����� � ������������� ��� ����������� ����*/
void HashTable::add_ui(bool* returnToMenu)
{
	TableNode car;
	*returnToMenu = false;

	car = createForm(returnToMenu);
	if (!*returnToMenu)
		if (this->add(car))
			cout << "����������� ���� ������ �������\n\n";
		else
			cout << "���� ������ �����������: �� ������� �������� �������.\n\n";
}
/*������ � ������������� ��� �������� ���� � ��������*/
void HashTable::del_ui()
{
	lopos variants;
	short choice, index;
	string numTDel("\0"); //����� ���� ��� ��������.

	if (this->isEmpty())
		cout << errorName(1101) << "\n\n";
	else
	{
		cout << warningName(1101) << endl
			<< askName(1106) << ' ';
		getline(cin, numTDel, '\n');
		cout << endl;
		if (isStateRegNumCorrect(numTDel))
		{
			index = this->findBy_regNum(numTDel);
			if (index != -1)
			{
				/*������ ��������*/
				if (listOfRent->findBy_regNum(numTDel))
				{
					cout << errorName(1206) << endl;
					return;
				}
				cout << warningName(1102) << endl;
				display(table[index]);
				cout << endl;
				variants.emplace_back("�", ", ����� ����������� ��������");
				variants.emplace_back("�", ", ��� ������");
				choice = chooseDoing(askName(1107), variants);
				if (!choice)
				{
					if (this->del(numTDel))
						cout << "���������� ������� �����.";
					else
						cout << "������ ��������.";
					cout << endl;
				}
				else
				{
					cout << warningName(9901) << endl;
				}
			}
			else
				cout << errorName(1102) << "\n\n"; //������ ���� ��� � �������				
		}
		else
			cout << errorName(1103) << endl;
	}
}

/*������ � ������������� ��� ������� �������*/
void HashTable::clear_ui()
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
				this->clear();
				cout << "��� ���������� ���� ������� �������.\n";
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

/*������ ���� repair*/
bool HashTable::set_repair(string inRN, bool rep_stat)
{
	int index = findBy_regNum(inRN);
	if (index != -1)
	{
		table[index].repair = rep_stat;
		return true;
	}
	return false;

}
/*��������� ���� � ������*/
void HashTable::repair_login_ui(RentalList* r)
{
	TableNode* helpPtr(nullptr);
	int index(0);
	string value("");

	cout << askName(1108) << ' ';
	getline(cin, value, '\n');
	
	/*���������� ���������� ���.  ������*/
	if (isStateRegNumCorrect(value))
	{
		/*����� ���������� �� ���������������*/
		if ((index = findBy_regNum(value)) == -1)
			cout << errorName(1105) << endl;
		else
		{
			/*���� ������ ��������*/
			if (r->findBy_regNum(value))
				cout << errorName(1204) << endl;
			/*���� ��� � �������*/
			else if (this->table[index].repair)
				cout << errorName(1107) << endl;
			else
			{
				this->table[index].repair = true;
				cout << "\n���������� ��������� � ������.\n\n";
			}
		}
	}
	else //������������ ����
		cout << errorName(1302) << endl;
}
/*������� ���� �� �������*/
void HashTable::repair_logout_ui(RentalList* r)
{
	TableNode* helpPtr(nullptr);
	int index(0);
	string value("");

	cout << askName(1109) << ' ';
	getline(cin, value, '\n');

	/*���������� ���������� ���.  ������*/
	if (isStateRegNumCorrect(value))
	{
		/*����� ���������� �� ���������������*/
		if ((index = findBy_regNum(value)) == -1)
			cout << errorName(1105) << endl;
		else
		{
			/*���� � ��� �� � �������*/
			if (!this->table[index].repair)
				cout << errorName(1108) << endl;
			else
			{
				this->table[index].repair = false;
				cout << "\n���������� �������� �� �������.\n\n";
			}
		}
	}
	else //������������ ����
		cout << errorName(1302) << endl;
}


