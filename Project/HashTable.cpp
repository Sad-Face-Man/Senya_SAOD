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


/*Перевод ключа в число*/
int HashTable::keyTo_int(string key) {
	/*Сумма кодов символов (символ "-" не считается)*/
	int res(0);
	/*Складываем номера символов*/
	/*До симола "-"*/
	for (int i(0); i < 7; i++)
		res += (int)key[i];
	/*после символа "-"*/
	res += (int)key[7] + (int)key[8];
	return res;
}
///*Первая хеш-функция*/
//int HashTable::hash_1(string key_char) {
//	long index = 0;
//	for (int i = 0; i < m1; i++) {
//		index += (int)key_char[i] * (int)key_char[i];
//	}
//	index %= _size;
//	return index;
//}
/*Первая хеш-функция*/
int HashTable::hash_1(string key)
{
	long index = 0;
	for (int i(0); i < key.length(); i++)
	{
		index += key[i] * pow(PRIME, i);
	}
	return index;
}
/*Вторая хеш-функция*/
int HashTable::hash_2(string key_char) 	// вторая хеш-ф-ция
{
	int key = keyTo_int(key_char);
	return (PRIME - (key % PRIME));
}

/*Добавить элемент в хеш-таблицу*/
bool HashTable::add(TableNode car) {
	int index1, index2, newIndex;
	index1 = hash_1(car.car_number);
	index2 = hash_2(car.car_number);
	for (int i = 0; i < tour; i++) {
		newIndex = (index1 + i * index2) % _size;
		/*нашли элемент*/
		if ((table[newIndex].car_number == "\0") || (table[newIndex].deleted)) {
			table[newIndex] = car;
			return true;
		}
	}
	return false;
	/*resize();
	return add(key);*/
}

/*Проверяет строку на соответствие норме рег. номера авто.*/
bool HashTable::isStateRegNumCorrect(string str)
{/*ANNNAA-NN*/
	const string allowedCheracters = "АВЕКМНОРСТУХ"; //разреш. символы
	const int m = 9; //длина ключа
	if (str.length() != m)
		return false;
	/*Проверка на буквы*/
	if (int(allowedCheracters.find(str[0])) == -1
		|| int(allowedCheracters.find(str[4])) == -1
		|| int(allowedCheracters.find(str[5])) == -1
		|| str[6] != '-')
		return false;
	/*проверка на числа*/
	for (int i(1); i < 3; i++)
		if (!isdigit(str[i]))
			return false;
	if (!isdigit(str[7])
		|| !isdigit(str[8]))
		return false;

	return true;
}

/*Поиск элемента по ключу*/
short HashTable::findBy_regNum(string k) {
	int index1, index2, newIndex;
	index1 = hash_1(k);
	index2 = hash_2(k);
	/*проходим таблицу tour раз*/
	for (unsigned long i(0); i < _size * tour; i++) {
		newIndex = (index1 + i * index2) % _size;
		/*пустая клетка- элемнета нет*/
		if (table[newIndex].car_number == "\0")
			return -1;
		/*метака удаления- идём дальше*/
		if (table[newIndex].deleted)
			continue;
		/*нашли элемент- возвращаем*/
		if (table[newIndex].car_number == k)
			return newIndex;
	}
	/*прошли всё и не нашли*/
	return -1;
}
/*Поиск элемента по ключу*/
TableNode HashTable::findBy_regNum_elem(string k) {
	TableNode emptyNode;
	int index1, index2, newIndex;
	index1 = hash_1(k);
	index2 = hash_2(k);
	/*проходим таблицу tour раз*/
	for (unsigned long i(0); i < _size * tour; i++) {
		newIndex = (index1 + i * index2) % _size;
		/*пустая клетка- элемнета нет*/
		if (table[newIndex].car_number == "\0")
			return emptyNode;
		/*метака удаления- идём дальше*/
		if (table[newIndex].deleted)
			continue;
		/*нашли элемент- возвращаем*/
		if (table[newIndex].car_number == k)
			return table[newIndex];
	}
	/*прошли всё и не нашли*/
	return emptyNode;
}
list<TableNode>* HashTable::findBy_brand(string k)
{
	list<TableNode>* result = new list<TableNode>;
	result->clear();
	/*Проходим таблицу*/
	for (int i(0); i < _size; i++)
		if (table[i].car_number != "\0")
			if (findInText(table[i].brand, k) != -1)
				result->emplace_back(table[i]);

	return result;
}

/*Удаление элемента из таблицы*/
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

