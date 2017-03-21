/*
* Title: Quiz01
* Description: Quiz01 on-site kelas Data Structure
* Date: 4-March-2016
* Author: William Chanrico
*/

#include <stdio.h>
#include "ItemList.cpp"

ItemList itemList1;

void clear(){
	for(int a = 0 ; a < 25; a++)
		printf("\n");
}

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

int showMenu(){
	int choice;

	clear();

	itemList1.printList();

	printf(" -= Menu =-\n");
	printf(" ----------\n");
	printf(" 1. Insert\n");
	printf(" 2. Delete\n");
	printf(" 3. Exit\n");

	do{
		printf(" >> ");

		scanf("%d", &choice);

		fflush();
	}while(choice < 1 || choice > 3);

	return choice;
}

int main(){
	int inputMenu;

	do{
		int inputPrice;
		char inputName[30];
		char inputCode[10];

		inputMenu = showMenu();

		switch(inputMenu){
		case 1:
			clear();

			printf(" -= Input =-\n");
			printf(" Code : ");

			fgets(inputCode, sizeof(inputCode), stdin);

			inputCode[strlen(inputCode) - 1] = '\0';

			printf(" Name : ");

			fgets(inputName, sizeof(inputName), stdin);

			inputName[strlen(inputName) - 1] = '\0';

			printf(" Price : ");

			scanf("%d", &inputPrice);

			fflush();

			itemList1.push_back(inputCode, inputName, inputPrice);

			break;
		case 2:
			itemList1.pop_back();

			break;
		}
	}while(inputMenu != 3);
}