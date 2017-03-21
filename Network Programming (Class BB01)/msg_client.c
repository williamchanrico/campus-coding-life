/*
* Title: msg_client
* Description: Send message to msg_server
* Author: William Chanrico
* Date: 1-March-2017
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <errno.h>

#define SA struct sockaddr
#define MAXLINE 4096
#define TRUE 1
#define FALSE 0

void err_exit(const char *fmt, ...){
	va_list ap;
	char buff[MAXLINE];

	va_start(ap, fmt);
	vsprintf(buff, fmt, ap);

	fflush(stdout);
	fputs(buff, stderr);
	fflush(stderr);

	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	void *addr;
	int status, sockfd;
	struct addrinfo hints, *res, *p;
	char buff[MAXLINE], serv_ip[INET6_ADDRSTRLEN], serv_port[8];
	char exit_cmd[] = "exit";
	char terminate_server_cmd[] = "shutdown";

	if(argc != 3)
		err_exit("usage: serv <hostname/IP> <port>\n");

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0)
		err_exit("getaddrinfo error: %s\n", gai_strerror(status));

	for(p = res; p != NULL; p = p->ai_next){
		if( (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue;

		if(connect(sockfd, (SA *) p->ai_addr, p->ai_addrlen) == 0)
			break;

		if(close(sockfd) < 0)
			err_exit("close error: %s\n", strerror(errno));
	}

	if(p == NULL)
		err_exit("socket/connect error: %s\n", strerror(errno));


	if(p->ai_family == AF_INET){
		struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;

		addr = &ipv4->sin_addr;
		sprintf(serv_port, "%d", ntohs(ipv4->sin_port));
	}else{
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;

		addr = &ipv6->sin6_addr;
		sprintf(serv_port, "%d", ntohs(ipv6->sin6_port));
	}

	if(inet_ntop(p->ai_family, p->ai_addr, serv_ip, sizeof(serv_ip)) < 0)
		err_exit("inet_ntop error: %s\n", strerror(errno));

	printf("[Console] Connected to server at %s: %s, %s\n",
		(p->ai_family == AF_INET ? "IPv4" : "IPv6"), serv_ip, serv_port);

	freeaddrinfo(res);

	while(TRUE){
		printf("[Message] ");
		scanf("%[^\n]", buff);
		getchar();

		if(write(sockfd, buff, strlen(buff) * sizeof(char)) < 0)
			err_exit("write error: %s\n", strerror(errno));

		if(strncmp(buff, exit_cmd, sizeof(exit_cmd)) == 0 || strncmp(buff, terminate_server_cmd, sizeof(terminate_server_cmd)) == 0)
			break;

		buff[0] = '\0';
	}

	if(close(sockfd) < 0)
		err_exit("close error: %s\n", strerror(errno));
	else
		printf("[Console] Connection terminated\n");

	exit(EXIT_SUCCESS);
}