/*Вывести таблицу на экран*/
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
/*Вывод элемента*/
void HashTable::display_elem(TableNode elem)
{
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "Номер:\t" << elem.car_number << endl
		<< "Марка: \t" << elem.brand << endl
		<< "Цвет:\t" << elem.color << endl
		<< "В ремонте: " << ((elem.repair) ? "Да" : "Нет") << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}
/*Вывод одного авто, при поиске по рег. номеру*/
RentalListNode*  HashTable::display(TableNode elem)
{/*Возвращает номер вод. удостов. ждя дальнейшей обработки*/
	RentalListNode* foundElem(nullptr);
	string licensNum(""); //номер водит. ужостов. арендателя
	int err(0);

	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
	cout << "Номер:\t" << elem.car_number << endl
		<< "Марка: \t" << elem.brand << endl
		<< "Цвет:\t" << elem.color << endl
		<< "В ремонте: " << ((elem.repair) ? "Да" : "Нет") << endl;
	foundElem = listOfRent->findBy_regNum(elem.car_number);

	return foundElem;
}
/*вывод ВТОРОЙ ЧАСТИ ДЛЯ ПОИСДЕРЕВЕ*/
void HashTable::display_hashScnd(RentalListNode* l)
{
	TableNode car;
	if (l)
	{
		/*ищем арендателя в дереве*/
		car = findBy_regNum_elem(l->stateRegNum);
		/*его нет*/
		if (car.car_number == "\0")
		{
			cout << errorName(1007) << endl;
			exit(1);
		}
		cout << "Аренда:" << endl
			<< "\tРег. номер авто.:\t\t" << car.car_number << endl;
	}
	else
		cout << errorName(1008) << endl;
	cout << setfill('-') << setw(120) << '-' << setfill(' ') << endl;
}
/*Поиск по марке авто*/
void HashTable::display(list<TableNode> lst)
{
	/*вывод шапки*/
	/*вывод элемнетов списка в форме таблицы*/
	list<TableNode>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++)
	{
		display_elem(*it);
		cout << endl;
	}

}

/*Очищает таблицу*/
void HashTable::clear()
{
	TableNode* a = new TableNode;
	if (table)
		for (int i(0); i < _size; i++)
			if(!listOfRent->findBy_regNum(table[i].car_number))
				table[i].clear();
}
/*ПРоверяет, находятся ли элементы в таблице*/
bool HashTable::isEmpty()
{
	for (int i(0); i < _size; i++)
		if (table[i].car_number != "\0")
			return false;
	return true;
}
/*Увеличивает размер хэш-таблицы в 2 раза
и переносит данные в расширенную таблицу.*/
void HashTable::resize()
{
	int prevSize(_size);
	_size *= 2;
	TableNode* newTable = new TableNode[_size];
	//void swap(table, newTable);

	/*переносим данные из старой таблицы в новую*/
	for (int i(0); i < prevSize; i++)
	{
		if (newTable[i].car_number != "\0")
			add(newTable[i]);
	}
}

