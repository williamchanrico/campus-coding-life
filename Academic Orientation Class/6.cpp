/*
* Title: Soal 06 Kelas AO
* Description: Tugas kelas Academic Orientation Binusian 2019
* Author: William Chanrico
*/

#include <stdio.h>
#include <stdlib.h>
 
int main(){
    int N;
    int lebarBuffer;
 
    scanf("%d", &N);

    N /= 2;

    for(int a = -N; a <= N; a++){
        lebarBuffer = 79;

        for(int b = -N; b <= N; b++){
            if(lebarBuffer == 0)
                break;

            if(abs(a) == abs(b))
                printf("x");
            else
                printf(" ");

            if(b == N)
                b = -N;

            --lebarBuffer;
        }
        
        printf("\n");
    }
}