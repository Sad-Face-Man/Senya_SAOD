#include "RentalList.h"



RentalList::RentalList()
{/*t, ct- хэш таблица и список, с которыми работает список*/
	this->head = nullptr;
	this->_size = 0;
}
RentalList::~RentalList()
{
	RentalListNode* viewPtr(head), * helpPtr(nullptr);
	/*разбиваем линейную связь*/
	if (head)
	{
		while (viewPtr->pNext != head)
			viewPtr = viewPtr->pNext;
		viewPtr->pNext = nullptr;
	}
	viewPtr = head;
	while (viewPtr)
	{
		helpPtr = viewPtr;
		viewPtr = viewPtr->pNext;
		delete helpPtr;
		helpPtr = nullptr;
	}
}

///*Меняет местами данные в объектах*/
//void RentalList::swap(RentalListNode*& p1, RentalListNode*& p2)
//{
//	RentalListNode* tempP;
//	tempP = p2;
//	p2 = p1;
//	p1 = tempP;
//}

void RentalList::swap(RentalListNode* p1, RentalListNode* p2)
{
	RentalListNode hNode;

	hNode = *p1;
	*p1 = *p2;
	*p2 = hNode;
}



///*быстрая ортировка*/
//void RentalList::quicksort(int* mas, int first, int last, int* comp, int* perm)
//{           //first, last- индексы первого и последнего элменета сортировки.
//			//comp, perm- кол-во сравнений и перестановок.
//	//*comp = *perm = 0; //зануляю счётчики
//	int mid, count; //mid-средний по значению элемент, count- вспомогательная переменная.
//	int l = first, r = last;
//	mid = min(max(mas[l], mas[r]), mas[(l + r) / 2]); //средний из первого, последнего и среднего по положению элемнетов. 
//	*comp += 2; //т.к. для нахождения среднего значения требуется 2 сравнения элементов.
//	do
//	{ /*ищем элементы, подходящие для перестановки местами*/
//		// >= среднему- вправо, <= среднему- влево (= повторяется, т.к. l и r смотрят независимо друг от друга).
//		while (mas[l] < mid)
//		{
//			l++;
//			(*comp)++; //сравнение
//		}
//		while (mas[r] > mid)
//		{
//			r--;
//			(*comp)++; //сравнение
//		}
//		//(*comp)++;
//		if (l <= r) //если не l и r не прошли мимо друг друга, то производим замену.
//		{
//			//(*comp)++;
//			count = mas[l];
//			mas[l] = mas[r];
//			mas[r] = count;
//			(*perm)++; //произошла перестановка.
//			/*отходим от переставленных элементов*/
//			l++;
//			r--;
//		}
//		//else
//
//	} while (l < r); //пока l и r в своих половинках (не прошли друг друга).
//	/*если не прошли весь массив.*/
//	if (first < r)  //сортируем левую часть.
//	{
//		//(*comp)++;
//		quicksort(mas, first, r, comp, perm);
//	}
//	if (l < last)   //сортируем правую часть.
//	{
//		//(*comp)++;
//		quicksort(mas, l, last, comp, perm);
//	}
//}
/*Сортировка списка методом Хоара*/
void RentalList::sort(int first, int last)
//сортировка по возрастанию
{           //first, last- индексы первого и последнего элменета сортировки.
	RentalListNode* mid = new RentalListNode, * hv = new RentalListNode;//средний по значению элемент, hv- вспомогательное значение
	RentalListNode* tmpMin, * tmpMax;
	int l = first, r = last; //левые и правые вспомог. индексы
	/*среднее по значению*/
	tmpMax = (*this->operator[](l) > *this->operator[](r)) ? this->operator[](l) : this->operator[](r);
	mid = (*tmpMax < *this->operator[]((l + r) / 2)) ? tmpMax : this->operator[]((l + r) / 2);
	do
	{ /*ищем элементы, подходящие для перестановки местами*/
		// >= среднему- вправо, <= среднему- влево (= повторяется, т.к. l и r смотрят независимо друг от друга).
		while (*this->operator[](l) < *mid)
		{
			l++;
		}
		while (*this->operator[](r) > *mid)
		{
			r--;
		}
		if (l <= r) //если не l и r не прошли мимо друг друга, то производим замену.
		{
			///*RentalListNode* p_1, * p_2;
			//p_1 = this->operator[](l);
			//p_2 = this->operator[](r);
			//hv = this->operator[](r);*/
			//*hv = *this->operator[](l);
			//*this->operator[](l) = *this->operator[](r);
			//*this->operator[](r) = *hv;
			///*отходим от переставленных элементов*/

			swap(this->operator[](l), this->operator[](r));
			l++;
			r--;

		}

	} while (l < r); //пока l и r в своих половинках (не прошли друг друга).
	/*если не прошли весь список.*/
	if (first < r)  //сортируем левую часть.
		sort(first, r);
	if (l < last)   //сортируем правую часть.
		sort(l, last);
}

