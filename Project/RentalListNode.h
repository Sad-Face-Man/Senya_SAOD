#pragma once

#include "Includes.h"

/*stateRegNum- ���. ���. ���. ����.
������: ANNNAA-NN�, ��� N ������; A � ����� �� ���������� ���������:
�, �, �, �, �, �, �, �, �, �, �, �;*/

/*������� ������ rentalList*/
struct RentalListNode
{
	RentalListNode(string = "",
				string = "",
				string = "",
				string = "",
				RentalListNode* = nullptr);
	/*stateRegNum ��������� � ����� ��������� ��� ����
	clientLicenseNum ��������� � ����� ��������� �������.*/
	string stateRegNum;	//���. ���. �����
	string clientLicenseNum;
	string date_issue;	//���� ������ ����.
	string date_return;	//���� �������� ����.

	RentalListNode* pNext;

	RentalListNode operator =  (const RentalListNode);
	bool operator >  (const RentalListNode);
	bool operator <  (const RentalListNode);
	bool operator == (const RentalListNode);
	bool operator != (const RentalListNode);
	bool operator >= (const RentalListNode);
	bool operator <= (const RentalListNode);
};

