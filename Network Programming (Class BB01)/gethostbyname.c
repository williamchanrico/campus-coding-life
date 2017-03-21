#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
	char buff[100];
	struct hostent *host;

	host = gethostbyname("arzhon.id");

	inet_ntop(AF_INET, host->h_addr, buff, 100);

	printf("IP: %s\n", buff);
	// printf("IP: %s\n", inet_ntoa(*((struct in_addr *) host->h_addr)));
}