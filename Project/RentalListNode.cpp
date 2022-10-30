#include "RentalListNode.h"

RentalListNode::RentalListNode(string inCLN,
	string inSRN,
	string inD_i,
	string inD_r, 
	RentalListNode* newPNext)
{/*при создании объекта rentaList в _Node ещё нечего загружать,
   поэтому значениями по умолчанию избавляюсь от мусора.*/
	this->stateRegNum = inSRN;
	this->clientLicenseNum = inCLN;
	this->date_issue = inD_i;
	this->date_return = inD_r;
	this->pNext = newPNext;
}


RentalListNode RentalListNode::operator =  (const RentalListNode rightOperand)
{
	/*RentalListNode helpOperator;

	helpOperator.stateRegNum = rightOperand.stateRegNum;
	helpOperator.clientLicenseNum = rightOperand.clientLicenseNum;
	helpOperator.date_issue = rightOperand.date_issue;
	helpOperator.date_return = rightOperand.date_return;

	return helpOperator;*/

	this->stateRegNum = rightOperand.stateRegNum;
	this->clientLicenseNum = rightOperand.clientLicenseNum;
	this->date_issue = rightOperand.date_issue;
	this->date_return = rightOperand.date_return;

	return *this;
}
bool RentalListNode::operator >  (RentalListNode rightOperand)
{
	/*Посимвольное сравнение кодов*/
	for (int i(0); i < this->stateRegNum.length(); i++)
	{
		if (this->stateRegNum[i] > rightOperand.stateRegNum[i])
			return true;
		if (this->stateRegNum[i] < rightOperand.stateRegNum[i])
			return false;
	}

	return false;
}
bool RentalListNode::operator <  (RentalListNode rightOperand)
{
	/*Посимвольное сравнение кодов*/
	for (int i(0); i < this->stateRegNum.length(); i++)
	{
		if (this->stateRegNum[i] < rightOperand.stateRegNum[i])
			return true;
		if (this->stateRegNum[i] > rightOperand.stateRegNum[i])
			return false;
	}

	return false;
}
bool RentalListNode::operator == (RentalListNode rightOperand)
{
	/*Посимвольное сравнение кодов*/
	for (int i(0); i < this->stateRegNum.length(); i++)
	{
		if (this->stateRegNum[i] != rightOperand.stateRegNum[i])
			return false;
	}

	return true;
}
bool RentalListNode::operator != (RentalListNode rightOperand)
{
	/*Посимвольное сравнение кодов*/
	for (int i(0); i < this->stateRegNum.length(); i++)
	{
		if (this->stateRegNum[i] != rightOperand.stateRegNum[i])
			return true;
	}

	return false;
}
bool RentalListNode::operator >= (RentalListNode rightOperand)
{
	if (*this > rightOperand ||
		*this == rightOperand)
		return true;
	else
		return false;
}
bool RentalListNode::operator <= (RentalListNode rightOperand)
{
	if (*this < rightOperand ||
		*this == rightOperand)
		return true;
	else
		return false;
}
