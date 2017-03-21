/*
* Title: showip
* Description: list IP(s) of a hostname
* Author: William Chanrico
* Date: 1-March-2017
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char **argv){
	int status;
	struct addrinfo hints, *res, *p;
	char ipstr[INET6_ADDRSTRLEN];

	if(argc != 2){
		fprintf(stderr, "usage: showip <hostname>\n");
		exit(1);
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(2);
	}

	printf("IP address of %s:\n", argv[1]);

	for(p = res; p != NULL; p = p->ai_next){
		void *addr;
		char ipver[5];

		if(p->ai_family == AF_INET){
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			strcpy(ipver, "IPv4");
		}else if(p->ai_family == AF_INET6){
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			strcpy(ipver, "IPv6");
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("\t%s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(res);
	
	exit(EXIT_SUCCESS);
}