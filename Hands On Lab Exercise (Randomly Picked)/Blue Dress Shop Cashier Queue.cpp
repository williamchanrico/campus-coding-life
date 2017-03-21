/*
* Title: Soal Hands On Lab - Blue Dress Shop
* Description: Soal dari HOL kelas lab
* Date: 
* Author: William Chanrico
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10

struct Data{
	char name[25];
	char dress[25];
	int price = -1;
} customer[10];

int total = 0;
int head = 0;
int tail = 0;
int curr = 0;

void fflush(){
	int c;

	while( (c = getchar()) != EOF && c != '\n');
}

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void showMenu(){
	printf(" BLUE DRESS SHOP CASHIER QUEUE\n");
	printf(" #############################\n\n");
	printf(" 1. View Queue\n");
	printf(" 2. Add Customer to Queue\n");
	printf(" 3. Serve Customer\n");
	printf(" 4. Exit\n\n");
	printf(">> Input choice : ");
}

int push(char name[], char dress[], int price){
	if(customer[head].price == -1){
		strcpy(customer[head].name, name);
		strcpy(customer[tail].name, name);
		strcpy(customer[head].dress, dress);
		strcpy(customer[tail].dress, dress);
		customer[head].price = customer[tail].price = price;
	}else if((tail + 1) % SIZE != head){
		tail = ++tail % SIZE;

		strcpy(customer[tail].name, name);
		strcpy(customer[tail].dress, dress);
		customer[tail].price = price;
	}else{
		return 0;
	}

	total++;

	return 1;
}

void serveCustomer(){
	if(customer[head].price != -1){
		printf("\n --- [ %s ] has been served ---\n", customer[head].name);

		customer[head].price = -1;

		head = ++head % SIZE;

		total--;
	}else{
		printf("\n --- There are no customers in queue ---\n");
	}

	getchar();
}

void viewQueue(){
	clear();

	printf("                 --- QUEUE VIEW ---\n\n");
	printf(" -------+----------------------+----------------------+--------\n");
	printf(" | No.  | Customer's Name      | Dress Name           | Price |\n");
	printf(" -------+----------------------+----------------------+--------\n");

	curr = (total > 0 ? head - 1 : tail);

	int counter = 1;

	while(curr != tail){
		curr = ++curr % SIZE;		

		printf(" | %3d. | %-20s | %-20s | $%4d |\n", counter++, customer[curr].name, customer[curr].dress, customer[curr].price);
	}

	printf(" -------+----------------------+----------------------+--------\n");

	getchar();
}

void addCustomer(){
	char name[25];
	char dress[25];
	int price;
	int valid;

	if(total == SIZE){
		printf("\n --- Maximum customers in queue is %d ---\n", SIZE);
		return;
	}

	do{
		valid = 1;

		printf(" Input customer's name [3..20][Must be in alphabets]: ");

		fgets(name, sizeof(name), stdin);

		name[strlen(name) - 1] = '\0';

		if(strlen(name) < 3 || strlen(name) > 20){
			valid = 0;
		}else{
			for(int a=0, len=strlen(name);a<len;a++){
				if(name[a] != ' ' && !isalpha(name[a])){
					valid = 0;
					break;
				}
			}
		}
	}while(!valid);

	do{
		printf(" Input dress' name [3..20] : ");

		fgets(dress, sizeof(dress), stdin);

		dress[strlen(dress) - 1] = '\0';
	}while(strlen(dress) < 3 || strlen(dress) > 20);

	do{
		printf(" Input dress' price [$50..$999] : ");

		valid = scanf("%d", &price);

		if(getchar() != '\n'){
			valid = 0;
			continue;
		}

		if(price < 50 || price > 999)
			valid = 0;

	}while(!valid);

	push(name, dress, price);

	printf("\n --- Success adding customer into queue list ---\n");

	getchar();
}

int main(){
	int choice;

	do{
		clear();

		showMenu();

		scanf("%d", &choice);

		fflush();

		switch(choice){
		case 1:
			viewQueue();

			break;
		case 2:
			addCustomer();

			break;
		case 3:
			serveCustomer();

			break;
		}
	}while(choice != 4);
}