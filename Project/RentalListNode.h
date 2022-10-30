#pragma once

#include "Includes.h"

/*stateRegNum- гос. рег. ном. авто.
Формат: ANNNAA-NN», где N –цифра; A – буква из следующего множества:
А, В, Е, К, М, Н, О, Р, С, Т, У, Х;*/

/*Элемент списка rentalList*/
struct RentalListNode
{
	RentalListNode(string = "",
				string = "",
				string = "",
				string = "",
				RentalListNode* = nullptr);
	/*stateRegNum совпадает с полем структуры для авто
	clientLicenseNum совпадает с полем структуры клиента.*/
	string stateRegNum;	//гос. рег. номер
	string clientLicenseNum;
	string date_issue;	//дата выдачи авто.
	string date_return;	//дата возврата авто.

	RentalListNode* pNext;

	RentalListNode operator =  (const RentalListNode);
	bool operator >  (const RentalListNode);
	bool operator <  (const RentalListNode);
	bool operator == (const RentalListNode);
	bool operator != (const RentalListNode);
	bool operator >= (const RentalListNode);
	bool operator <= (const RentalListNode);
};

