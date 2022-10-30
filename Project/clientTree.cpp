#include "ClientTree.h"

ClientTree::ClientTree(RentalList* rl)
{
	listOfRent = rl;
	root = nullptr;
}
/*Рекурсивное удаление дерева*/
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

/*Все повороты называются по направлению поворота
левый- против часовой стрелки, правый- по часовой стрелке*/
/*Малое левое вращение*/
node* ClientTree::srl(node** curRoot)
{
	node* newRoot = (*curRoot)->right;
	(*curRoot)->right = newRoot->left;
	newRoot->left = (*curRoot);

	height_upd(*curRoot);
	height_upd(newRoot);

	return newRoot;
}
/*Малое правое вращение*/
node* ClientTree::srr(node** curRoot)
{
	node* newRoot = (*curRoot)->left;
	(*curRoot)->left = newRoot->right;
	newRoot->right = (*curRoot);

	height_upd(*curRoot);
	height_upd(newRoot);

	return newRoot;
}
/*Большое левое вращение*/
node* ClientTree::brl(node** curRoot)
{
	node* newRoot = nullptr;

	(*curRoot)->right = srr(&(*curRoot)->right);
	newRoot = srl(curRoot);
	return newRoot;
}
/*Большое правое вращение*/
node* ClientTree::brr(node** curRoot)
{
	node* newRoot = nullptr;

	(*curRoot)->left = srl(&(*curRoot)->left);
	newRoot = srr(curRoot);
	return newRoot;
}

/*Функция, выполняющая необходимый поворот, если это необходимо
Возвращает указатель на новый элемент, находящийся на месте "старого"*/
node* ClientTree::balance(node* p)
{
	height_upd(p);
	switch (bFactor(p))
	{
		/*Перевес влево - правый поворот*/
	case(-2):
		/*Левове поддерево больше- большой поворот,
			правое большое- большой*/
		return (bFactor(p->left) > 0) ? brr(&p) : srr(&p);
		/*Перевес вправо - ллевый поворот*/
	case(2):
		/*правое поддерево больше- большой поворот,
			левое большое- большой*/
		return (bFactor(p->right) < 0) ? brl(&p) : srl(&p);
		/*Балансировка не нужна*/
	default:
		return p;
	}
}

///*Выделение места под новый узел дерева с заполнением его данными*/
//node* ClientTree::getNewNode(node::DATA value, node* l, node* r)
//{
//	node* newnode = new node(value, l, r);
//
//	/*произощла ошибка выделения памяти*/
//	if (!newnode)
//	{
//		std::cerr << "ошибка выделения памяти!" << endl;
//		exit(1);
//	}
//	else
//	{
//		return newnode;
//	}
//}

/*АВл вставка- алгоритм обхода дерева со вставкой элемента и
конетролем балансировки*/
node* ClientTree::add(node*& curRoot, node::DATA newNode)
{
	/*используется стандартный алгоритм поиска для АВЛ дерева, а не
	заданный по варианту, т.к. тогда бы утерялся смысл самого АВЛ-дереева.
	Заданный тип обхода дерева используется в другой функции.

	В левое  поддерево записываются элементы < рассматриваемого
	В правое поддерево записываются элементы > рассматриваемого.*/

	/*curRoot-узел, с которым идёт сравнение в данный момент*/
	//node* tempP(nullptr);

	/*Нашли место для вставки*/
	if (!curRoot)
	{
		/*Инициализируем новый элемент*/
		node* root = new node(newNode);
		curRoot = root;
		curRoot->height = 1;
		return curRoot;
	}
	/*Спускаемся ниже*/
	/*спуск в левое поддерево*/
	if (newNode < curRoot->data)
		add(curRoot->left, newNode);
	else
		/*Спуск в правое поддерево*/
		if (newNode > curRoot->data)
			add(curRoot->right, newNode);
		else
			/*Такой элемент уже был в дереве- ничего не вставляем*/
			return curRoot;
	/*Корректируем узел, при проведении балнсировки*/
	curRoot = balance(curRoot);
	return curRoot;
}

///*рекурсивно вычисляет высоту, на которой находится корень*/
//int ClientTree::Height(node* root)
//{
//	/*Обратный обход дерева*/
//	if (!root)
//		return 0;
//	int hLeft = Height(root->left);		//рассчитываем высоту левого поддерева
//	int hRight = Height(root->right);	//рассчитываем высоту правого поддерева
//
//	/*Возваращаем высоту наибольшего поддерева + 1 за счёт рассматриваемого узла*/
//	return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
//}

/*Возвращает высоту дерева*/
int ClientTree::get_height(node* p)
{
	/*Обёртка, чтобы работать даже с нулевыми указателями*/
	return p ? p->height : 0;
}

/*Расскчитывает и возвращает баланс фактор*/
int ClientTree::bFactor(node* p)
{
	/*Работает при корректных высотах потомков*/
	return get_height(p->right) - get_height(p->left);
}

