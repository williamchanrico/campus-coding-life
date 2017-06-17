/*
* Title: listen-broadcast-ipv4
* Description: Listen to broadcast message, only supports IPv4
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
	struct sockaddr_in addr;

	if(argc != 2){
		printf("usage: %s <bcast_port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	printf("Listening for broadcast messages on port %s...\n\n", argv[1]);

	while(1){
		char recv_msg[MSG_SIZE];
		struct sockaddr_in sender_addr;
		socklen_t sender_addrlen = sizeof(sender_addr);

		memset(recv_msg, '\0', sizeof(recv_msg));

		if(recvfrom(sockfd, recv_msg, sizeof(recv_msg), 0, (struct sockaddr *) &sender_addr, &sender_addrlen) == -1){
			perror("recvfrom");
			continue;
		}

		printf("[Broadcast Message from %s:%d]\n", inet_ntoa(sender_addr.sin_addr), ntohs(sender_addr.sin_port));
		printf("== BEGIN MSG ==\n\n");
		printf("%s\n\n", recv_msg);
		printf("== END MSG ==\n\n");
	}
}