#pragma once

#include "Includes.h"

// Значения показателя сбалансированности узла
const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

/*структура для хранения информации о клиенте бюро проката (узел АВЛ дерева)*/
struct node
{
	/*фромат записи licenseNum: RR AA NNNNNN*/
/*RR- код региона (цифры); */
/*AA – серия (буквы из следующего множества:
	А, В, Е, К, М, Н, О, Р, С, Т, У, Х);*/
	/*NNNNNN – порядковый номер удостоверения (цифры).*/
	struct DATA
	{
		string licenseNum;	// Номер водительского удостоверения.
		string fullName;	// ФИО.
		string passportID;  // Номер паспорта.
		string adress;		// Адрес проживания.
			/*Операторы сравнения*/
			bool operator >  (const DATA);
		bool operator <  (const DATA);
		bool operator >= (const DATA);
		bool operator <= (const DATA);
		bool operator == (const DATA);
		bool operator != (const DATA);

		void clear();
	};
	DATA data; //Открытый элемент для доступа к данным клиента

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
	/*Указатели на левого и правого потомка АВЛ дерева*/
	node* left;
	node* right;
	/*balance- высота правого поддерева минус высота левого поддерева.*/
	//int height;
	int height;

	/*Класс дерева должен иметь доступ ко всем полям узла*/
	friend class ClientTree;
};

