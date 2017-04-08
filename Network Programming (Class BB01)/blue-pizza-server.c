/*
* Title: Blue Pizza Delivery Server
* Description: Blue Pizza delivery server side program
* Date: 24-March-2017
* Author: William Chanrico
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <errno.h>

#define SA struct sockaddr
#define MAXLINE 4096
#define LISTENQ 1024
#define TRUE 1
#define FALSE 0

typedef struct {
	char code[10];
	char name[25];
	char address[30];
	char pizzaName[25];
	char topping[3][15];
	int basePrice;
	int totalPrice;
	int totalTopping;
} Data;

int toppingPrice(char *topping){
	if(!strcasecmp(topping, "cheese"))
		return 5000;
	else if(!strcasecmp(topping, "mushroom"))
		return 10000;
	else
		return 15000;
	return -1;
}

void calculatePrice(Data *data){
	int a = 0;

	data->totalPrice = data->basePrice = 20000 * data->totalTopping;

	for(a = 0; a < data->totalTopping; a++)
		data->totalPrice += toppingPrice(data->topping[a]);
}

void generateOrderCode(Data *data){
	sprintf(data->code, "PZ%d%d%d", rand() % 10, rand() % 10, rand() % 10);
}

void printWelcomeMessage(){
	printf(" ==============================\n");
	printf(" | Blue Custom                |\n");
	printf(" |             Pizza Delivery |\n");
	printf(" |          SERVER            |\n");
	printf(" ==============================\n");
}

void printBill(Data *data){
	int a = 0;

	printf(" Bill\n");
	printf(" ======================================\n");
	printf(" | Code\t\t: %-5s               |\n", data->code);
	printf(" | Name\t\t: %-20s|\n", data->name);
	printf(" | Address\t: %-20s|\n", data->address);
	printf(" | -----------------------------------|\n");
	printf(" | Pizza Name\t: %-20s|\n", data->pizzaName);

	for(a = 0; a < data->totalTopping; a++){
		printf(" | Topping %d\t: %-8s            |\n", a + 1, data->topping[a]);
		printf(" |\t\t: Price + Rp %-8d |\n", toppingPrice(data->topping[a]));
	}

	printf(" | Base Price\t: Rp %-15d  |\n", data->basePrice);
	printf(" | Total Price\t: Rp %-15d  |\n", data->totalPrice);
	printf(" ======================================\n");
}

void err_exit(char *fmt, ...){
	va_list ap;
	char buff[MAXLINE];

	va_start(ap, fmt);
	vsprintf(buff, fmt, ap);

	fflush(stdout);
	fputs(buff, stderr);
	fflush(stderr);

	exit(EXIT_FAILURE);
}

void clear(){
	int a = 0;

	for(a = 0; a < 25; a++)
		printf("\n");
}

int main(int argc, char **argv){
	const int on = 1;
	int status, listenfd, connfd;
	struct addrinfo hints, *res, *p;
	// struct sockaddr_storage cliaddr;
	// socklen_t cliaddrlen = sizeof(cliaddr);

	if(argc != 2)
		err_exit("usage: %s <port>\n", argv[0]);

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(NULL, argv[1], &hints, &res)) != 0)
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

	clear();

	printWelcomeMessage();
	

	printf("\n Server active !\n");
	printf(" Waiting for client...\n");

	// if( (connfd = accept(listenfd, (SA *) &cliaddr, &cliaddrlen)) < 0)
	// 	err_exit("accept error: %s\n", strerror(errno));

	if( (connfd = accept(listenfd, NULL, NULL)) < 0)
		err_exit("accept error: %s\n", strerror(errno));

	printf(" Client connected sockfd %d\n", connfd);
	
	while(TRUE){
		Data data;

		if(read(connfd, (Data *) &data, sizeof(data)) < 0)
			err_exit("read error: %s\n", strerror(errno));

		if(!strcasecmp(data.name, "exit"))
			break;

		generateOrderCode(&data);

		calculatePrice(&data);

		printBill(&data);

		printf("\n\n");

		if(write(connfd, &data, sizeof(data)) < 0)
			err_exit("write error: %s\n", strerror(errno));
	}

	if(close(listenfd) < 0)
		err_exit("close error: %s\n", strerror(errno));

	if(close(connfd) < 0)
		err_exit("close error: %s\n", strerror(errno));

	printf(" Client disconnected\n");
	printf("\n Thanks for ordering in Blue Custom Pizza Delivery!!\n\n");

	exit(EXIT_SUCCESS);
}