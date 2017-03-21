/*
* Title: Soal 03 Kelas AO
* Description: Tugas kelas Academic Orientation Binusian 2019
* Author: William Chanrico
*/

#include <stdio.h>

int main(){
	int N;

	scanf("%d", &N);
	
	for(int a = 0; a < N; a++){
		for(int b = 0; b < a; b++)
			printf("%-3c", ' ');

		for(int b = 1; b <= N-a; b++)
			printf("%-3d", b);

		printf("\n");
	}
}