/*Обновляет высоту узла*/
void ClientTree::height_upd(node* p)
{
	/*работает с корректными высотами потомков*/
	if (p)
	{
		int h_1 = get_height(p->left);
		int h_2 = get_height(p->right);

		p->height = (h_1 > h_2) ? h_1 + 1 : h_2 + 1;
	}
}

/*поиск минимального элемента, начиная с переданного узла*/
node* ClientTree::find_min(node*& curNode)
{
	return curNode->left ? find_min(curNode->left) : curNode;
}
/*Изымание минимального элемента из дерева без его удаления из памяти*/
node* ClientTree::remove_min(node*& value)
{
	/*У минимального элемента из потомков может быть только 1 правый или не быть совсем*/
	/*Нашли минимальный*/
	if (!value->left)
		return value->right;
	value->left = remove_min(value->left);
	return balance(value);

}
/*Удаление элемента из дерева*/
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
//	/*Рекурсивный поиск*/
//	/*В лево поддерево*/
//	if (value < root->data)
//		root->left = remove(root->left, value);
//	/*В правое поддерево*/
//	else if (value > root->data)
//		root->right = remove(root->right, value);
//	else //Нашли элемент
//	{
//		/*Сохраняем потомков*/
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
//	/*Выполняем баллансировку узла перед выходом из рекурсии*/
//	return balance(root);
//
//}

/*поиск по водительскому удостовеению*/
node* ClientTree::findBy_licNum(node* curRoot, const string value, int* err)
{
	node* res(nullptr), * temp(nullptr);
	/*err- порядковый номер ошибки*/
	if (!this->root)
	{
		*err = 1002;//не нашлось узла
		return nullptr;
	}
	if (!isCorrect_licenseNum(value))
	{
		*err = 1003; //Некорректна  строка для поиска
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
		/*Если нашли подходящий узел- возвращем его и сохраняем в переменную*/
		if (value == curRoot->data.licenseNum)
			return curRoot;
	}
	/*продолжаем перемещать найденый узел через всю глубину рекурсии*/
	return res;
}
/*Поиск по номеру паспорта*/
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
		/*Если нашли подходящий узел- возвращем его и сохраняем в переменную*/
		if (value == curRoot->data.passportID)
			return curRoot;
		/*продолжаем перемещать найденый узел через всю глубину рекурсии*/
	}
	return res;
}
/*Поиск по ФИО*/
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

