/*
* Title: Tugas BeeFest
* Description: Tugas kelas Algoritma dan Pemrograman untuk minggu BeeFest
* Date: 14-December-2015
* Author: William Chanrico
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

struct Data{
	char title[25];
	char speaker[25];
	char note[350];

	Data *next;
	Data *prev;
} *head = NULL, *tail = NULL, *curr = NULL;

int dataSize = 0;

void push(char *title, char *speaker, char *note);
void deleteNote();
void clear();
void fflush();
void printEventList();
void showNotes(int eventNumber);
void readData();
void readNotes();
void inputData();
void saveAndExit();
void showMenu();
int wordsCount(char note[]);

int main(){
	readData();

	showMenu();
}

void push(char *title, char *speaker, char *note){
	Data *newData = (struct Data *) malloc(sizeof(struct Data));

	strcpy(newData->title, title);
	strcpy(newData->speaker, speaker);
	strcpy(newData->note, note);

	if(head == NULL){
		head = tail = newData;
	}else{
		tail->next = newData;
		newData->prev = tail;
		tail = newData;
	}

	head->prev = NULL;
	tail->next = NULL;
}

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

void showMenu(){
	int choice;
	
	do{
		clear();

		printEventList();

		printf("\n\n -= BINUS Festival =-\n");
		printf(" ====================\n");
		printf(" 1. Read Notes\n");
		printf(" 2. Input\n");
		printf(" 3. Delete Notes\n");
		printf(" 4. Save & Exit\n");
		printf(" --------------------\n");
		printf(" >> ");

		scanf("%d", &choice);
		fflush();;

		switch(choice){
		case 1:
			readNotes();
			break;
		case 2:
			inputData();
			break;
		case 3:
			deleteNote();
			break;
		case 4:
			saveAndExit();
			break;
		}

	}while(choice != 4);
}

void deleteNote(){
	clear();

	if(dataSize == 0){
		printf("There are no events recorded.");

		getchar();

		return;
	}

	int choice;
	int idx = 0;
	char title[25];

	printf(" Events\n");
	printf(" ======\n");

	printEventList();

	do{
		printf(" Pick Event : ");

		scanf("%d", &choice);

		fflush();;
	}while(choice < 1 || choice > dataSize);

	curr = head;

	while(++idx != choice){
		curr = curr->next;
	}

	if(head == tail){
		head = tail = NULL;
	}else if(curr == head){
		head = head->next;
		head->prev = NULL;
	}else if(curr == tail){
		tail = tail->prev;
		tail->next = NULL;
	}else{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}

	free(curr);

	dataSize--;

	printf(" Successfully deleted !");

	getchar();
}

void printEventList(){
	int idx = 0;

	curr = head;

	printf(" No. Title                 Speaker\n");
	printf(" -------------------------------------\n");

	while(curr != NULL){
		printf(" %2d. %-20s  %-11s\n", ++idx, curr->title, curr->speaker);

		curr = curr->next;
	}

	printf(" -------------------------------------\n");
}

void readData(){
	FILE *file = fopen("BeeFest.txt", "r");

	if(!file){
		perror("Error opening BeeFest.txt");
	}else{
		char buffer[600];
		char title[25];
		char speaker[25];
		char note[350];

		while(true){
			fgets(buffer, 350, file);
			
			if(feof(file))
				break;

			strcpy(title, strtok(buffer, ";"));
			strcpy(speaker, strtok(NULL, ";"));
			strcpy(note, strtok(NULL, ";"));

			push(title, speaker, note);

			dataSize++;
		}

		fclose(file);
	}
}

void readNotes(){
	clear();

	if(dataSize == 0){
		printf("There are no events recorded.");

		getchar();

		return;
	}

	int choice;
	char title[25];

	curr = head;

	printf(" Events\n");
	printf(" ======\n");

	printEventList();

	do{
		printf(" Pick Event : ");

		scanf("%d", &choice);

		fflush();;
	}while(choice < 1 || choice > dataSize);

	showNotes(choice);

	getchar();
}

void showNotes(int eventNumber){
	int idx = 1;

	curr = head;

	clear();

	while(idx != eventNumber && curr != tail){
		curr = curr->next;
	}

	printf("Title\n");
	printf("-----\n");
	printf("%s\n\n", curr->title);

	printf("Speaker\n");
	printf("-------\n");
	printf("%s\n\n", curr->speaker);

	printf("Note\n");
	printf("----\n");
	printf("%s\n\n", curr->note);
}

int wordsCount(char note[]){
	char temp[500];
	int ans = 0;

	strcpy(temp, note);

	char *tok = strtok(temp, " ");

	while(tok != NULL){
		if(strcmp(tok, " ") != 0 && strcmp(tok, "") != 0)
			ans++;
		tok = strtok(NULL, " ");
	}

	return ans;
}

void inputData(){
	int valid;
	char title[25];
	char speaker[25];
	char note[350];

	clear();

	printf(" Input Event Data\n");
	printf(" ================\n");
	
	printf(" Title\t\t: ");

	fgets(title, sizeof(title), stdin);

	title[strlen(title) - 1] = '\0';

	do{
		valid = 1;

		printf(" Speaker [3-30]\t: ");

		fgets(speaker, sizeof(speaker), stdin);

		speaker[strlen(speaker) - 1] = '\0';

		for(int a = 0, len = strlen(speaker); a < len; a++)
			if(!isalpha(speaker[a]) || len < 3 || len > 30){
				valid = 0;

				break;
			}

	}while(!valid);

	do{
		valid = 1;

		printf(" Note [20-300]\t: ");

		fgets(note, sizeof(note), stdin);

		note[strlen(note) - 1] = '\0';
	}while(wordsCount(note) < 20 || wordsCount(note) > 300);

	push(title, speaker, note);

	dataSize++;
}

void saveAndExit(){
	FILE *file = fopen("BeeFest.txt", "w");

	curr = head;

	while(curr != NULL){
		fprintf(file, "%s;%s;%s;\n", curr->title, curr->speaker, curr->note);

		curr = curr->next;
	}

	fclose(file);

	printf(" Data Saved!");

	getchar();
}
