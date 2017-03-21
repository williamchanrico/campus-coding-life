/*
* Title: Soal 05 Kelas AO
* Description: Tugas kelas Academic Orientation Binusian 2019
* Author: William Chanrico
*/

#include <stdio.h>

int main(){
	int N;

	scanf("%d", &N);

	for(int a = 1; a <= N; a++){
		for(int b = 1; b <= N; b++){
			if(a == 1 || a == N || b == 1 || b == N){
				printf("%-2c", '*');
			}else{ 
				printf("%-2c", ' ');
			}
		}
		
		printf("\n");
	}
}