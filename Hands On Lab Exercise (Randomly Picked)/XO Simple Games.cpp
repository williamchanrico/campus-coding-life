/*
* Title: Soal Hands On Lab - Digipet
* Description: Soal dari HOL kelas lab
* Date: 
* Author: William Chanrico
*/

#include <stdio.h>
#include <stdlib.h>

char xoTable[4][4];

void resetTable(){
	for(int a = 1; a <= 3; a++)
		for(int b = 1; b <= 3; b++)
			xoTable[a][b] = '_';
}

void printTable(){
	printf("XO Table\n");
	printf("=-=-=-=-=-=-\n\n");

	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++)
			if(a == 0 && b == 0)
				printf("  ");
			else if(a == 0)
				printf("%2d", b);
			else if(b == 0)
				printf("%2d", a);
			else
				printf("%2c", xoTable[a][b]);

		printf("\n\n");
	}
}

void inputKoordinat(int &x, int &y){
	int a, b;

	printf("masukan koordinat X [1..3]: ");

	scanf("%d", &a);

	printf("masukan koordinat Y [1..3]: ");

	scanf("%d", &b);

	while(a > 3 || a < 1 || b > 3 || b < 1){
		printf("Posisi di luar tabel permainan.\n\n");
		printf("masukan koordinat X [1..3]: ");

		scanf("%d", &a);

		printf("masukan koordinat Y [1..3]: ");

		scanf("%d", &b);
	}

	x = a;
	y = b;
}

int customDFS(char n, int x, int y, int direction){
	if(x > 3 || x < 1 || y > 3 || y < 1 || xoTable[x][y] != n)
		return 0;

	switch(direction){
	case 1:
		return 1 + customDFS(n, x + 1, y, direction);
	case 2:
		return 1 + customDFS(n, x + 1, y + 1, direction);
	case 3:
		return 1 + customDFS(n, x, y + 1, direction);
	case 4:
		return 1 + customDFS(n, x + 1, y - 1, direction);
	}
}

bool won(bool x){
	char target = (x ? 'X' : 'O');
	
	for(int a = 1; a <= 3; a++)
		for(int b = 1; b <= 3; b++)
			if(xoTable[a][b] == target)
				for(int c = 1; c <= 4; c++)
					if(customDFS(target, a, b, c) == 3)
						return true;
	return false;
}

void clearScreen(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

int main(){
	while(true){
		int steps = 9;
		bool giliranX = true;
		bool draw = true;

		clearScreen();

		resetTable();

		while(steps){
			int X, Y;

			printTable();

			if(won(!giliranX))
				break;
			
			printf("Giliran pemain %c untuk jalan.\n", (giliranX?'X':'O'));
			printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");

			inputKoordinat(X, Y);

			while(xoTable[Y][X] != '_'){
				printf("Posisi telah diisi..\n");

				inputKoordinat(X, Y);
			}

			xoTable[Y][X] = (giliranX ? 'X' : 'O');

			clearScreen();

			giliranX = !giliranX;
			steps--;
		}

		printf("GAME SELESAI^^\n\n");

		if(steps){
			printf("Selamat \"%c\" Menang!!\n\n", (!giliranX) ? 'X' : 'O');
		}else{
			printTable();

			printf("Permainan Seri..\n\n");
		}

		printf("Apakah Anda mau mengulang [y/n]: ");

		char inp;

		getchar();

		inp = getchar();

		if(inp != 'y')
			break;
	}
	
	return 0;
}