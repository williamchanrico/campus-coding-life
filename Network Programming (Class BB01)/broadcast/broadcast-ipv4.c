/*
* Title: broadcast-ipv4
* Description: Broadcast message, only supports IPv4
* Date: 16-June-2017
* Author: William Chanrico
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MSG_SIZE 1024

int main(int argc, char **argv){
	int sockfd;
	int allow_bcast = 1;
	struct sockaddr_in addr;

	if(argc != 3){
		printf("usage: %s <bcast_addr> <bcast_port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &allow_bcast, sizeof(allow_bcast)) != 0){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	
	if(inet_pton(AF_INET, argv[1], &addr.sin_addr) != 1){
		perror("inet_pton");
		exit(EXIT_FAILURE);
	}

	printf("Send to %s:%s\n", argv[1], argv[2]);

	while(1){
		char send_msg[MSG_SIZE];

		printf("Broadcast: ");
		scanf("%[^\n]", send_msg);
		getchar();

		if(sendto(sockfd, send_msg, strlen(send_msg) * sizeof(char), 0, (struct sockaddr *) &addr, sizeof(addr)) == -1){
			perror("sendto");
			exit(EXIT_FAILURE);
		}
	}

}