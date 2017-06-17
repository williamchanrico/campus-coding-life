/*
* Title: listen-broadcast-ipv6
* Description: Listen to broadcast message, also supports IPv6
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
	struct sockaddr_in6 addr;

	if(argc != 2){
		printf("usage: %s <bcast_port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if( (sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(atoi(argv[1]));
	addr.sin6_addr = in6addr_any;

	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	printf("Listening for broadcast messages on port %s...\n\n", argv[1]);

	while(1){
		char recv_msg[MSG_SIZE];
		char sender_ip[INET6_ADDRSTRLEN];
		struct sockaddr_in6 sender_addr;
		socklen_t sender_addrlen = sizeof(sender_addr);

		memset(recv_msg, '\0', sizeof(recv_msg));

		if(recvfrom(sockfd, recv_msg, sizeof(recv_msg), 0, (struct sockaddr *) &sender_addr, &sender_addrlen) == -1){
			perror("recvfrom");
			continue;
		}

		if(inet_ntop(AF_INET6, &sender_addr.sin6_addr, sender_ip, sizeof(sender_ip)) == NULL){
			perror("inet_ntop");
			continue;
		}

		printf("[Broadcast Message from %s:%d]\n", sender_ip, ntohs(sender_addr.sin6_port));
		printf("== BEGIN MSG ==\n\n");
		printf("%s\n\n", recv_msg);
		printf("== END MSG ==\n\n");
	}
}