/*
* Title: Alay Word Checker
* Description: Tugas kelas Algoritma dan Pemrograman
* Date: 27-October-2015
* Author: William Chanrico
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void clear();
int alayLevel(char input[]);

int main(){
	char input[25];

	while(true){
		clear();

		printf("\n Nama: WILLIAM CHANRICO\n");
		printf(" NIM : 1901487652\n");

		printf("\n   -==- Welcome to 4L4Y Word Checker -==-\n");
		printf(" __________________________________________\n\n");
		printf("    ( Type \"exit\" to terminate program )\n\n");

		printf(">> ");
		scanf("%[^\n]", input);

		getchar();

		if(strcmp(input, "exit") == 0)
			return 0;

		printf(" The \"Alay\" level of that word is %d", alayLevel(input));

		getchar();
	}
}

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

int alayLevel(char input[]){
	int ans = 0;
	int len = strlen(input);

	printf("   ");

	if(!isalpha(input[0])){ // if the 1st character is non-alphabetic
		ans++;

		printf("%c", input[0]);

		for(int a = 1; a < len; a++){
			if(!isalpha(input[a]) || input[a] != tolower(input[a])){
				printf("%c", input[a]);

				ans++;
			}else{
				printf(" ");
			}
		}

		printf("\n\n If the 1st char is a non-alphabetic, the rest should be in lowercase.\n\n");
	}else if(input[0] == tolower(input[0])){ // if the 1st character is in lowercase
		printf(" ");

		for(int a = 1; a < len; a++){
			if(!isalpha(input[a]) || input[a] == toupper(input[a])){
				printf("%c", input[a]);

				ans++;
			}else{
				printf(" ");
			}
		}

		printf("\n\n If the 1st char is in lowercase, the rest should be in lowercase.\n\n");
	}else if(input[0] == toupper(input[0])){ // if the 1st character is in uppercase
		int  upper = 0;
		int lower = 0;

		printf(" ");

		for(int a = 1; a < len; a++){
			if(!isalpha(input[a])){
				ans++;
			}else if(input[a] == toupper(input[a])){
				upper++;
			}else if(input[a] == tolower(input[a])){
				lower++;
			}
		}

		ans += (upper > lower? lower : upper);

		for(int a = 1; a < len; a++){
			if(!isalpha(input[a]) || input[a] == (upper > lower? tolower(input[a]) : toupper(input[a]))){
				printf("%c", input[a]);
			}else{
				printf(" ");
			}
		}

		printf("\n\n If the 1st char is in uppercase, the rest should either be in lowercase\n");
		printf(" or uppercase.\n\n");
	}

	printf("\n");

	return ans;
}
