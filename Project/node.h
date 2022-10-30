#pragma once

#include "Includes.h"

// �������� ���������� ������������������ ����
const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

/*��������� ��� �������� ���������� � ������� ���� ������� (���� ��� ������)*/
struct node
{
	/*������ ������ licenseNum: RR AA NNNNNN*/
/*RR- ��� ������� (�����); */
/*AA � ����� (����� �� ���������� ���������:
	�, �, �, �, �, �, �, �, �, �, �, �);*/
	/*NNNNNN � ���������� ����� ������������� (�����).*/
	struct DATA
	{
		string licenseNum;	// ����� ������������� �������������.
		string fullName;	// ���.
		string passportID;  // ����� ��������.
		string adress;		// ����� ����������.
			/*��������� ���������*/
			bool operator >  (const DATA);
		bool operator <  (const DATA);
		bool operator >= (const DATA);
		bool operator <= (const DATA);
		bool operator == (const DATA);
		bool operator != (const DATA);

		void clear();
	};
	DATA data; //�������� ������� ��� ������� � ������ �������

	node(node::DATA,
		node* l = nullptr,
		node* r = nullptr,
		int h = 0);

	node(string licenseNum = "",
		string fullName = "",
		string passportID = "",
		string adress = "",
		node* left = nullptr,
		node* right = nullptr,
		//int height,
		int height = 1);
private:
	/*��������� �� ������ � ������� ������� ��� ������*/
	node* left;
	node* right;
	/*balance- ������ ������� ��������� ����� ������ ������ ���������.*/
	//int height;
	int height;

	/*����� ������ ������ ����� ������ �� ���� ����� ����*/
	friend class ClientTree;
};

