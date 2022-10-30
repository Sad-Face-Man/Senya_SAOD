#include "RentalList.h"



RentalList::RentalList()
{/*t, ct- ��� ������� � ������, � �������� �������� ������*/
	this->head = nullptr;
	this->_size = 0;
}
RentalList::~RentalList()
{
	RentalListNode* viewPtr(head), * helpPtr(nullptr);
	/*��������� �������� �����*/
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

///*������ ������� ������ � ��������*/
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



///*������� ���������*/
//void RentalList::quicksort(int* mas, int first, int last, int* comp, int* perm)
//{           //first, last- ������� ������� � ���������� �������� ����������.
//			//comp, perm- ���-�� ��������� � ������������.
//	//*comp = *perm = 0; //������� ��������
//	int mid, count; //mid-������� �� �������� �������, count- ��������������� ����������.
//	int l = first, r = last;
//	mid = min(max(mas[l], mas[r]), mas[(l + r) / 2]); //������� �� �������, ���������� � �������� �� ��������� ���������. 
//	*comp += 2; //�.�. ��� ���������� �������� �������� ��������� 2 ��������� ���������.
//	do
//	{ /*���� ��������, ���������� ��� ������������ �������*/
//		// >= ��������- ������, <= ��������- ����� (= �����������, �.�. l � r ������� ���������� ���� �� �����).
//		while (mas[l] < mid)
//		{
//			l++;
//			(*comp)++; //���������
//		}
//		while (mas[r] > mid)
//		{
//			r--;
//			(*comp)++; //���������
//		}
//		//(*comp)++;
//		if (l <= r) //���� �� l � r �� ������ ���� ���� �����, �� ���������� ������.
//		{
//			//(*comp)++;
//			count = mas[l];
//			mas[l] = mas[r];
//			mas[r] = count;
//			(*perm)++; //��������� ������������.
//			/*������� �� �������������� ���������*/
//			l++;
//			r--;
//		}
//		//else
//
//	} while (l < r); //���� l � r � ����� ���������� (�� ������ ���� �����).
//	/*���� �� ������ ���� ������.*/
//	if (first < r)  //��������� ����� �����.
//	{
//		//(*comp)++;
//		quicksort(mas, first, r, comp, perm);
//	}
//	if (l < last)   //��������� ������ �����.
//	{
//		//(*comp)++;
//		quicksort(mas, l, last, comp, perm);
//	}
//}
/*���������� ������ ������� �����*/
void RentalList::sort(int first, int last)
//���������� �� �����������
{           //first, last- ������� ������� � ���������� �������� ����������.
	RentalListNode* mid = new RentalListNode, * hv = new RentalListNode;//������� �� �������� �������, hv- ��������������� ��������
	RentalListNode* tmpMin, * tmpMax;
	int l = first, r = last; //����� � ������ �������. �������
	/*������� �� ��������*/
	tmpMax = (*this->operator[](l) > *this->operator[](r)) ? this->operator[](l) : this->operator[](r);
	mid = (*tmpMax < *this->operator[]((l + r) / 2)) ? tmpMax : this->operator[]((l + r) / 2);
	do
	{ /*���� ��������, ���������� ��� ������������ �������*/
		// >= ��������- ������, <= ��������- ����� (= �����������, �.�. l � r ������� ���������� ���� �� �����).
		while (*this->operator[](l) < *mid)
		{
			l++;
		}
		while (*this->operator[](r) > *mid)
		{
			r--;
		}
		if (l <= r) //���� �� l � r �� ������ ���� ���� �����, �� ���������� ������.
		{
			///*RentalListNode* p_1, * p_2;
			//p_1 = this->operator[](l);
			//p_2 = this->operator[](r);
			//hv = this->operator[](r);*/
			//*hv = *this->operator[](l);
			//*this->operator[](l) = *this->operator[](r);
			//*this->operator[](r) = *hv;
			///*������� �� �������������� ���������*/

			swap(this->operator[](l), this->operator[](r));
			l++;
			r--;

		}

	} while (l < r); //���� l � r � ����� ���������� (�� ������ ���� �����).
	/*���� �� ������ ���� ������.*/
	if (first < r)  //��������� ����� �����.
		sort(first, r);
	if (l < last)   //��������� ������ �����.
		sort(l, last);
}

/*���������� �������� ������ � ������*/
bool RentalList::emplace_front(string inCLN
								, string inSRN
								, string inD_i
								, string inD_r)
{/*���������� ������ � ������, �.�. ��� �������, ��� �����, ���
	����� ������� ���������� ����� ������������� ���������� ������ (�� �������).*/

	/*������ � ����� ������� �� ����������������*/
	
	/*������� � ����� ���. �������������� �� ���������������.*/
	
	/*��������� ������ ������� � ������*/
	if (!head)
	{
		head = new RentalListNode(inCLN, inSRN, inD_i, inD_r);
		head->pNext = head; //�������� �� ����.
	}
	else
	{
		RentalListNode* newNode = new RentalListNode(inCLN, inSRN, inD_i, inD_r, head);

		/*����� ���������� �������� ������ ��� �������������*/
		RentalListNode* lastNode(head);
		while (lastNode->pNext != head)
		{
			lastNode = lastNode->pNext;
		}
		lastNode->pNext = newNode;
		head = newNode;
	}
	/*��������� ���� �������*/
	head->clientLicenseNum = inCLN;
	head->stateRegNum = inSRN;
	head->date_issue = inD_i;
	head->date_return = inD_r;

	this->_size++;

	
	return true;
}

/*������� ������� ������ �� ���������*/
bool RentalList::remove(RentalListNode*& elem)
{
	RentalListNode* viewPtr(nullptr),* helpPtr(nullptr);
	if (elem)
	{
		/*������� ������*/
		if (elem == head)
		{
			if (head->pNext)
			{
				/*�������������� ��������� ������� �� ������*/
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
		else /*������� ��������� �������*/
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
		/*����������� �������*/
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


/*����� ���������� �� ������ �� �����.*/
void RentalList::out()
{
	for (int i(0); i < _size; i++)
	{
		cout << (*this)[i]->stateRegNum << " ";
	}
	cout << endl;
}

/*����� �� ������ �����. �������������*/
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
/*����� �� ������ �����. �������������*/
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

/*���������� ������� ������ �� ��� ����������� ������*/
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
	/*���� �������� ��� �������� => ������� �� ������ �� ������*/
	return nullptr;
}

/**/
void RentalList::display_elem(RentalListNode* p)
{
	cout << "\t|" << setw(15) << p->clientLicenseNum << setw(2) << " |" << setw(12) << p->stateRegNum << setw(2) << " |" << setw(15) << p->date_issue << setw(2) << " |" << setw(15) << p->date_return << setw(2) << " |" << endl;

	cout << "\t+----------------+-------------+----------------+----------------+" << endl;
}
/*����� ����� �������*/
void RentalList::display_firstLine()
{
	cout << "\t+----------------+-------------+----------------+----------------+" << endl;
	cout << "\t|" << setw(2) << ' ' << "�������������" << setw(1) << " |" << setw(12) << "����� ����" << setw(2) << " |" << setw(15) << "���� ������" << setw(2) << " |" << setw(15) << "���� ��������" << setw(2) << " |" << endl;
	cout << "\t+----------------+-------------+----------------+----------------+" << endl;
}
/*����� ����� ������*/
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

