#include "node.h"

node::node(node::DATA value,
	node* l,
	node* r,
	int h)
{
	this->data = value;
	left = l;
	right = r;
	height = h;
}
node::node(string lic,
	string fName,
	string pass,
	string adr,
	node* l,
	node* r,
	int h)
{
	/*Значащие поля*/
	data.licenseNum = lic;
	data.fullName = fName;
	data.passportID = pass;
	data.adress = adr;
	/*указатели на потомков*/
	left = l;
	right = r;
	/*баланс фактор*/
	height = 0;
}

bool node::DATA::operator >  (const DATA r)
{
	return (this->licenseNum > r.licenseNum) ? true : false;
}
bool node::DATA::operator <  (const DATA r)
{
	return (this->licenseNum < r.licenseNum) ? true : false;
}
bool node::DATA::operator >= (const DATA r)
{
	if (this->licenseNum > r.licenseNum ||
		this->licenseNum == r.licenseNum)
		return true;
	return false;
}
bool node::DATA::operator <= (const DATA r)
{
	if (this->licenseNum < r.licenseNum ||
		this->licenseNum == r.licenseNum)
		return true;
	return false;
}
bool node::DATA::operator == (const DATA r)
{
	return (this->licenseNum == r.licenseNum) ? true : false;
}
bool node::DATA::operator != (const DATA r)
{
	return (this->licenseNum != r.licenseNum) ? true : false;
}

void node::DATA::clear()
{
	this->licenseNum.clear();
	this->fullName.clear();
	this->passportID.clear();
	this->adress.clear();
}