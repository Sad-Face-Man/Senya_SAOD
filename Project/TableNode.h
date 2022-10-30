#pragma once

#include "Includes.h"

/*Элемент тхеш-такблицы хранящий информацию об автомобиле.*/
struct TableNode
{
	string car_number; //  «ANNNAA-NN» где A – буква из следующего множества: А,В,Е,К,М,Н,О,Р,С,Т,У,Х; N - цифры
	string brand; // Марка машины
	string color; // Цвет машины
	int yearOfManufacture; // год выпуска
	bool status = true; //признак наличия автомобиля
	bool repair = false;
	bool deleted = false;

	TableNode();
	TableNode(string refNum,
		string brand,
		string color,
		int yOfManafact,
		bool stat= true,
		bool del= false);
	void clear();
};

