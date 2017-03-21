/*
* Title: Matris 4x4
* Description: Tugas kelas Algoritma dan Pemrograman
* Date: 27-October-2015
* Author: William Chanrico
*/

#include <stdio.h>

void inputMatriks(int arr[][4]){
	for(int a = 1;a <= 4;a++){
		for(int b = 1;b <= 4;b++){
			printf(" Matrik[%d][%d] : ", a, b);

			scanf("%d", &arr[a - 1][b - 1]);
		}
	}
}

void clear(){
	for(int a = 0;a < 25;a++)
		printf("\n");
}

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

int main(){
	int choice;
	int arr1[4][4];
	int arr2[4][4];
	int arr3[4][4];

	do{
		clear();

		printf("\n Nama: WILLIAM CHANRICO\n");
		printf(" NIM : 1901487652\n");

		printf(" =====================\n");
		printf(" Operasi Matriks 4 x 4\n");
		printf(" =====================\n");
		printf(" 1. Penjumlahan matriks\n");
		printf(" 2. Perkalian matriks\n");
		printf(" 3. Keluar\n\n");
		printf(">> ");

		scanf("%d", &choice);

		fflush();

		switch(choice){
		case 1:
			clear();

			printf(" =========================\n");
			printf(" Penjumlahan Matriks 4 x 4\n");
			printf(" =========================\n\n");
			printf(" Isi elemen-elemen matriks 1 :\n");

			inputMatriks(arr1);

			printf(" Isi elemen-elemen matriks 2 :\n");

			inputMatriks(arr2);

			fflush();

			for(int a = 0 ; a < 4; a++)
				for(int b = 0; b < 4; b++){
					arr3[a][b] = arr1[a][b] + arr2[a][b];
				}

			clear();

			printf(" =========================\n");
			printf(" Penjumlahan Matriks 4 x 4\n");
			printf(" =========================\n\n");

			for(int a = 0; a < 4; a++){
				printf(" ");
				for(int b = 0; b < 4; b++)
					printf(" %-2d", arr1[a][b]);

				printf(" ");

				for(int b = 0; b < 4; b++)
					if((a > 0 && a < 3) || (b > 0 && b < 3))
						printf(".");
					else
						printf(" ");

				printf(" ");

				for(int b = 0; b < 4; b++)
					printf(" %-2d", arr2[a][b]);

				printf("  ");

				for(int b = 0;b < 4; b++)
					if((a > 0 && a < 3))
						printf(".");
					else
						printf(" ");

				printf(" ");

				for(int b = 0; b < 4; b++)
					printf(" %-2d", arr3[a][b]);

				printf("\n");
			}

			getchar();

			break;
		case 2:
			clear();
			printf(" =======================\n");
			printf(" Perkalian Matriks 4 x 4\n");
			printf(" =======================\n\n");
			printf(" Isi elemen-elemen matriks 1 :\n");

			inputMatriks(arr1);

			printf(" Isi elemen-elemen matriks 2 :\n");

			inputMatriks(arr2);

			fflush();

			for(int a = 0; a < 4; a++){
				for(int b = 0; b < 4; b++){
					arr3[a][b] = 0;

					for(int c = 0; c < 4; c++)
						arr3[a][b] += arr1[a][c] * arr2[c][b];
				}
			}

			clear();

			printf(" =======================\n");
			printf(" Perkalian Matriks 4 x 4\n");
			printf(" =======================\n\n");

			for(int a = 0; a < 4; a++){
				printf(" ");
				for(int b = 0; b < 4; b++)
					printf(" %-2d", arr1[a][b]);

				printf(" ");

				for(int b = 0; b < 4; b++)
					if((a + b == 3) || a == b)
						printf(".");
					else
						printf(" ");

				printf(" ");

				for(int b = 0; b < 4; b++)
					printf(" %-2d", arr2[a][b]);

				printf("  ");

				for(int b = 0; b < 4; b++)
					if((a > 0 && a < 3))
						printf(".");
					else
						printf(" ");

				printf(" ");

				for(int b = 0; b < 4; b++)
					printf(" %-2d", arr3[a][b]);

				printf("\n");
			}

			getchar();
			
			break;
		}
	}while(choice != 3);
}