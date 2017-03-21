/*
* Title: msg_server
* Description: Receive message from msg_client
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
#define LISTENQ 1024
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
	int status, listenfd, connfd;
	struct addrinfo hints, *res, *p;
	char buff[MAXLINE], cli_ip[INET6_ADDRSTRLEN], cli_port[8];
	char exit_cmd[] = "shutdown";
	const int on = 1;

	if(argc != 3)
		err_exit("usage: serv <hostname/IP> <port>\n");

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0)
		err_exit("getaddrinfo error: %s\n", gai_strerror(status));

	for(p = res; p != NULL; p = p->ai_next){
		if( (listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue;

		if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
			err_exit("setsockopt error: %s\n", strerror(errno));

		if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
			break;

		if(close(listenfd) < 0)
			err_exit("close error: %s\n", strerror(errno));
	}

	if(p == NULL)
		err_exit("socket/bind error: %s\n", strerror(errno));

	if(listen(listenfd, LISTENQ) < 0)
		err_exit("listen error: %s\n", strerror(errno));
	else
		printf("[Console] Server is listening at %s, %s\n", argv[1], argv[2]);

	while(TRUE){
		int n;
		void *addr;
		struct sockaddr_storage cliaddr;
		socklen_t cliaddrlen = sizeof(cliaddr);

		if( (connfd = accept(listenfd, (SA *) &cliaddr, &cliaddrlen)) < 0)
			err_exit("accept error: %s\n", strerror(errno));

		if(p->ai_family == AF_INET){
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) &cliaddr;

			addr = &ipv4->sin_addr;
			sprintf(cli_port, "%d", ntohs(ipv4->sin_port));
		}else{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) &cliaddr;

			addr = &ipv6->sin6_addr;
			sprintf(cli_port, "%d", ntohs(ipv6->sin6_port));
		}

		if(inet_ntop(p->ai_family, addr, cli_ip, sizeof(cli_ip)) < 0)
			err_exit("inet_ntop error: %s\n", strerror(errno));

		printf("[Console] A client connected from %s: %s, %s\n",
			(p->ai_family == AF_INET ? "IPv4" : "IPv6"), cli_ip, cli_port);

		while( (n = read(connfd, buff, sizeof(buff))) > 0){
			buff[n] = '\0';

			printf("[Client] %s\n", buff);

			if(strncmp(buff, exit_cmd, sizeof(exit_cmd)) == 0)
				break;
		}

		if(close(connfd) < 0)
			err_exit("close error: %s\n", strerror(errno));
		else
			printf("[Console] Client disconnected\n");

		if(strncmp(buff, exit_cmd, sizeof(exit_cmd)) == 0)
			break;
	}

	freeaddrinfo(res);

	if(close(listenfd) < 0)
		err_exit("close error: %s\n", strerror(errno));
	else
		printf("[Console] Server stopped listening\n");

	exit(EXIT_SUCCESS);
}