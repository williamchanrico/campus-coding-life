#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
	char code[10];
	int price;
	char name[30];

	struct Node *next;
} Item;

typedef struct List{
	Item *head = NULL;
	Item *tail = NULL;
	Item *curr = NULL;

	void push_back(char* code, char *name, int price){
		Item *newNode = (Item *) malloc(sizeof(Item));

		newNode->price = price;
		strcpy(newNode->code, code);
		strcpy(newNode->name, name);

		if(head == NULL){
			head = tail = newNode;
			head->next = NULL;
		}else if(head == tail){
			head->next = newNode;
			tail = newNode;
		}else{
			tail->next = newNode;
			tail = newNode;
		}

		tail->next = NULL;
	}

	void pop_back(){
		if(head != NULL){
			if(head == tail){
				free(head);

				head = tail = NULL;
			}else{
				curr = head;

				while(curr->next != tail){
					curr = curr->next;
				}
				
				free(tail);

				tail = curr;
				tail->next = NULL;
			}
		}
	}

	void printList(){
		int idx = 0;

		curr = head;

		printf(" _____________________________________\n");
		printf(" | Code  | Name          | Price     |\n");
		printf(" -------------------------------------\n");

		while(curr != NULL){
			printf(" | %05s | %-13s | Rp.%-6d |\n", curr->code, curr->name, curr->price);

			curr = curr->next;
		}

		printf(" -------------------------------------\n\n");
	}
} ItemList;