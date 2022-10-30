#include "TableNode.h"

TableNode::TableNode()
{
	car_number.clear();
	brand.clear();
	yearOfManufacture = -1;
	color.clear();
	status = false;
	repair = false;
	deleted = false;
}

TableNode::TableNode(string cN,
	string b,
	string c,
	int y,
	bool s,
	bool d)
{
	car_number = cN;
	brand = b;
	color = c;
	yearOfManufacture = y;
	status = s;
	repair = false;
	deleted = d;
}
/*Очистка полей структуры*/
void TableNode::clear()
{
	this->car_number.clear();
	this->brand.clear();
	this->color.clear();
	this->yearOfManufacture = -1;
	this->status = false;
	this->repair = false;
	this->deleted = false;
}