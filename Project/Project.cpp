/*Программу выполняет студент СПб ГУАП, Поздеев Арсений Андреевич, гр. 4032.
Вариант по методичке:
8.1 Предметная область:  1, Обслуживание клиентов в бюро проката автомобилей
8.2 Метод хеширования:	 3, Закрытое хеширование с двойным хешированием
8.3 Метод сортировки:	 4, Быстрая (Хоара)
8.4 Вид списка:			 2, Циклический однонаправленный
8.5 Метод обхода дерева: 1, Обратный
8.6 Алгоритм поиска слова в тексте: 1, Прямой
*/

#include "Includes.h"
#include "RentalList.h"
#include "ClientTree.h"
#include "HashTable.h"




/*Функция для работы с пользовтелем для аренды авто.*/
void rentCar_start(HashTable* tab, ClientTree* tree, RentalList* rental)
{
	/*Переменные для хранения введённый идентификаторов*/
	string inLicNum(""), inRegNum(""), date_start(""), date_end("");
	bool returnToMenu(false);
	int err(0), choice(0);
	lopos variants;

	if (!tab->isEmpty() && !tree->isEmpty())
	{
		cout << "ОФОРМЛЕНИЕ АРЕНДЫ АВТО.\n\n";
		/*Ввод номера вод. удостоверения арендателя.*/
		while (!returnToMenu)
		{
			cout << warningName(1001) << endl
				<< askName(1201) << ' ';
			getline(cin, inLicNum, '\n');
			/*Запросил выход*/
			if (inLicNum == "0")
			{
				returnToMenu = true;
				cout << warningName(9901) << "\n\n";
			}
			/*Ввели номер водит. удостов.*/
			else
			{
				if (tree->isCorrect_licenseNum(inLicNum))
				{
					/*Проверка на наличие*/
					/*Пользователь не зарегистрирован*/
					if (!tree->findBy_licNum(tree->_get_root(), inLicNum, &err))
					{
						cout << errorName(1002) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
					/*У пользователя уже есть авто*/
					if (rental->findBy_licNum(inLicNum))
					{
						cout << errorName(1201) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
				}
				else
				{
					cout << errorName(1302) << endl
						<< "Повторите ввод!" << endl;
					continue;
				}
				break;
			}
		}
		/*Ввод рег. номера арендуемой машины.*/
		while (!returnToMenu)
		{
			cout << warningName(1101) << endl
				<< askName(1202) << ' ';
			getline(cin, inRegNum, '\n');
			/*Запросил выход*/
			if (inRegNum == "0")
			{
				variants.emplace_back("Д", ", чтобы выйти в меню");
				variants.emplace_back("Н", ", чтобы продолжить ввод");
				choice = chooseDoing(warningName(9903), variants);
				variants.clear();   //очистка списка вариантов

				if (!choice) //Решил выйти в меню.
				{
					returnToMenu = true;
					cout << warningName(9901) << "\n\n";
				}
				else
				{
					returnToMenu = false;
					cout << warningName(9902) << endl << endl;
					continue;
				}
			}
			/*Ввели рег. номер авто.*/
			else
			{
				if (tab->isStateRegNumCorrect(inRegNum))
				{
					/*Проверка на наличие*/
					/*авто не зарегистрировано*/
					if (tab->findBy_regNum(inRegNum) == -1)
					{
						cout << errorName(1102) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
					/*Авто уже арендуется*/
					if (rental->findBy_regNum(inRegNum))
					{
						cout << errorName(1106) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
					/*Авто в ремонте*/
					if (tab->findBy_regNum_elem(inRegNum).repair)
					{
						cout << errorName(1203) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
				}
				else
				{
					/*неверный ввод*/
					cout << errorName(1302) << endl
						<< "Повторите ввод!" << endl;
					continue;
				}
				break;
			}
		}
		/*Дата начала аренды*/
		while (!returnToMenu)
		{
			cout << askName(1203) << ' ';
			getline(cin, date_start, '\n');
			/*Запросил выход*/
			if (date_start == "0")
			{
				variants.emplace_back("Д", ", чтобы выйти в меню");
				variants.emplace_back("Н", ", чтобы продолжить ввод");
				choice = chooseDoing(warningName(9903), variants);
				variants.clear();   //очистка списка вариантов

				if (!choice) //Решил выйти в меню.
				{
					returnToMenu = true;
					cout << warningName(9901) << "\n\n";
				}
				else
				{
					returnToMenu = false;
					cout << warningName(9902) << endl << endl;
					continue;
				}
			}
			/*Ввели датуначала аренды*/
			////
			break;
		}
		/*Дата начала аренды*/
		while (!returnToMenu)
		{
			cout << askName(1204) << ' ';
			getline(cin, date_end, '\n');
			/*Запросил выход*/
			if (date_end == "0")
			{
				variants.emplace_back("Д", ", чтобы выйти в меню");
				variants.emplace_back("Н", ", чтобы продолжить ввод");
				choice = chooseDoing(warningName(9903), variants);
				variants.clear();   //очистка списка вариантов

				if (!choice) //Решил выйти в меню.
				{
					returnToMenu = true;
					cout << warningName(9901) << "\n\n";
				}
				else
				{
					returnToMenu = false;
					cout << warningName(9902) << endl << endl;
					continue;
				}
			}
			/*Ввели дату окончания аренды.*/
			////
			break;
		}

		if (!returnToMenu)
		{
			rental->emplace_front(inLicNum, inRegNum, date_start, date_end);
			rental->sort(0, rental->getSize()-1);
		}
	}
	else
	cout << errorName(1202) << endl;
}
/*Функция для работы с пользовтелем для аренды авто.*/
void rentCar_end(HashTable* tab, ClientTree* tree, RentalList* rental)
{
	/*Переменные для хранения введённый идентификаторов*/
	string inLicNum(""), inRegNum("");
	bool returnToMenu(false);
	int err(0), choice(0);
	lopos variants;

	RentalListNode* foundElem(nullptr);

	if (!tab->isEmpty() && !tree->isEmpty())
	{
		cout << "ОФОРМЛЕНИЕ ВОЗВРАЩЕНИЯ АВТО ИЗ АРЕНДЫ.\n\n";
		/*Ввод номера вод. удостоверения арендателя.*/
		while (!returnToMenu)
		{
			cout << warningName(1001) << endl
				<< askName(1201) << ' ';
			getline(cin, inLicNum, '\n');
			/*Запросил выход*/
			if (inLicNum == "0")
			{
				returnToMenu = true;
				cout << warningName(9901) << "\n\n";
			}
			/*Ввели номер водит. удостов.*/
			else
			{
				if (tree->isCorrect_licenseNum(inLicNum))
				{
					/*Проверка на наличие*/
					/*Пользователь не зарегистрирован*/
					if (!tree->findBy_licNum(tree->_get_root(), inLicNum, &err))
					{
						cout << errorName(1002) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
					/*У пользователя уже есть авто*/
					if (!rental->findBy_licNum(inLicNum))
					{
						cout << "Данный пользователь не арендует авто!" << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
				}
				else
				{
					cout << errorName(1302) << endl
						<< "Повторите ввод!" << endl;
					continue;
				}
				break;
			}
		}
		/*Ввод рег. номера арендуемой машины.*/
		while (!returnToMenu)
		{
			cout << warningName(1101) << endl
				<< askName(1202) << ' ';
			getline(cin, inRegNum, '\n');
			/*Запросил выход*/
			if (inRegNum == "0")
			{
				variants.emplace_back("Д", ", чтобы выйти в меню");
				variants.emplace_back("Н", ", чтобы продолжить ввод");
				choice = chooseDoing(warningName(9903), variants);
				variants.clear();   //очистка списка вариантов

				if (!choice) //Решил выйти в меню.
				{
					returnToMenu = true;
					cout << warningName(9901) << "\n\n";
				}
				else
				{
					returnToMenu = false;
					cout << warningName(9902) << endl << endl;
					continue;
				}
			}
			/*Ввели рег. номер авто.*/
			else
			{
				if (tab->isStateRegNumCorrect(inRegNum))
				{
					/*Проверка на наличие*/
					/*Пользователь не зарегистрирован*/
					if (tab->findBy_regNum(inRegNum) == -1)
					{
						cout << "Данное авто не зарегистрировано в программе." << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
					/*авто не арендуется*/
					if (!rental->findBy_regNum(inRegNum))
					{
						cout << errorName(1106) << endl
							<< "Повторите ввод!" << endl;
						continue;
					}
				}
				else
				{
					cout << errorName(1302) << endl
						<< "Повторите ввод!" << endl;
					continue;
				}
				break;
			}
		}
		

		if (!returnToMenu)
		{
			foundElem = rental->findBy_licNum(inLicNum);

			if (foundElem && foundElem->stateRegNum == inRegNum)
			{
				rental->remove(foundElem);
				cout << "Удаление прошло успешно" << endl;
			}
			else
				cout << "Введённый польоавтель не арендовал введённый автомобиль" << endl;
		}
	}
	else
		cout << errorName(1202) << endl;
}

/*Работа с пользователем для поиска*/
void find_ui_tree(ClientTree* tree, HashTable* tab)
{
	lopos variants;
	list<node> foundList; foundList.clear();
	node* foundElem(nullptr);
	int choice(0), errorKey;
	string strTFnd = "";
	RentalListNode* elem;

	if (tree->_get_root())
	{
		variants.emplace_back("1", " для поика по номеру водительского удостоверения");
		variants.emplace_back("2", " для поика по ФИО");
		variants.emplace_back("0", " Отмена.");

		choice = chooseDoing("Выберите, по какому параметру вы хотите осуществить поиск:", variants);

		switch (choice)
		{
		case(0):
		{
			cout << askName(1002) << ' ';
			getline(cin, strTFnd, '\n');
			/*Запросили выход*/
			if (strTFnd == "0")
			{
				cout << warningName(9901) << endl;
			}
			else
			{
				if (tree->isCorrect_licenseNum(strTFnd))
				{
					foundElem = tree->findBy_licNum(tree->_get_root(), strTFnd, &errorKey);
					if (foundElem)
					{
						elem = tree->display_elem_wCar(*foundElem);
						tab->display_hashScnd(elem);
					}
					else
						cout << errorName(1002) << endl;
				}
				else
					cout << errorName(1302) << endl;
			}
			break;
		}
		case(1):
		{
			cout << askName(1001) << ' ';
			getline(cin, strTFnd, '\n');
			/*Запросили выход*/
			if (strTFnd == "0")
			{
				cout << warningName(9901) << endl;
			}
			else
			{
				tree->findBy_SN(tree->_get_root(), strTFnd, &foundList);
				if (!foundList.empty())
					tree->display_set(foundList);
				else
					cout << errorName(1002);
			}
			break;
		}
		case(2):
		{
			cout << warningName(9901) << endl;
			break;
		}
		}
	}
	else
		cout << errorName(1001) << endl;
}

/*Работа с пользователем для поиска авто*/
void find_ui_hash(HashTable* tab, ClientTree* tree)
{
	lopos variants;
	int choice(0);
	int index(0);
	string strTFnd(""); //строка со значением для поиска.
	list<TableNode>* foundList;
	TableNode elem;
	RentalListNode* rentNode;
	if (!tab->isEmpty())
	{
		variants.emplace_back("1", " для поиска по рег. номеру автомобиля.");
		variants.emplace_back("2", " для поиска по марке автомобиля.");
		variants.emplace_back("0", " для выхода в меню.");
		choice = chooseDoing("По какому параметру вы хотите найти автомобиль?", variants);
		switch (choice)
		{
		case(0):
		{
			index = 0;
			system("cls");
			cout << warningName(1101) << endl << askName(1101) << ' ';
			getline(cin, strTFnd, '\n');

			/*Запросили выход*/
			if (strTFnd == "0")
				cout << warningName(9901) << endl;
			/*Был введён номер.*/
			else
			{
				if (tab->isStateRegNumCorrect(strTFnd))
				{
					elem = tab->findBy_regNum_elem(strTFnd);
					if (elem.car_number == "\0")
						cout << errorName(1102) << endl;
					else
					{
						cout << warningName(1102) << "\n\n";
						rentNode = tab->display(elem);
						tree->display_treeScnd(rentNode);
					}
				}
				else
					cout << errorName(1103) << endl;
			}
			break;
		}
		case(1):
		{
			cout << askName(1102) << ' ';
			getline(cin, strTFnd, '\n');
			foundList = tab->findBy_brand(strTFnd);
			if (foundList->empty())
				cout << errorName(1102) << endl;
			else
			{
				cout << warningName((foundList->size() == 1) ? 1102 : 1103) << "\n\n";
				tab->display(*foundList);
			}
			delete foundList;
			break;
		}
		case(2):
		{
			cout << warningName(9901) << endl;
			break;
		}
		}
	}
	/*В программе нет авто*/
	else
		cout << errorName(1101) << "\n\n";
}

/*Основной цикл работы программы, включая меню*/
void programLoop(HashTable* tableOfAuto		//Хештаблица авто
				, ClientTree* treeOfClients	//АВЛ дереов клиентов+++
				, RentalList* listOfRent)	//Список текущих аренд.
{
	/*Переменные для временного хранеия элементов хэш-таблицы и дерева.*/
	TableNode tempCar;
	node tempClient;
	lopos variants; //варианты выбора
	int errorKey(0), choice(0); //choice- номер выборв пользователя для ф-ции chooseDoing
	int index(0);
	bool returnTMenu(false), wasExit(false); // был выход в меню и из программы.

	while (!wasExit)
	{
		/*обнуление переменных*/
		errorKey = 0;
		returnTMenu = false;
		variants.clear();

		int key(0); //Какой пункт меню выберет пользователь.
		cout << "\t***********************************\n"
			<< "\t*********БЮРО ПРОКАТА АВТО*********\n"
			<< "\t***********************************\n"
			<< "\nМеню:\n"


			<< "\t\tКЛИЕНТЫ\n"
			<< ((treeOfClients->isEmpty()) ? ("(" + errorName(1001) + ")\n") : "")	
			<< "11:\tЗарегистрировать.\n"
			<< "12:\tУдалить аккаунт.\n"
			<< "13:\tВсе клиенты.\n"
			<< "14:\tНайти.\n"
			<< "15:\tУдалить все.\n\n"

			<< "\t\tАТОМОБИЛИ\n"
			<<( (tableOfAuto->isEmpty()) ? ("(" + errorName(1101) + ")\n") : "")
			<< "21:\tЗарегистрировать.\n"
			<< "22:\tУдалить из базы.\n"
			<< "23:\tВсе автомобили.\n"
			<< "24:\tНайти.\n"
			<< "25:\tУдалить все.\n\n"

			<< "\t\tАРЕНДА\n"
			<< ((listOfRent->isEmpty()) ? ("(" + errorName(1205) + ")\n") : "")
			<< "31:\tАрендавать автомобиль.\n"
			<< "32:\tПринять атвомобиль из аренды.\n"
			<< "33:\tОтправить авто в ремонт.\n"
			<< "34:\tПринять авто из ремонта.\n"
			<< "35:\tВсе договоры аренды авто.\n\n"

			<< "0:\tВыход.\n";
		/*Запрос ввода пункта меню.*/
		key = inputAndCheck_int("номер меню");
		system("cls");
		/*Отработка выбранного алгоритма*/
		switch (key)
		{
		/*Выход из программы*/
		case(0):
		{
			variants.emplace_back("Д", "- Выход.");
			variants.emplace_back("Н", "- Отмена.");

			choice = chooseDoing(askName(1301), variants);
			variants.clear();
			cout << endl;

			if (!choice)
			{
				cout << "До свидания!" << endl << endl;
				wasExit = true;
			}
			else
			{
				cout << "Возвращение в меню..." << endl << endl;
				system("pause");
				system("cls");
			}
			break;
		}
		/*Добавить клиента*/
		case(11):
		{
			treeOfClients->add_ui();
			system("pause");
			system("cls");
			break;
		}
		/*Удалить клиента*/
		case(12):
		{
			treeOfClients->del_ui();
			system("pause");
			system("cls");
			break;
		}
		/*Вывести всех клиентов (в форме дерева)*/
		case(13):
		{
			treeOfClients->display_ui();
			system("pause");
			system("cls");
			break;
		}
		/*Найти клиента*/
		case(14):
		{
			find_ui_tree(treeOfClients, tableOfAuto);
			system("pause");
			system("cls");
			break;
		}
		/*Очистить дерево клиентов*/
		case(15):
		{
			treeOfClients->clear_ui();
			system("pause");
			system("cls");
			break;
		}
		/*Зарегистрировать авто.*/
		case(21):
		{
			returnTMenu = false;
			tableOfAuto->add_ui(&returnTMenu);
			system("pause");
			system("cls");
			break;
		}
		/*Удалить автомобиль.*/
		case(22):
		{
			tableOfAuto->del_ui();
			system("pause");
			system("cls");
			break;
		}
		/*Выводит таблицу номеров зарегистрированных авто*/
		case(23):
		{
			system("cls");
			tableOfAuto->display();
			system("pause");
			system("cls");
			break;
		}
		/*Найти автомобиль*/
		case(24):
		{
			find_ui_hash(tableOfAuto, treeOfClients);
			system("pause");
			system("cls");
			break;
		}
		/*Очистить хэш таблицу с автомобилями*/
		case(25):
		{
			tableOfAuto->clear_ui();
			system("pause");
			system("cls");
			break;
		}
		/*Арендовать автомобиль*/
		case(31):
		{
			rentCar_start(tableOfAuto, treeOfClients, listOfRent);
			system("pause");
			system("cls");
			break;
		}
		/*Возврат из аренды*/
		case(32):
		{
			rentCar_end(tableOfAuto, treeOfClients, listOfRent);
			system("pause");
			system("cls");
			break;
		}
		/*Отправить в ремонт*/
		case(33):
		{
			tableOfAuto->repair_login_ui(listOfRent);
			system("pause");
			system("cls");
			break;
		}
		/*Забрать из ремонта*/
		case(34):
		{
			tableOfAuto->repair_logout_ui(listOfRent);
			system("pause");
			system("cls");
			break;
		}
		/*Вывести список на экран*/
		case(35):
		{
			listOfRent->display_all();
			system("pause");
			system("cls");
			break;
		}
		default:
		{
			cout << errorName(1301) << "\nПовторите ввод!\n\n";
			system("pause");
			system("cls");
		}
		}
	}
}

/*Симуляция малого левого поворота*/
void slr_ex(ClientTree*& ct)
{
	cout << "МАЛЫЙ ЛЕВЫЙ ПОВОРОТ НАЧАЛО" << endl;

	ct->_dltTree(ct->root);
	node client_1("25ОР000500", "Поздеев Арсений", "0416926253", "Красноярск");
	ct->add(ct->root, client_1.data);
	node client_2("25ОР000400", "Созинова Вероника", "0416926254", "Пенза");
	ct->add(ct->root, client_2.data);
	node client_3("25ОР000600", "Ильинков Игорь Сервеевич", "0416926255", "Ижевск");
	ct->add(ct->root, client_3.data);
	node client_4("25ОР000700", "Брежнева Анастасия", "0416926256", "Киров");
	ct->add(ct->root, client_4.data);
	node client_5("25ОР000650", "Переверзев Алексей Игоревич", "5474521457", "Москва");
	ct->add(ct->root, client_5.data);
	/*вывод до возникновения ситуации разбалансировки*/
	cout << "\nДо возникновения ситуации разбалансировки:\n\n";
	ct->display_tree(ct->root);
	node client_6("25ОР000800", "Петров Александр Алексеевич", "7418529632", "Санкт-Петербург");
	ct->add(ct->root, client_6.data);

	/*дерево после поворота*/
	cout << "\nДерево после поворота:\n\n";
	ct->display_tree(ct->root);
	cout << "\nДобавился 25ОР000800\n";

	cout << "МАЛЫЙ ЛЕВЫЙ ПОВОРОТ КОНЕЦ\n\n\n";
}
/*Симуляция большого левого поворота*/
void blr_ex(ClientTree*& ct)
{
	cout << "БОЛЬШОЙ ЛЕВЫЙ ПОВОРОТ НАЧАЛО" << endl;

	ct->_dltTree(ct->root);
	node client_1("25ОР000500", "Поздеев Арсений", "0416926253", "Красноярск");
	ct->add(ct->root, client_1.data);
	node client_2("25ОР000400", "Созинова Вероника", "0416926254", "Пенза");
	ct->add(ct->root, client_2.data);
	node client_3("25ОР000600", "Ильинков Игорь Сервеевич", "0416926255", "Ижевск");
	ct->add(ct->root, client_3.data);
	node client_4("25ОР000700", "Брежнева Анастасия", "0416926256", "Киров");
	ct->add(ct->root, client_4.data);
	node client_5("25ОР000650", "Переверзев Алексей Игоревич", "5474521457", "Москва");
	ct->add(ct->root, client_5.data);
	/*вывод до возникновения ситуации разбалансировки*/
	cout << "\nДо возникновения ситуации разбалансировки:\n\n";
	ct->display_tree(ct->root);
	node client_6("25ОР000550", "Петров Александр Алексеевич", "7418529632", "Санкт-Петербург");
	ct->add(ct->root, client_6.data);

	/*дерево после поворота*/
	cout << "\nДерево после поворота:\n\n";
	ct->display_tree(ct->root);
	cout << "\nДобавился 25ОР000550\n";

	cout << "БОЛЬШОЙ ЛЕВЫЙ ПОВОРОТ КОНЕЦ\n\n\n";
}
/*Симуляция малого правого поворота*/
void srr_ex(ClientTree*& ct)
{
	cout << "МАЛЫЙ ПРАВЫЙ ПОВОРОТ НАЧАЛО" << endl;

	ct->_dltTree(ct->root);
	node client_5("25ОР000650", "Переверзев Алексей Игоревич", "5474521456", "Москва");
	ct->add(ct->root, client_5.data);
	node client_1("25ОР000500", "Поздеев Арсений", "0416926253", "Красноярск");
	ct->add(ct->root, client_1.data);
	node client_4("25ОР000700", "Брежнева Анастасия", "0416926254", "Киров");
	ct->add(ct->root, client_4.data);
	node client_2("25ОР000400", "Созинова Вероника", "0416926255", "Пенза");
	ct->add(ct->root, client_2.data);
	node client_3("25ОР000600", "Ильинков Игорь Сервеевич", "0416926256", "Ижевск");
	ct->add(ct->root, client_3.data);


	/*вывод до возникновения ситуации разбалансировки*/
	cout << "\nДо возникновения ситуации разбалансировки:\n\n";
	ct->display_tree(ct->root);
	node client_6("25ОР000300", "Петров Александр Алексеевич", "7418529632", "Санкт-Петербург");
	ct->add(ct->root, client_6.data);

	/*дерево после поворота*/
	cout << "\nДерево после поворота:\n\n";
	ct->display_tree(ct->root);
	cout << "\nДобавился 25ОР000300\n";

	cout << "МАЛЫЙ ПРАВЫЙ ПОВОРОТ КОНЕЦ\n\n\n";
}
/*Симуляция большого правого поворота*/
void brr_ex(ClientTree*& ct)
{
	cout << "БОЛЬШОЙ ПРАВЫЙ ПОВОРОТ НАЧАЛО" << endl;

	ct->_dltTree(ct->root);
	node client_5("25ОР000650", "Переверзев Алексей Игоревич", "5474521456", "Москва");
	ct->add(ct->root, client_5.data);
	node client_1("25ОР000500", "Поздеев Арсений", "0416926253", "Красноярск");
	ct->add(ct->root, client_1.data);
	node client_4("25ОР000700", "Брежнева Анастасия", "0416926254", "Киров");
	ct->add(ct->root, client_4.data);
	node client_2("25ОР000400", "Созинова Вероника", "0416926255", "Пенза");
	ct->add(ct->root, client_2.data);
	node client_3("25ОР000600", "Ильинков Игорь Сервеевич", "0416926253", "Ижевск");
	ct->add(ct->root, client_3.data);


	/*вывод до возникновения ситуации разбалансировки*/
	cout << "\nДо возникновения ситуации разбалансировки:\n\n";
	ct->display_tree(ct->root);
	node client_6("25ОР000550", "Петров Александр Алексеевич", "74185296329", "Санкт-Петербург");
	ct->add(ct->root, client_6.data);

	/*дерево после поворота*/
	cout << "\nДерево после поворота:\n\n";
	ct->display_tree(ct->root);
	cout << "\nДобавился 25ОР000550\n";

	cout << "БОЛЬШОЙ ПРАВЫЙ ПОВОРОТ КОНЕЦ\n\n\n";
}
/*Загрузка пользователей в том числе с повторяющимися ФИО*/
void equalNames_ex(ClientTree*& ct)
{
	cout << "ЗАГРУЗКА ПОЛЬЗОВАТЕЛЕЙ, В ТОМ ЧИСЛЕ С ПОВТОРЯЮЩИМИСЯ ФИО НАЧАЛО" << endl;

	ct->_dltTree(ct->root);
	node client_1("25ОР000500", "Поздеев Арсений Андреевич", "0416926253", "Красноярск");
	ct->add(ct->root, client_1.data);
	node client_2("25ОР000400", "Поздеев Арсений Андреевич", "0416926254", "Пенза");
	ct->add(ct->root, client_2.data);
	node client_3("25ОР000600", "Поздеев Арсений Андреевич", "0416926255", "Ижевск");
	ct->add(ct->root, client_3.data);
	node client_4("25ОР000700", "Поздеев Арсений Андреевич", "0416926256", "Киров");
	ct->add(ct->root, client_4.data);

	node client_5("25ОР000800", "Созинова Вероника", "4561238526", "Пенза");
	ct->add(ct->root, client_5.data);
	node client_6("25ОР000650", "Созинова Вероника", "4561238527", "Орёл");
	ct->add(ct->root, client_6.data);

	node client_7("25ОР000550", "Зверев Иван", "7898527412", "Казань");
	ct->add(ct->root, client_7.data);
	node client_8("25ОР000300", "Иванов Арсений Степанович", "7898527412", "Мариуполь");
	ct->add(ct->root, client_8.data);
	node client_9("25ОР000350", "Сидоров Антон Олегович", "7898527412", "Владивосток");
	ct->add(ct->root, client_9.data);
	node client_10("25ОР000750", "Созинова Валерия Олеговна", "7898527412", "Владивосток");
	ct->add(ct->root, client_10.data);

	ct->display_tree(ct->root);
	cout << "Одинаковые:\n";
	cout << "25ОР000500,\n 25ОР000400, - Поздеев Арсений Андреевич\n 25ОР000600,\n 25ОР000700.\n\n";
	cout << "25ОР000800, - Созинова Вероника\n 25ОР000650.\n\n";
	cout << "Также есть частичные совпадения по \"Арсений\" и \"Созинова\"\n";

	cout << "ЗАГРУЗКА ПОЛЬЗОВАТЕЛЕЙ, В ТОМ ЧИСЛЕ С ПОВТОРЯЮЩИМИСЯ ФИО ЗАВЕРШЕНА\n\n";
}
/*загрузка автомобилей*/
void cars_ex(HashTable*& t)
{
	cout << "ЗАГРУЗКА АВТОМОБИЛЕЙ НАЧАЛО\n";
	t->clear();
	TableNode car_1("А456ОР-60", "Хонда", "Зелёный", 1995);
	t->add(car_1);
	TableNode car_3("А456ОР-89", "Хонда", "Красный", 2002);
	t->add(car_3);
	TableNode car_4("А456ОР-92", "Лексус", "Чёрный", 2010);
	t->add(car_4);
	TableNode car_5("А456ОР-36", "Тойота", "Чёрный", 1999);
	t->add(car_5);
	TableNode car_6("А456ОР-90", "Хонда", "Оранжевый", 1989);
	t->add(car_6);
	TableNode car_7("А456ОР-98", "Жигули", "Зелёный", 1980);
	t->add(car_7);
	TableNode car_8("А456ОР-55", "Хонда", "Белый", 2000);
	t->add(car_8);
	TableNode car_9("А456ОР-63", "Жигули", "Зелёный", 1980);
	t->add(car_9);
	TableNode car_10("А456РО-63", "Камри", "Оранжевый", 2002);
	t->add(car_10);
	TableNode car_11("А465РО-36", "Тойота", "Красный", 2003);
	t->add(car_11);
	TableNode car_12("А645РО-36", "Тойота", "Красный", 2003);
	t->add(car_12);
	TableNode car_13("А645РО-63", "Хюндай", "Синий", 2005);
	t->add(car_13);

	t->display();
	cout << "\nКолизия(для старого варианта):\nА456ОР-36, А456ОР-63, А456РО-63, А465РО-36, А645РО-36, А645РО-63;\nА456ОР-89, А456ОР-98.\n\n";
	cout << "Для переполнения (при старом варианте) попытайтесь добавить авто с номером \"А645ОР-63\"\n";
	cout << "Есть совпадения: Хонда, Тойота, Жигули";

	cout << "ЗАГРУЗКА АВТОМОБИЛЕЙ КОНЕЦ\n\n";
}
/*Заполнение списка аренды*/
void rentList_ex(HashTable*& t, ClientTree*& ct, RentalList*& rl)
{
	cout << "ЗАПОЛНЕНИЯ СПИСКА АРЕНДЫ НАЧАЛО\n";
	t->clear();
	ct->_dltTree(ct->root);
	/*Клиенты*/
	node client_1("25ОР000500", "Поздеев Арсений Андреевич", "0416926253", "Красноярск");
	ct->add(ct->root, client_1.data);
	node client_2("25ОР000400", "Кортонов Антон", "5475824512", "Пенза");
	ct->add(ct->root, client_2.data);
	node client_3("25ОР000600", "Поздняков Владимир", "3254587412", "Ижевск");
	ct->add(ct->root, client_3.data);
	node client_4("25ОР000700", "Поздеев Игорь Андреевич", "0254523698", "Красноряск");
	ct->add(ct->root, client_4.data);
	node client_5("25ОР000800", "Созинова Вероника", "4561238526", "Пенза");
	ct->add(ct->root, client_5.data);
	node client_6("25ОР000650", "Созинова Валентина Олеговна", "4561238527", "Орёл");
	ct->add(ct->root, client_6.data);
	node client_7("25ОР000550", "Зверев Иван", "7898527412", "Казань");
	ct->add(ct->root, client_7.data);
	node client_8("25ОР000300", "Иванов Арсений Степанович", "7898527412", "Мариуполь");
	ct->add(ct->root, client_8.data);
	node client_9("25ОР000350", "Сидоров Антон Олегович", "7898527412", "Владивосток");
	ct->add(ct->root, client_9.data);
	node client_10("25ОР000750", "Созинова Валерия Олеговна", "7898527412", "Владивосток");
	ct->add(ct->root, client_10.data);
	/*Автомобили*/
	t->clear();
	TableNode car_1("А456ОР-60", "Хонда", "Зелёный", 1995);
	t->add(car_1);
	TableNode car_3("М524МН-54", "Хонда", "Красный", 2002);
	t->add(car_3);
	TableNode car_4("Е874УХ-92", "Лексус", "Чёрный", 2010);
	t->add(car_4);
	TableNode car_5("У214ХМ-32", "Тойота", "Чёрный", 1999);
	t->add(car_5);
	TableNode car_6("К856РО-23", "Хонда", "Оранжевый", 1989);
	t->add(car_6);
	TableNode car_7("Н236МУ-98", "Жигули", "Зелёный", 1980);
	t->add(car_7);
	TableNode car_8("О001ОО-11", "Хонда", "Белый", 2000);
	t->add(car_8);
	TableNode car_9("О448БУ-85", "Жигули", "Зелёный", 1980);
	t->add(car_9);
	TableNode car_10("Р255РБ-41", "Камри", "Оранжевый", 2002);
	t->add(car_10);
	TableNode car_11("Х332НВ-36", "Тойота", "Красный", 2003);
	t->add(car_11);
	TableNode car_12("В784КЕ-41", "Тойота", "Красный", 2003);
	t->add(car_12);
	TableNode car_13("А996УК-20", "Хюндай", "Синий", 2005);
	t->add(car_13);

	/*t->clear();
	TableNode car_1("Г456ОР-60", "Хонда", "Зелёный", 1995);
	t->add(car_1);
	TableNode car_3("В456ОР-60", "Хонда", "Красный", 2002);
	t->add(car_3);
	TableNode car_4("А456ОР-60", "Лексус", "Чёрный", 2010);
	t->add(car_4);
	TableNode car_5("К456ОР-60", "Тойота", "Чёрный", 1999);
	t->add(car_5);
	TableNode car_6("О456ОР-60", "Хонда", "Оранжевый", 1989);
	t->add(car_6);
	TableNode car_7("Р456ОР-60", "Жигули", "Зелёный", 1980);
	t->add(car_7);
	TableNode car_8("А456ОР-61", "Хонда", "Белый", 2000);
	t->add(car_8);
	TableNode car_9("М456ОР-60", "Жигули", "Зелёный", 1980);
	t->add(car_9);
	TableNode car_10("М456ОР-59", "Камри", "Оранжевый", 2002);
	t->add(car_10);
	TableNode car_11("О456ОР-61", "Тойота", "Красный", 2003);
	t->add(car_11);
	TableNode car_12("Р456ОР-61", "Тойота", "Красный", 2003);
	t->add(car_12);
	TableNode car_13("Н456ОР-60", "Хюндай", "Синий", 2005);
	t->add(car_13);*/

	/*Список аренды*/
	rl->emplace_front(client_1.data.licenseNum, car_1.car_number, "01.06.2022", "01.08.2022");
	rl->emplace_front(client_3.data.licenseNum, car_3.car_number, "25.05.2022", "01.06.2022");
	rl->emplace_front(client_5.data.licenseNum, car_5.car_number, "01.06.2022", "01.08.2022");
	rl->emplace_front(client_8.data.licenseNum, car_8.car_number, "23.03.2022", "13.07.2022");
	rl->emplace_front(client_10.data.licenseNum, car_10.car_number, "23.03.2022", "13.07.2022");

	cout << "\nАвто:\n";
	t->display();
	cout << "\n\nКлиенты:\n";
	ct->display_tree(ct->root);
	cout << "\n\nСписок аренды до сортировки:\n";
	rl->display_all();
	rl->sort(0, rl->getSize()-1);
	cout << "\nСписок аренды после сортировки:\n";
	rl->display_all();
	cout << endl << endl;

	cout << "Свободные клиенты:\n"
		<< client_2.data.licenseNum << ", " 
		<< client_4.data.licenseNum << ", " 
		<< client_6.data.licenseNum << ", " 
		<< client_7.data.licenseNum << ", " 
		<< client_9.data.licenseNum << "\n\n";
	cout << "Свободные авто:\n"
		<< car_4.car_number << ", "
		<< car_6.car_number << ", "
		<< car_7.car_number << ", "
		<< car_9.car_number << ", "
		<< car_11.car_number << ", "
		<< car_12.car_number << ", "
		<< car_13.car_number << "\n\n";


	cout << "ЗАПОЛНЕНИЯ СПИСКА АРЕНДЫ КОНЕЦ\n\n";
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	RentalList* rl = new RentalList;
	HashTable* t = new HashTable(rl);
	ClientTree* ct = new ClientTree(rl);
	
	
	/*===========ТЕСТОВЫЕ ДАННЫЕ===========*/
	/*ПОВОРОТЫ*/
	//slr_ex(ct); //малый левый поворот
	//blr_ex(ct); //большой левый поворот
	//srr_ex(ct); //малый правый поворот
	//brr_ex(ct); //большой правый поворот

	/*ЗАГРУЗКА ДАННЫХ*/
	equalNames_ex(ct); //Регистрация клиентов + совпадение ФИО
	//cars_ex(t); //Регистрация авто.
	//rentList_ex(t, ct, rl); // Список аренды

	/*===========ОСНОВНОЙ ХОД РАБОТЫ ПРОГРАММЫ===========*/
	programLoop(t, ct, rl);

	delete t, ct, rl;

	return 0;
}