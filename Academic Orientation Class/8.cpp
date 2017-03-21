/*
* Title: Soal 08 Kelas AO
* Description: Tugas kelas Academic Orientation Binusian 2019
* Author: William Chanrico
*/

#include <stdio.h>
#include <vector>
#include <bitset>

std::vector<int> primes;
std::bitset<10000000> bs;

void sieve(long long x){
	bs.set();

	for(long long a = 2; a <= x; a++) if(bs[a]){
		for(long long b = a * a; b <= x; b += a) bs[b] = 0;
		primes.push_back((int) a);
	}
}

int main(){
	int N;

	sieve(1000000);

	scanf("%d", &N);

	for(int a = 0; a < N; a++){
		for(int b = 1; b < N-a; b++)
			printf("%-3c", ' ');

		for(int b = a; b >= 0; b--)
			printf("%-3d", primes[b]);
		
		printf("\n");
	}
}