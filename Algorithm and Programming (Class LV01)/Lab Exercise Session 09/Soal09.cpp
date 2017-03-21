/*
* Title: Soal09
* Description: Soal latihan lab kelas Algoritma dan Pemrograman sesi 09
* Date: 11-December-2015
* Author: William Chanrico
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Player{
	char name[15];
	int averageScore;
	int numOfGame;

	struct Player *next;
	struct Player *prev;
} *head = NULL, *tail = NULL, *curr = NULL;

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

void pushPlayer(char name[], int averageScore, int numOfGame){
	struct Player *newPlayer = (struct Player *) malloc(sizeof(struct Player));

	strcpy(newPlayer->name, name);
	newPlayer->averageScore = averageScore;
	newPlayer->numOfGame = numOfGame;
	
	if(head == NULL){
		head = tail = newPlayer;
	}else{
		tail->next = newPlayer;
		newPlayer->prev = tail;
		tail = newPlayer;
	}

	head->prev = NULL;
	tail->next = NULL;
}

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void deletePlayer(){
	char name[15];

	do{
		printf("\nInput player name[1..10] : ");

		scanf("%s", name);
		fflush();
	}while(strlen(name) < 1 || strlen(name) > 10);

	curr = head;

	while(curr != NULL && strcmp(curr->name, name)){
		curr = curr->next;
	}

	if(curr == NULL){
		printf("\nName of %s not found!\n\n", name);

		printf("Press Enter to continue....");
	}else{
		if(curr == head){
			head = curr->next;
			
			if(head != NULL)
				head->prev = NULL;

			free(curr);
		}else if(curr == tail){
			tail = curr->prev;
			tail->next = NULL;

			free(curr);
		}else{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;

			free(curr);
		}
		
		printf("\n%s successfully deleted..\n\n", name);

		printf("Press Enter to continue....");
	}

	getchar();
}

void printMenu(){
	printf("Score Record DotA Player\n");
	printf("========================\n");
	printf("1.View Record\n");
	printf("2.Add Player Record\n");
	printf("3.Add New Player\n");
	printf("4.Delete Player\n");
	printf("5.Save and Exit\n");
}

void viewRecord(){
	clear();

	curr = head;

	printf("  Player Name     | Average Score   | Number of Playing\n");
	printf("=======================================================\n");

	while(curr != NULL){
		printf("  %-15s | %-15d | %-15d  \n", curr->name, curr->averageScore, curr->numOfGame);
		
		curr = curr->next;
	}

	printf("\nPress Enter to continue.....");

	getchar();
}

void readData(){
	FILE *file = fopen("soal09.txt", "r");

	if(!file){
		perror("Error opening soal09.txt");

		getchar();
	}else{
		char name[15];
		int averageScore;
		int numOfGame;
		
		while(fscanf(file, "%s%d%d\n", name, &averageScore, &numOfGame) != EOF){
			pushPlayer(name, averageScore, numOfGame);
		}
	}

	fclose(file);
}

void addNewPlayer(){
	char name[15];

	do{
		printf("\nInput player name[1..10] : ");

		scanf("%s", name);

		fflush();
	}while(strlen(name) < 1 || strlen(name) > 10);

	pushPlayer(name, 0, 0);

	printf("\nData successfully added..\n\n");

	printf("Tekan ENTER untuk melanjutkan.....");

	getchar();
}

void addPlayerRecord(){
	char name[15];
	int score;

	do{
		printf("\nInput player name[1..10] : ");

		scanf("%s", name);

		fflush();
	}while(strlen(name) < 1 || strlen(name) > 10);

	do{
		printf("Input player score[0..100] : ");

		scanf("%d", &score);

		fflush();
	}while(score < 0 || score > 100);

	curr = head;

	while(curr != NULL && strcmp(curr->name, name)){
		curr = curr->next;
	}

	if(curr == NULL){
		printf("\nName of %s not found!\n\n", name);
		printf("Tekan ENTER untuk melanjutkan....");
	}else{
		curr->averageScore = ((curr->averageScore * curr->numOfGame) + score)/ (curr->numOfGame + 1);

		(curr->numOfGame)++;

		printf("\nScore successfully updated^^\n\n");
		printf("Tekan ENTER untuk melanjutkan....");
	}

	getchar();
}

void saveAndExit(){
	FILE *file = fopen("soal09.txt", "w");

	curr = head;

	while(curr != NULL){
		fprintf(file, "%s %d %d\n", curr->name, curr->averageScore, curr->numOfGame);

		curr = curr->next;
	}
	
	fclose(file);
}

int main(){
	int choice;

	readData();

	do{
		clear();

		printMenu();

		do{
			printf("Input your choice[1..5] : ");

			scanf("%d", &choice);

			fflush();
		}while(choice < 1 || choice > 5);

		switch(choice){
		case 1:
			viewRecord();

			break;
		case 2:
			addPlayerRecord();

			break;
		case 3:
			addNewPlayer();

			break;
		case 4:
			deletePlayer();

			break;
		case 5:
			saveAndExit();

			break;
		}
	}while(choice != 5);
}