/*добавление элемента списка в начало*/
bool RentalList::emplace_front(string inCLN
								, string inSRN
								, string inD_i
								, string inD_r)
{/*добавление только в начало, т.к. это быстрее, при учёте, что
	после каждого добавления будет производиться сортировка списка (по заданию).*/

	/*Машина с таким номером не зарегистрирована*/
	
	/*Клинент с таким вод. удостоверением не зарегистрирован.*/
	
	/*добавляем первый элемент в список*/
	if (!head)
	{
		head = new RentalListNode(inCLN, inSRN, inD_i, inD_r);
		head->pNext = head; //замыкаем на себя.
	}
	else
	{
		RentalListNode* newNode = new RentalListNode(inCLN, inSRN, inD_i, inD_r, head);

		/*поиск последнего элемента списка для зациклилвания*/
		RentalListNode* lastNode(head);
		while (lastNode->pNext != head)
		{
			lastNode = lastNode->pNext;
		}
		lastNode->pNext = newNode;
		head = newNode;
	}
	/*заполняем поля данными*/
	head->clientLicenseNum = inCLN;
	head->stateRegNum = inSRN;
	head->date_issue = inD_i;
	head->date_return = inD_r;

	this->_size++;

	
	return true;
}

/*удаляет элемент списка по указателю*/
bool RentalList::remove(RentalListNode*& elem)
{
	RentalListNode* viewPtr(nullptr),* helpPtr(nullptr);
	if (elem)
	{
		/*удаляем голову*/
		if (elem == head)
		{
			if (head->pNext)
			{
				/*перенаправляем последний элемент на второй*/
				viewPtr = head;
				while (viewPtr->pNext != head)
				{
					viewPtr = viewPtr->pNext;
				}
				viewPtr->pNext = head->pNext;
				delete elem;
				elem = nullptr;
				head = viewPtr->pNext;
			}
			else
			{
				delete head;
				head = nullptr;
			}
			_size--;
			return true;
		}
		else /*Удаляем хвостовой элемент*/
			if (elem->pNext == head)
			{
				viewPtr = head;
				while (viewPtr->pNext != elem)
					viewPtr = viewPtr->pNext;
				viewPtr->pNext = elem->pNext;
				delete elem;
				elem = nullptr;
				_size--;
				return true;
			}
		/*середнинный элемент*/
			else
			{
				viewPtr = head;
				while (viewPtr->pNext != elem)
					viewPtr = viewPtr->pNext;
				viewPtr->pNext = elem->pNext;
				delete elem;
				elem = nullptr;
				_size--;
			}
	}
	return false;
}


/*Вывод информации об анкете на экран.*/
void RentalList::out()
{
	for (int i(0); i < _size; i++)
	{
		cout << (*this)[i]->stateRegNum << " ";
	}
	cout << endl;
}

/*Поиск по номеру водит. удостоверения*/
RentalListNode* RentalList::findBy_licNum(string value)
{
	if (head)
	{
		RentalListNode* viewPtr = this->head;
		do
		{
			if (value == viewPtr->clientLicenseNum)
				return viewPtr;
			viewPtr = viewPtr->pNext;
		} while (viewPtr != this->head);
	}
	return nullptr;
}
/*Поиск по номеру водит. удостоверения*/
RentalListNode* RentalList::findBy_regNum(string value)
{
	if (head)
	{
		RentalListNode* viewPtr = this->head;
		do
		{
			if (value == viewPtr->stateRegNum)
				return viewPtr;
			viewPtr = viewPtr->pNext;
		} while (viewPtr != this->head);
	}
	return nullptr;
}

/*Возвращает элемент списка по его порядковому номеру*/
RentalListNode* RentalList::operator[](int index)
{
	int curIndex(0);
	RentalListNode* curNode(head);
	if (curNode)
	{
		do
		{
			if (curIndex == index)
				return curNode;
			curNode = curNode->pNext;
			curIndex++;
		} while (curNode != head);
	}
	/*Были пройдены все элементы => элемент по номеру не найден*/
	return nullptr;
}

/**/
void RentalList::display_elem(RentalListNode* p)
{
	cout << "\t|" << setw(15) << p->clientLicenseNum << setw(2) << " |" << setw(12) << p->stateRegNum << setw(2) << " |" << setw(15) << p->date_issue << setw(2) << " |" << setw(15) << p->date_return << setw(2) << " |" << endl;

	cout << "\t+----------------+-------------+----------------+----------------+" << endl;
}
/*Вывод шапки таблицы*/
void RentalList::display_firstLine()
{
	cout << "\t+----------------+-------------+----------------+----------------+" << endl;
	cout << "\t|" << setw(2) << ' ' << "Удостоверение" << setw(1) << " |" << setw(12) << "Номер авто" << setw(2) << " |" << setw(15) << "Дата выдачи" << setw(2) << " |" << setw(15) << "Дата возврата" << setw(2) << " |" << endl;
	cout << "\t+----------------+-------------+----------------+----------------+" << endl;
}
/*Вывод всего списка*/
void RentalList::display_all()
{
	RentalListNode* viewPtr(this->head);

	if (!viewPtr)
		cout << errorName(1205) << endl;
	else
	{
		display_firstLine();
		do
		{
			display_elem(viewPtr);
			viewPtr = viewPtr->pNext;
		} while (viewPtr != this->head);
	}
}

