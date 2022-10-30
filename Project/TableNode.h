#pragma once

#include "Includes.h"

/*������� ����-�������� �������� ���������� �� ����������.*/
struct TableNode
{
	string car_number; //  �ANNNAA-NN� ��� A � ����� �� ���������� ���������: �,�,�,�,�,�,�,�,�,�,�,�; N - �����
	string brand; // ����� ������
	string color; // ���� ������
	int yearOfManufacture; // ��� �������
	bool status = true; //������� ������� ����������
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

