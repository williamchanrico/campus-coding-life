/*
* Title: Soal Hands On Lab - Blue Cake Shop
* Description: Soal dari HOL kelas lab
* Date: 
* Author: William Chanrico
*/

#include <stdio.h>
#include <string.h>

struct cake{
	int no;
	int available;
	int price;
	char code[20];
	char name[20];
};

cake BlueCake[4];

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void fflush(){
	int c;

	while( (c = getchar()) != EOF && c != '\n');
}

int choose(){
	int inp;

	do{
		printf("Input choice : ");

		scanf("%d", &inp);

		fflush();
	}while(!(inp >= 1 && inp <= 3));

	return inp;
}

int find(char x[]){
	for(int a = 0; a < 4; a++)
		if(strcmp(x, BlueCake[a].code) == 0)
			return a;
	return -1;
}


void sell(){
	char code[20];
	int quantity;
	int cakeIdx;

	do{
		printf("Input Cake Code [5 chars]: ");

		scanf("%s", code);

		fflush();

		cakeIdx = find(code);

		if(cakeIdx == -1)
			printf("---The Cake Code doesn't exist---\n");
	}while(cakeIdx == -1);

	do{
		printf("Input Quantity [0..%d]: ", BlueCake[cakeIdx].available);

		scanf("%d", &quantity);

		fflush();

		if(quantity > BlueCake[cakeIdx].available)
			printf("...The quantity of cake is not enough...\n");
	}while(!(quantity >= 0 && quantity <= BlueCake[cakeIdx].available));

	printf("Total Price is: Rp %d,- x %d = Rp %d,-\n", BlueCake[cakeIdx].price, quantity, BlueCake[cakeIdx].price * quantity);
	
	BlueCake[cakeIdx].available -= quantity;
	
	getchar();
}

void addStock(){
	char code[20];
	int quantity;
	int cakeIdx;

	do{
		printf("Input Cake Code [5 chars]: ");

		scanf("%s", code);

		fflush();

		cakeIdx = find(code);

		if(cakeIdx == -1)
			printf("---The Cake Code doesn't exist---\n");
	}while(cakeIdx == -1);

	do{
		printf("Input Quantity [1..10]: ");

		scanf("%d", &quantity);

		fflush();
		
		if(!(quantity >= 1 && quantity <= 10))
			printf("...The quantity of cake must range from 1 to 10...\n");

	}while(!(quantity >= 1 && quantity <= 10));

	BlueCake[cakeIdx].available += quantity;

	printf("---Adding Stock Success---\n");

	getchar();
}

int main(){
	int inp;

	BlueCake[0].no = 1;
	strcpy(BlueCake[0].code, "CK001");
	strcpy(BlueCake[0].name, "Blueberry Cake");
	BlueCake[0].available = 13;
	BlueCake[0].price = 25000;

	BlueCake[1].no = 2;
	strcpy(BlueCake[1].code, "CK009");
	strcpy(BlueCake[1].name, "Chocochip Cake");
	BlueCake[1].available = 5;
	BlueCake[1].price = 20000;

	BlueCake[2].no = 3;
	strcpy(BlueCake[2].code, "CK017");
	strcpy(BlueCake[2].name, "Mayonaise Cake");
	BlueCake[2].available = 24;
	BlueCake[2].price = 30000;

	BlueCake[3].no = 4;
	strcpy(BlueCake[3].code, "CK023");
	strcpy(BlueCake[3].name, "Strawberry ShortCake");
	BlueCake[3].available = 7;
	BlueCake[3].price = 17500;

	do{
		clear();

		printf("BLUE CAKE SHOP CASHIER\n");
		printf("======================\n\n");
		printf("No. | Cake Code | Cake Name            | Available | Price     \n");
		printf("---------------------------------------------------------------\n");
		printf("%02d. | %-9s | %-20s | %9d | Rp.%6d.-\n", BlueCake[0].no, BlueCake[0].code, BlueCake[0].name, BlueCake[0].available, BlueCake[0].price);
		printf("%02d. | %-9s | %-20s | %9d | Rp.%6d.-\n", BlueCake[1].no, BlueCake[1].code, BlueCake[1].name, BlueCake[1].available, BlueCake[1].price);
		printf("%02d. | %-9s | %-20s | %9d | Rp.%6d.-\n", BlueCake[2].no, BlueCake[2].code, BlueCake[2].name, BlueCake[2].available, BlueCake[2].price);
		printf("%02d. | %-9s | %-20s | %9d | Rp.%6d.-\n", BlueCake[3].no, BlueCake[3].code, BlueCake[3].name, BlueCake[3].available, BlueCake[3].price);
		printf("---------------------------------------------------------------\n\n\n");

		printf("Menu :\n");
		printf("1. Sell\n");
		printf("2. Add Stock\n");
		printf("3. Exit\n");

		inp = choose();

		switch(inp){
		case 1:
			sell();
			break;
		case 2:
			addStock();
			break;
		}
	}while(inp != 3);
}