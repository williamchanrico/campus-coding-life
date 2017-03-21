/*
* Title: Soal Hands On Lab - Digipet
* Description: Soal dari HOL kelas lab
* Date: 
* Author: William Chanrico
*/

#include <stdio.h>

struct Data{
	int num;
	int health;
	int happiness;
	int cleaness;
};

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void fflush(){
	int c;

	while( (c = getchar()) != EOF && c != '\n');
}

void play(struct Data &digi){
	digi.happiness += 3;
	digi.health -= 1;
	digi.cleaness -= 1;
}

void eat(struct Data &digi){
	digi.health += 3;
	digi.happiness -= 1;
	digi.cleaness -= 1;
}

void bath(struct Data &digi){
	digi.cleaness += 3;
	digi.health -= 1;
	digi.happiness -= 1;
}

void status(struct Data &digi){
	printf("%c%cDigipet %d's Status\n", 3, 3, digi.num);

	for(int a = 0; a < 20; a++)
		printf("%c", 205);

	printf("\nHappiness\t : %d\n", digi.happiness);
	printf("Health\t\t : %d\n", digi.health);
	printf("Cleanness\t : %d\n", digi.cleaness);
}

void cek(struct Data &digi){
	if(digi.happiness <= 0){
		digi.happiness = 0;

		printf("Your Digipet %d is going to sad, play with it..", digi.num);

		getchar();
	}

	if(digi.health <= 0){
		digi.health = 0;

		printf("Your Digipet %d is going to sick, it must eat..", digi.num);

		getchar();
	}

	if(digi.cleaness <= 0){
		digi.cleaness = 0;

		printf("Your Digipet %d is going to dirty, it must go to bath..", digi.num);

		getchar();
	}

	digi.happiness = (digi.happiness > 100 ? 100 : digi.happiness);
	digi.cleaness = (digi.cleaness > 100 ? 100 : digi.cleaness);
	digi.health = (digi.health > 100 ? 100 : digi.health);
}

int choose(){
	int pet;
	do{
		printf("Choose your digipet [1..2]: ");

		scanf("%d", &pet);

		fflush();
	}while(pet != 1 && pet != 2);

	return pet;
}

int main(){
	int pil = 0;
	Data digi1;
	Data digi2;

	digi1.num = 1;
	digi1.happiness = 10;
	digi1.health = 10;
	digi1.cleaness = 10;

	digi2.num = 2;
	digi2.happiness = 10;
	digi2.health = 10;
	digi2.cleaness = 10;

	do{
		clear();

		printf("\t%c", 201);

		for(int a = 0; a < 9; a++)
			printf("%c", 205);

		printf("%c\n", 187);
		printf("\t%c Digipet %c\n", 186, 186);
		printf("\t%c", 200);

		for(int a = 0; a < 9; a++)
			printf("%c", 205);

		printf("%c", 188);
		printf("\n\n");

		status(digi1);

		printf("\n\n");

		status(digi2);

		printf("\n\n");

		printf("Choose Digipet Activity :\n");
		printf("1. Play\n");
		printf("2. Eat\n");
		printf("3. Bath\n");
		printf("4. Exit\n");

		printf("Input your choice : ");

		scanf("%d", &pil);

		fflush();

		switch(pil){
		case 1:
			if(choose() == 1)
				play(digi1);
			else
				play(digi2);
			break;
		case 2:
			if(choose() == 1)
				eat(digi1);
			else
				eat(digi2);
			break;
		case 3:
			if(choose() == 1)
				bath(digi1);
			else
				bath(digi2);
			break;
		}

		cek(digi1);
		cek(digi2);
	}while(pil != 4);
}