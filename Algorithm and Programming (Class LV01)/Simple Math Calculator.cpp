/*
	WILLIAM CHANRICO - 1901487652

	Create a program that demonstrate all these :
	1. Recursive
	2. Iteration
	3. Pass by value
	4. Pass by reference
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int memo[200][200];

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

int pow(int x, int y){
	if(y == 0)
		return 1;
	return (x * pow(x, y - 1));
}

int pascalTriangle(int row, int col){
	if(memo[row][col] != -1)
		return memo[row][col];

	if(col==0 || row==col)
		return memo[row][col] = 1;

	return memo[row][col] = pascalTriangle(row-1, col) + pascalTriangle(row-1, col-1);
}

double average(double *numbers, int N){
	double ans = 0;

	for(int a = 0; a < N; a++)
		ans += numbers[a];

	return (ans / N);
}

void averageCalculator(){
	int N;
	double numbers[1000];

	printf("\n Average Calculator\n");
	printf(" ==================\n");
	printf(" How many numbers to calculate ? ");

	scanf("%d", &N);

	for(int a = 0; a < N; a++){
		printf(" Enter number (%d) : ", a + 1);
		scanf("%lf", &numbers[a]);
	}

	fflush();

	printf("\n\n The average is %.3lf\n", average(numbers, N));
}

void polynomialCalculator(){
	int N;
	int A;
	int B;
	int coef[10];
	int bilDalam;
	int ans = 0;

	printf("\n Polynomial Function (a+b)^N\n");
	printf(" ===========================\n\n");
	printf(" Input N [1..9] : ");

	scanf("%d", &N);

	printf(" Input a [0..9] : ");

	scanf("%d", &A);

	printf(" Input b [0..9] : ");

	scanf("%d", &B);

	fflush();

	printf("\n Result of (a+b)^%d :\n\n", N);

	for(int a = 0; a <= N; a++){
		coef[a] = pascalTriangle(N, a);

		if(!a)
			printf(" = %d(a^%d*b^%d) ", coef[a], N-a, a);
		else
			printf("+ %d(a^%d*b^%d)", coef[a], N-a, a);
	}

	printf("\n\n");

	for(int a = 0; a <= N; a++){
		bilDalam = (pow(A, N-a) * pow(B, a));

		if(!a)
			printf(" = %d(%d) ", pascalTriangle(N, a), bilDalam);
		else
			printf("+ %d(%d)", pascalTriangle(N, a), bilDalam);

		ans += coef[a] * bilDalam;
	}

	printf("\n\n = %d\n", ans);
}

int main(){
	int choice;

	memset(memo, -1, sizeof(memo));

	do{
		clear();

		printf("\n Nama : William Chanrico\n");
		printf(" NIM  : 1901487652\n\n");

		printf(" -= Simple Math Calculator =-\n");
		printf(" =================================\n");
		printf(" 1. Polynomial Function Calculator\n");
		printf(" 2. Average Calculator\n");
		printf(" 3. Quit\n");
		printf(" ---------------------------------\n");
		printf(" >> ");

		scanf("%d", &choice);

		clear();

		switch(choice){
		case 1:
			polynomialCalculator();

			break;
		case 2:
			averageCalculator();

			break;
		}

		getchar();
	}while(choice != 3);
}