/*Проверка на правильность записи номера водительского удостоверения*/
bool ClientTree::isCorrect_licenseNum(string str)
{/*фромат записи licenseNum: RR AA NNNNNN*/
/*RR- код региона (цифры); */
/*AA – серия (буквы из следующего множества:
	А, В, Е, К, М, Н, О, Р, С, Т, У, Х);*/
	/*NNNNNN – порядковый номер удостоверения (цифры).*/

	/*Разрешённые символы*/
	const string allowedCheracters = "АВЕКМНОРСТУХ-";
	if (str.length() != 10)
		return false;
	if (!isdigit(str[0]) || !isdigit(str[1]))
		return false;
	if (int(allowedCheracters.find(str[2])) == -1
		|| int(allowedCheracters.find(str[3])) == -1)
		return false;
	/*проверка наличия только разрешённых символов*/
	for (int i(4); i < str.length(); i++)
		if (!isdigit(str[i]))
			return false;
	return true;
}
/*Проверка на правильность номера паспорта*/
bool ClientTree::isCorrect_passportID(string num, int* err)
{/*10 цифр без пробелов*/
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

/*Вывод дерева на экран*/
void ClientTree::display_tree(node* R, int l) {
	if (R)
	{
		display_tree(R->right, l + 11);
		for (int i = 1; i <= l; i++) cout << " ";
		cout << R->data.licenseNum << endl; //выводит номера водительского удостоверения
		display_tree(R->left, l + 11);
	}
}
void ClientTree::display_ui()
{
	if(root)	display_tree(this->root);
	else		cout << errorName(1001) << endl;
}
/*Вывод клиента, при поиске по водительскому удостоверению.*/
RentalListNode* ClientTree::display_elem_wCar(node elem)
{
	RentalListNode* foundElem(nullptr);
	string regNum(""); //номер авто.

	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "Номер воительского удостоверения:\t" << elem.data.licenseNum << endl
		<< "ФИО:\t\t\t\t" << elem.data.fullName << endl
		<< "Адрес проживания:\t\t" << elem.data.adress<< endl;

	foundElem = listOfRent->findBy_licNum(elem.data.licenseNum);

	return foundElem;


	

}
/*вывод ВТОРОЙ ЧАСТИ ДЛЯ ПОИСКА В ТАБЛИЦЕ*/
void ClientTree::display_treeScnd(RentalListNode* l)
{
	node* client(nullptr);
	int err;
	if (l)
	{
		/*ищем арендателя в дереве*/
		client = findBy_licNum(root, l->clientLicenseNum, &err);
		/*его нет (а аренда, связанная с ним есть => ошибка)*/
		if (!client)
		{
			cout << errorName(1007) << endl;
			exit(1);
		}
		cout << "Арендатель:" << endl
			<< "\tФИО:\t\t" << client->data.fullName << endl
			<< "\tНомер водительского удостоверения:\t" << client->data.licenseNum << endl;
	}
	else
		cout << errorName(1109) << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}

/*Вывод клиента, при поиске по марке.*/
void ClientTree::display_elem(node elem)
{

	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "Номер воительского удостоверения:\t" << elem.data.licenseNum << endl
		<< "ФИО:\t\t\t\t\t" << elem.data.fullName << endl
		<< "Адрес проживания:\t\t\t" << elem.data.adress << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}
/*Вывод списка клиентов, при поиске по ФИО.*/
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

/*Есть ли элементы в дереве*/
bool ClientTree::isEmpty()
{
	return (root) ? false : true;
}

/*Ввод информации о новом клиенте*/
node::DATA ClientTree::createForm(bool* returnToMenu)
{
	node::DATA person;
	node* tempP(nullptr);
	int errorKey(0); // код ошибки для вывода внутри этой ф-ции.
	short int choice; //номер пункта, выбранного пользователем в ситуации выбора.
	lopos variants;
	*returnToMenu = false;

	/*ФИО*/
	while (!*returnToMenu)
	{
		cout << askName(1001) << ' ';
		getline(cin, person.fullName, '\n');
		/*Запросили выход*/
		if (person.fullName == "0")
		{
			*returnToMenu = true;
			cout << warningName(9901) << endl;
		}
		/*Введи ФИО*/
		else
		{
			if (!isNameCorrect(person.fullName, &errorKey))
			{
				cout << errorName(errorKey) << "\nПовторите ввод!\n\n";
				continue;
			}
			cout << endl;
		}
		break;
	}
	/*Водительское удостоверение*/
	while (!*returnToMenu)
	{
		cout << warningName(1001) << endl
			<< askName(1002) << ' ';
		getline(cin, person.licenseNum, '\n');
		/*Запросил выход*/
		if (person.licenseNum == "0")
		{
			variants.emplace_back("Д", ", чтобы выйти в меню");
			variants.emplace_back("Н", ", чтобы продолжить ввод");
			choice = chooseDoing(warningName(9903), variants);
			variants.clear();   //очистка списка вариантов

			if (!choice) //Решил выйти в меню.
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
		/*Ввели номер водит. удостов.*/
		else
		{
			if (!isCorrect_licenseNum(person.licenseNum))
			{
				cout << errorName(1302) << "\nПовторите ввод.\n\n";
				continue;
			}
			/*Проверка на уникальность*/
			if (this->findBy_licNum(this->root, person.licenseNum, &errorKey))
			{
				cout << errorName(1004) << "\nПовторите ввод.\n\n";
				continue;
			}
		}
		break;
	}
	/*номер паспорта*/
	while (!*returnToMenu)
	{
		cout << warningName(1002) << endl
			<< askName(1003) << ' ';
		getline(cin, person.passportID, '\n');
		/*Запросил выход*/
		if (person.passportID == "0")
		{
			variants.emplace_back("Д", ", чтобы выйти в меню");
			variants.emplace_back("Н", ", чтобы продолжить ввод");
			choice = chooseDoing(warningName(9903), variants);
			variants.clear();   //очистка списка вариантов

			if (!choice) //Решил выйти в меню.
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
		/*Ввели номер паспорта*/
		else
		{
			if (!isCorrect_passportID(person.passportID, &errorKey))
			{
				cout << errorName(errorKey) << "\nПовторите ввод.\n\n";
				continue;
			}
			else
			{
				/*Проверка на уникальность*/
				if (this->findBy_passportID(this->root, person.passportID, &errorKey))
				{
					cout << errorName(1005) << "\nПовторите ввод.\n\n";
					continue;
				}
			}
		}
		break;
	}
	/*Адрес проживания*/
	while (!*returnToMenu)
	{
		cout << askName(1004) << ' ';
		getline(cin, person.adress, '\n');
		/*Запросил выход*/
		if (person.adress == "0")
		{
			variants.emplace_back("Д", ", чтобы выйти в меню");
			variants.emplace_back("Н", ", чтобы продолжить ввод");
			choice = chooseDoing(warningName(9903), variants);
			variants.clear();   //очистка списка вариантов

			if (!choice) //Решил выйти в меню.
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

/*Работа с пользователем для регистрации клиента компании*/
void ClientTree::add_ui()
{
	bool returnTMenu(false);
	node::DATA newPerson = createForm(&returnTMenu);
	if (!returnTMenu)
	{
		add(this->root, newPerson);
		cout << "Регистрация клиента прошла успешно." << endl;
	}
}

/*Работа с пользователем для удаления пользователя*/
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
		/*Запросили выход*/
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
							cout << "Удаление прошло успешно." << endl;
						else
							cout << "Не нашлось элемента для удаления." << endl;
					}
				}
				else
					cout << "Не нашлось элемента для удаления." << endl;
			}
			else
				cout << "Удаление не было произведено" << endl;
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
		variants.emplace_back("Д", "- Удалить");
		variants.emplace_back("Н", "- Отмена");
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
				cout << "Все клиенты были успешно удалены.\n";
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