/*Ввод данных для регистрации авто*/
TableNode HashTable::createForm(bool* returnToMenu)
{
	TableNode newCar;
	int errorKey(0); // код ошибки для вывода внутри этой ф-ции.
	short int choice; //номер пункта, выбранного пользователем в ситуации выбора.
	lopos variants;
	/*Для получения текущего года*/
	time_t seconds = time(nullptr);
	tm* timeInfo = localtime(&seconds);
	unsigned int curYear(1900 + timeInfo->tm_year);
	*returnToMenu = false;

	/*Ввод регистрационного номера.
	номер- УНИКАЛЬНЫЙ*/
	while (!*returnToMenu)
	{
		cout << warningName(1101) << endl
			<< askName(1101) << ' ';
		getline(cin, newCar.car_number, '\n');
		/*Запросили выход*/
		if (newCar.car_number == "0")
		{
			*returnToMenu = true;
			cout << warningName(9901) << endl;
		}
		/*Был введён номер.*/
		else
		{
			if (!isStateRegNumCorrect(newCar.car_number))
			{
				cout << errorName(1103) << "\nПовторите ввод!\n\n";
				continue;
			}
			/*Проверка на уникальность*/
			if (this->findBy_regNum(newCar.car_number) != -1)
			{
				cout << errorName(1104) << "\nПовторите ввод.\n\n";
				continue;
			}
			cout << endl;
			break;
		}

	}
	/*Ввод марки.*/
	while (!*returnToMenu)
	{
		cout << askName(1102) << ' ';
		getline(cin, newCar.brand, '\n');
		/*Запросили выход*/
		if (newCar.brand == "0")
		{
			/*Варианты для выбора*/
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
		/*Была введена марка.*/
		else
		{
			if (!isStrCorrect(newCar.brand, &errorKey))
			{
				cout << errorName(errorKey) << "\nПовторите ввод!\n\n";
				continue;
			}
			cout << endl;
			break;
		}
	}
	/*Ввод цвета.*/
	while (!*returnToMenu)
	{
		cout << askName(1103) << ' ';
		getline(cin, newCar.color, '\n');
		/*Запросили выход*/
		if (newCar.color == "0")
		{
			/*Варианты для выбора*/
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
		/*Был введён номер.*/
		else
		{
			if (!isStrCorrect(newCar.color, &errorKey))
			{
				cout << errorName(errorKey) << "\nПовторите ввод!\n\n";
				continue;
			}
			cout << endl;
			break;
		}
	}
	/*Ввод года выпуска.*/
	while (!*returnToMenu)
	{
		newCar.yearOfManufacture = inputAndCheck_int(askName(1104));
		if (newCar.yearOfManufacture == 0)
		{
			/*Варианты для выбора*/
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
		/*Был введён год производства*/
		else
		{
			/*Если год производства <0 или если больше текущего года.*/
			if (newCar.yearOfManufacture < 0
				|| newCar.yearOfManufacture > curYear)
			{
				cout << errorName(1306) << "\nПовторите ввод!\n\n";
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

/*Рабта с пользователем для регистрации авто*/
void HashTable::add_ui(bool* returnToMenu)
{
	TableNode car;
	*returnToMenu = false;

	car = createForm(returnToMenu);
	if (!*returnToMenu)
		if (this->add(car))
			cout << "Регистрация авто прошла успешно\n\n";
		else
			cout << "База данных переполнена: не удалось добавить маршрут.\n\n";
}
/*Работа с пользователем для удалении авто с площадки*/
void HashTable::del_ui()
{
	lopos variants;
	short choice, index;
	string numTDel("\0"); //Номер авто для удаления.

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
				/*сейчас арендует*/
				if (listOfRent->findBy_regNum(numTDel))
				{
					cout << errorName(1206) << endl;
					return;
				}
				cout << warningName(1102) << endl;
				display(table[index]);
				cout << endl;
				variants.emplace_back("У", ", чтобы подтвердить удаление");
				variants.emplace_back("О", ", для отмены");
				choice = chooseDoing(askName(1107), variants);
				if (!choice)
				{
					if (this->del(numTDel))
						cout << "Автомобиль успешно удалён.";
					else
						cout << "Ошибка удаления.";
					cout << endl;
				}
				else
				{
					cout << warningName(9901) << endl;
				}
			}
			else
				cout << errorName(1102) << "\n\n"; //такого авто нет в таблице				
		}
		else
			cout << errorName(1103) << endl;
	}
}

/*Работа с пользователем для очистки таблицы*/
void HashTable::clear_ui()
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
				this->clear();
				cout << "Все автомобили были успешно удалены.\n";
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

/*сеттер поля repair*/
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
/*отправить авто в ремонт*/
void HashTable::repair_login_ui(RentalList* r)
{
	TableNode* helpPtr(nullptr);
	int index(0);
	string value("");

	cout << askName(1108) << ' ';
	getline(cin, value, '\n');
	
	/*Корректное лизначение рег.  номера*/
	if (isStateRegNumCorrect(value))
	{
		/*такой автомобиль не зарегистрирован*/
		if ((index = findBy_regNum(value)) == -1)
			cout << errorName(1105) << endl;
		else
		{
			/*Авто сейчас арендуют*/
			if (r->findBy_regNum(value))
				cout << errorName(1204) << endl;
			/*авто уже в ремонте*/
			else if (this->table[index].repair)
				cout << errorName(1107) << endl;
			else
			{
				this->table[index].repair = true;
				cout << "\nАвтомобиль отправлен в ремонт.\n\n";
			}
		}
	}
	else //некорректный ввод
		cout << errorName(1302) << endl;
}
/*Забрать авто из ремонта*/
void HashTable::repair_logout_ui(RentalList* r)
{
	TableNode* helpPtr(nullptr);
	int index(0);
	string value("");

	cout << askName(1109) << ' ';
	getline(cin, value, '\n');

	/*Корректное лизначение рег.  номера*/
	if (isStateRegNumCorrect(value))
	{
		/*такой автомобиль не зарегистрирован*/
		if ((index = findBy_regNum(value)) == -1)
			cout << errorName(1105) << endl;
		else
		{
			/*авто и так не в ремонте*/
			if (!this->table[index].repair)
				cout << errorName(1108) << endl;
			else
			{
				this->table[index].repair = false;
				cout << "\nАвтомобиль вернулся из ремонта.\n\n";
			}
		}
	}
	else //некорректный ввод
		cout << errorName(1302) << endl;
}


