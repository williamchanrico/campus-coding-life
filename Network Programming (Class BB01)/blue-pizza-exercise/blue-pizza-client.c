/*
* Title: Blue Pizza Delivery Client
* Description: Blue Pizza delivery client side program
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

void clear();
void err_exit(char *fmt, ...);
void printWelcomeMessage();
void inputData(Data *data);
void printOrder(Data *data);

int main(int argc, char **argv){
	int status, sockfd;
	struct addrinfo hints, *res, *p;

	if(argc != 3)
		err_exit("usage: %s <port> <hostname/IP>\n", argv[0]);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(argv[2], argv[1], &hints, &res)) != 0)
		err_exit("getaddrinfo error: %s\n", gai_strerror(status));

	for(p = res; p != NULL; p = p->ai_next){
		if( (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue;

		if(connect(sockfd, p->ai_addr, p->ai_addrlen) == 0)
			break;

		if(close(sockfd) < 0)
			err_exit("close error: %s\n", strerror(errno));
	}

	if(p == NULL)
		err_exit("socket/connect error: %s\n", strerror(errno));

	while(TRUE){
		Data data;

		clear();

		printWelcomeMessage();

		printf("\n");

		inputData(&data);

		if(write(sockfd, &data, sizeof(data)) < 0)
			err_exit("write error: %s\n", strerror(errno));

		if(!strcasecmp(data.name, "exit")){
			printf("\n Thanks for ordering in Blue Custom Pizza Delivery!!\n\n");

			break;
		}

		if(read(sockfd, (Data *) &data, sizeof(data)) < 0)
			err_exit("read error: %s\n", strerror(errno));

		printf("\n");

		printOrder(&data);

		getchar();
	}

	if(close(sockfd) < 0)
		err_exit("close error: %s\n", strerror(errno));

	freeaddrinfo(res);

	exit(EXIT_SUCCESS);
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

void printWelcomeMessage(){
	printf(" ==============================\n");
	printf(" | Blue Custom                |\n");
	printf(" |             Pizza Delivery |\n");
	printf(" |          CLIENT            |\n");
	printf(" ==============================\n");
}

void inputData(Data *data){
	int a = 0;
	int exit = 0;

	do{
		printf(" Input your name [5...20 | \"Exit\" to close the program]: ");
		scanf("%[^\n]", data->name);
		getchar();

		exit = !strcasecmp(data->name, "exit");
	}while((!exit && strlen(data->name) < 5)
		|| strlen(data->name) > 20);

	if(exit)
		return;

	do{
		printf(" Input your address [ends with \"Street\"]: ");
		scanf("%[^\n]", data->address);
		getchar();
	}while(strlen(data->address) < 6
		|| strcmp(data->address + strlen(data->address) - 6, "Street") != 0);

	do{
		printf(" Input pizza name [5...20]: ");
		scanf("%[^\n]", data->pizzaName);
		getchar();
	}while(strlen(data->pizzaName) < 5 || strlen(data->pizzaName) > 20);

	do{
		printf(" Input total topping [1...3]: ");
		scanf("%d", &data->totalTopping);
		getchar();
	}while(data->totalTopping < 1 || data->totalTopping > 3);

	for(a = 0; a < data->totalTopping; a++){
		do{
			printf(" Input topping %d [cheese | mushroom | beef]: ", a + 1);
			scanf("%[^\n]", data->topping[a]);
			getchar();
		}while(strcasecmp(data->topping[a], "cheese") != 0
			&& strcasecmp(data->topping[a], "mushroom") != 0
			&& strcasecmp(data->topping[a], "beef") != 0);
	}
}

void printOrder(Data *data){
	printf(" Pizza code\t: %s\n", data->code);
	printf(" Deliv to\t: %s\n", data->address);
	printf(" Total\t\t: Rp %d\n", data->totalPrice);
	printf(" Press Enter to Continue...");
}

void clear(){
	int a = 0;

	for(a = 0; a < 25; a++)
		printf("\n");
}