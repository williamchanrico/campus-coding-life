/*
* Title: Soal Hands On Lab - Blue Computer Administrator
* Description: Soal dari HOL kelas lab
* Date: 
* Author: William Chanrico
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data{
	char name[51];
	char type[21];
	int qty;
	int price;
	struct data *next;
} *head = NULL, *tail = NULL, *curr = NULL;

void fflush(){
	int c;

	while( (c = getchar()) != EOF && c != '\n');
}

void push(char name[], char type[], int qty, int price){
	struct data *temp = (struct data*) malloc(sizeof(struct data));
	
	strcpy(temp->name, name);
	strcpy(temp->type, type);
	temp->qty = qty;
	temp->price = price;

	if(head == NULL){
		head = tail = temp;
	}else{
		tail->next = temp;
		tail = temp;
	}

	tail->next = NULL;
}

void pop(char name[]){
	curr = head;

	while(curr != NULL && strcmp(curr->name, name) != 0){
		curr = curr->next;
	}

	if(curr == head){
		head = head->next;

		free(curr);

		printf(" Item deleted successfuly...\n");
	}else if(head != curr && tail != curr){
		struct data *temp;

		temp = head;

		while(temp->next != curr){
			temp = temp->next;
		}

		temp->next = curr->next;

		free(curr);

		printf(" Item deleted successfuly...\n");
	}else if(curr == tail){
		printf(" The last item cannot be deleted...\n");
	}
}

void view(){
	printf("            --- ITEM LIST ---\n\n");
	for(int a = 0; a < 68; a++)
		printf("=");

	printf("\n");

	printf("| %-3s. | %-20s | %-15s | %-8s | %-4s |\n", "No.", "Name", "Type", "Quantity", "Price");
	
	for(int a = 0; a < 68; a++)
		printf("=");

	printf("\n");

	curr = head;

	int idx = 0;

	while(curr){
		idx++;

		printf("| %3d. | %-20s | %-15s | %8d | $%4d |\n", idx, curr->name, curr->type, curr->qty, curr->price);
		
		curr = curr->next;
	}

	for(int a = 0; a < 68; a++)
		printf("=");

	printf("\n");
	
	getchar();
}

void popall(){
	while(head != NULL){
		curr = head;
		head = head->next;

		free(curr);
	}
}

void showMenu(){
	printf("\n BLUE COMPUTER ADMINISTRATOR");
	printf("\n +++++++++++++++++++++++++++");
	printf("\n 1. Item List");
	printf("\n 2. Add (PUSH) New Item");
	printf("\n 3. Delete (POP) Item");
	printf("\n 4. Exit");
	printf("\n >> Input your choice : ");
}

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

int main(){
	char name[51];
	char type[21];
	int qty;
	int price;
	int choice;

	while(true){
		clear();

		showMenu();

		scanf("%d", &choice);

		fflush();

		switch(choice){
		case 1:
			view();

			break;
		case 2:
			do{
				printf(" Input name of the new item [3..20]: ");

				fgets(name, sizeof(name), stdin);

				name[strlen(name) - 1] = '\0';

			}while(strlen(name) < 3 || strlen(name) > 20);

			printf("\n");

			do{
				printf(" Input type of the new item [processor/graphic card/memory]: ");

				fgets(type, sizeof(type), stdin);

				type[strlen(type) - 1] = '\0';
			}while(strcmp(type, "processor") != 0 && strcmp(type, "graphic card") != 0 && strcmp(type, "memory") != 0);
			
			printf("\n");
			
			do{
				printf(" Input quantity of the new item [1..20]: ");

				scanf("%d", &qty);

				fflush();
			}while(qty < 1 || qty > 20);
			
			do{
				printf(" Input price of the new item [$1..$1000]: ");

				scanf("%d", &price);

				fflush();
			}while(price < 1 || price > 10000);

			push(name, type, qty, price);

			printf("\n\n\n --- Add new item success ---\n");

			getchar();

			break;
		case 3:
			if(head == NULL){
				printf(" List is empty.. ");
			}else{
				do{
					printf(" Input name of the item [3..20]: ");

					fgets(name, sizeof(name), stdin);

					name[strlen(name) - 1] = '\0';
				}while(strlen(name) < 1 || strlen(name) > 20);

				pop(name);
			}

			getchar();

			break;
		case 4:
			popall();

			return 0;

			break;
		}
	}
}


