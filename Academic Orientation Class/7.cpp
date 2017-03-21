/*
* Title: Soal 07 Kelas AO
* Description: Tugas kelas Academic Orientation Binusian 2019
* Author: William Chanrico
*/

#include <stdio.h>
#include <string.h>

int memo[10000];

int fib(int x){
	if(memo[x] != -1)
		return memo[x];
	return memo[x] = fib(x - 1) + fib(x - 2);
}

int main(){
	int N;

	memset(memo, -1, sizeof(memo));

	memo[0] = memo[1] = 1;

	scanf("%d", &N);

	for(int a = 1; a <= N; a++){
		for(int b = 0; b < a; b++)
			printf("%-4d", fib(b));

		printf("\n");
	}
}

/* versi non-rekursif

#include <stdio.h>

int main(){
	int N;
	int x;
	int y;
	int z;

	scanf("%d", &N);
	
	for(int a = 0; a < N; a++){
		x = 0; 
		y = 0; 
		z = 1;

		for(int b = 0; b <= a; b++){
			printf("%-3d", z);

			x = y;
			y = z;
			z = x + y;
		}
		
		printf("\n");
	}
}

*/