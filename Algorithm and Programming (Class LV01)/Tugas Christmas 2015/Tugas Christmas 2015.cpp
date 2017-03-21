/*
* Title: Tugas Christmas 2015
* Description: Tugas kelas Algoritma dan Pemrograman untuk natal tahun 2015
* Date: 1-January-2016
* Author: William Chanrico
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "musiclist.txt"

typedef struct Data{
	char name[150];
	int duration;
} Music;

Music music[1000];
int musicIdx = 0;

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

void aboutAuthor(){
	printf(" Name\t: William Chanrico\n");
	printf(" NIM\t: 1901487652\n");

	getchar();
}

void printMusicList(){
	printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 194, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 194, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
	printf(" %c Index %c Music Name           %c Duration %c\n", 179, 179, 179, 179);
	printf(" |-------%c----------------------%c----------|\n", 197, 197);
	
	for(int a = 0; a < musicIdx; a++)
		printf(" %c  %2d   %c %-20s %c  %02d:%02d   %c\n", 179, a, 179, music[a].name, 179, music[a].duration / 60, music[a].duration % 60, 179);
	
	printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
}

int showMenu(){
	int input;

	clear();

	printMusicList();

	printf("\n -= LV01's Music Box =-\n");
	printf(" -====================-\n");
	printf(" 1. Insert\n");
	printf(" 2. Sort\n");
	printf(" 3. Search\n");
	printf(" 4. Update\n");
	printf(" 5. Delete\n");
	printf(" 6. Save & Exit\n");

	do{
		printf(" >> ");

		scanf("%d", &input);

		fflush();
	}while(input < 1 || input > 6);

	return input;
}

void insertMusic(){
	clear();

	printf(" -= Insert Music =-\n\n");

	do{
		printf(" Input Music's Name [Max 100 chars] : ");

		fgets(music[musicIdx].name, sizeof(music[musicIdx].name), stdin);

		music[musicIdx].name[strlen(music[musicIdx].name) - 1] = '\0';

		printf("\n");
	}while(strlen(music[musicIdx].name) < 1 || strlen(music[musicIdx].name) > 100);

	while(true){
		printf("\n Input Music's Duration [In seconds] : ");

		if(scanf("%d", &music[musicIdx].duration) != 1){
			fflush();

			continue;
		}else{
			break;
		}
	}

	musicIdx++;

	printf("\n Insert Music Success.");
	
	fflush();

	getchar();
}

void swap(int x, int y){
	Music temp = music[x];
	music[x] = music[y];
	music[y] = temp;
}

void sortAscByName(){
	int swapped = 1;

	while(swapped){
		swapped = 0;

		for(int a = 1; a < musicIdx; a++){
			if(strcmp(music[a - 1].name, music[a].name) > 0){
				swap(a - 1, a);
				swapped = 1;
			}
		}
	}
}

void sortAscByDuration(){
	int swapped = 1;

	while(swapped){
		swapped = 0;

		for(int a = 1; a < musicIdx; a++){
			if(music[a - 1].duration > music[a].duration){
				swap(a - 1, a);
				swapped = 1;
			}
		}
	}
}

void sortMusic(){
	int inputSort;

	clear();

	printMusicList();

	printf("\n -= Sort Music =-\n\n");
	printf(" 1. Sort by name\n");
	printf(" 2. Sort by duration\n");

	do{
		printf(" >> ");

		scanf("%d", &inputSort);

		fflush();
	}while(inputSort != 1 && inputSort != 2);

	switch(inputSort){
		case 1:
			sortAscByName();
			break;

		case 2:
			sortAscByDuration();
			break;
	}

	printf("\n Music has been sorted by %s.", inputSort == 1 ? "Name" : "Duration");

	getchar();
}

void readFile(){
	FILE *in = fopen(FILENAME, "r");

	if(!in){
		perror("Error opening file");

		getchar();
	}else{
		while(fscanf(in, "%[^#]#%d\n", music[musicIdx].name, &music[musicIdx].duration) != EOF){
			musicIdx++;
		}

		fclose(in);
	}
}

void searchByName(){
	char inputName[150];

	clear();

	printMusicList();

	if(musicIdx == 0){
		printf("\n There's no music listed.");

		getchar();

		return;
	}

	printf("\n -= Search Music =-\n\n");
	printf(" Input Music's name : ");

	fgets(inputName, sizeof(inputName), stdin);

	inputName[strlen(inputName) - 1] = '\0';

	printf("in name: %s\n", inputName);

	for(int a = 0; a < musicIdx; a++){
		printf("|%s| |%s|\n", music[a].name, inputName);
		if(strcmp(music[a].name, inputName) == 0){
			printf("\n Music Found!\n\n");
			printf(" Music's Name     : %s\n", music[a].name);
			printf(" Music's Duration : %02d:%02d\n", music[a].duration / 60, music[a].duration % 60);
			
			break;
		}else if(a == musicIdx - 1){
			printf("\n No Music Found!");
		}
	}

	getchar();
}

void updateDuration(){
	char inputName[150];

	clear();

	printMusicList();

	if(musicIdx == 0){
		printf("\n There's no music listed.");

		getchar();

		return;
	}

	printf("\n -= Update Music =-\n\n");
	printf(" Input Music's name : ");

	fgets(inputName, sizeof(inputName), stdin);

	inputName[strlen(inputName) - 1] = '\0';

	for(int a = 0; a < musicIdx; a++){
		if(strcmp(music[a].name, inputName) == 0){
			printf("\n Music Found!\n\n");
			printf(" Music's Name     : %s\n", music[a].name);
			printf(" Music's Duration : %02d:%02d\n\n", music[a].duration / 60, music[a].duration % 60);
			
			while(1){
				printf(" Input new duration [In seconds] : ");

				if(scanf("%d", &music[a].duration) == 1){
					printf("\n Duration updated!.");

					break;
				}

				fflush();
			}

			break;
		}else if(a == musicIdx - 1){
			printf("\n No Music Found!");
		}
	}

	fflush();

	getchar();
}

void deleteMusic(){
	char inputName[150];

	clear();

	printMusicList();

	if(musicIdx == 0){
		printf("\n There's no music listed.");

		getchar();

		return;
	}

	printf("\n -= Delete Music =-\n\n");
	printf(" Input Music's name : ");

	fgets(inputName, sizeof(inputName), stdin);

	inputName[strlen(inputName) - 1] = '\0';

	for(int a = 0; a < musicIdx; a++)
		if(strcmp(music[a].name, inputName) == 0){
			printf("\n Music Found!\n\n");
			printf(" Music's Name     : %s\n", music[a].name);
			printf(" Music's Duration : %02d:%02d\n\n", music[a].duration / 60, music[a].duration % 60);
			
			for(int b = a + 1; b < musicIdx; b++){
				music[b - 1] = music[b];
			}
			
			musicIdx--;

			printf(" Music deleted!");

			break;
		}else if(a == musicIdx - 1){
			printf("\n No Music Found!");
		}

	getchar();
}

void saveAndExit(){
	FILE *out = fopen(FILENAME, "w");

	for(int a = 0; a < musicIdx; a++){
		fprintf(out, "%s#%d\n", music[a].name, music[a].duration);
	}

	fclose(out);

	clear();

	printf(" All data saved.");

	getchar();
}

int main(){
	int inputMenu;

	aboutAuthor();

	readFile();

	do{
		inputMenu = showMenu();

		switch(inputMenu){
			case 1:
				insertMusic();
				break;

			case 2:
				sortMusic();
				break;

			case 3:
				searchByName();
				break;

			case 4:
				updateDuration();
				break;

			case 5:
				deleteMusic();
				break;

			case 6:
				saveAndExit();
				break;
		}

	}while(inputMenu != 6);
}