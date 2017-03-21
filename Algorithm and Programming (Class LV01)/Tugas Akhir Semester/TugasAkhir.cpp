/*
* Title: TugasAkhir
* Description: Tugas akhir semester 1 kelas Algoritma dan Pemrograman
* Date: 15-January-2016
* Author: William Chanrico
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *weekday[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

struct Vehicle{
	char plate[15];
	time_t inSecond;
	struct tm tmInTime;

	Vehicle *next;
	Vehicle *prev;
} *head = NULL, *tail = NULL, *curr = NULL;

void clear(int c){
    for(int a = 0; a < c; a++)
        printf("\n");
}

void fflush(){
	int c;

	while((c = getchar()) != EOF && c != '\n');
}

void splash(){
}

void splash2(){
}

void splash3(){
}

void addVehicle(char *plate){
	struct Vehicle *newVehicle = (struct Vehicle *) malloc(sizeof(struct Vehicle));

	strcpy(newVehicle->plate, plate);
	newVehicle->inSecond = time(NULL);

	time_t timer = time(NULL);

	struct tm *tmNow = localtime(&timer);

	newVehicle->tmInTime = *tmNow;

	if(head == NULL){
		head = tail = newVehicle;
	}else{
		tail->next = newVehicle;
		newVehicle->prev = tail;
		tail = newVehicle;
	}

	head->prev = NULL;
	tail->next = NULL;
}

void removeVehicle(char *plate){
	curr = head;

	while(curr != NULL && strcmp(curr->plate, plate) != 0){
		curr = curr->next;
	}

	if(curr == NULL)
		return;

	if(head == tail){
		free(head);
		head = tail = NULL;
	}else if(curr == head){
		head = head->next;
		head->prev = NULL;

		free(curr);
	}else if(curr == tail){
		tail = tail->prev;
		tail->next = NULL;

		free(curr);
	}else{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;

		free(curr);
	}
}

int printParkedHour(const time_t &inSecond, const time_t &OutSecond){
	return (OutSecond - inSecond) / 3600;
}	

void clear(){
	for(int a = 0; a < 25; a++)
		printf("\n");
}

void printCurrentTimeAndDate(){
	time_t timer = time(NULL);

	struct tm *tmCurrent = localtime(&timer);

	printf("%s, %02d/%02d/%04d - %02d:%02d:%02d\n",
		weekday[tmCurrent->tm_wday],
		tmCurrent->tm_mday,
		tmCurrent->tm_mon + 1,
		tmCurrent->tm_year + 1900,
		tmCurrent->tm_hour,
		tmCurrent->tm_min,
		tmCurrent->tm_sec);
}

void viewParkedVehicles(){
	clear();

	curr = head;

	printf("\n Today is ");
	printCurrentTimeAndDate();

	printf("\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=                              Parked Vehicle                              -=\n");
	printf(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

	int idx = 0;

	if(curr != NULL){
		while(curr != NULL){
			struct tm tmCurr = curr->tmInTime;

			printf(" -= %2d. %-13s Parked @%s, %02d/%02d/%04d - %02d:%02d:%02d\n",
				++idx,
				curr->plate,
				weekday[tmCurr.tm_wday],
				tmCurr.tm_mday,
				tmCurr.tm_mon + 1,
				tmCurr.tm_year + 1900,
				tmCurr.tm_hour,
				tmCurr.tm_min,
				tmCurr.tm_sec);

			curr = curr->next;
		}
	}else{
		printf(" There are no vehicles parked.\n");
	}

	printf("\n Total Vehicles Parked : %d\n", idx);
	
	fflush();
}

void readVehicles(){
	char buffer[100];
	FILE *in = fopen("Parked.txt", "r");

	if(in == NULL)
		return;

	while(true){
		fgets(buffer, 100, in);

		if(feof(in))
			break;

		addVehicle(strtok(buffer, "#"));

		tail->tmInTime.tm_wday = atoi(strtok(NULL, "#"));
		tail->tmInTime.tm_mday = atoi(strtok(NULL, "#"));
		tail->tmInTime.tm_mon = atoi(strtok(NULL, "#"));
		tail->tmInTime.tm_year = atoi(strtok(NULL, "#"));
		tail->tmInTime.tm_hour = atoi(strtok(NULL, "#"));
		tail->tmInTime.tm_min = atoi(strtok(NULL, "#"));
		tail->tmInTime.tm_sec = atoi(strtok(NULL, "#"));
		tail->inSecond = atoi(strtok(NULL, "#"));
	}
}

void showSplash(){
	clear();

	splash();
	splash2();
	splash3();
}

void updateLogs(char *parkInfo, int parkIn){
	FILE *out = fopen("ParkingLogs.txt", "a");

	fputs(parkInfo, out);

	fclose(out);
}

void showLogs(){
	char buffer[100];
	FILE *in = fopen("ParkingLogs.txt", "r");

	clear();

	printf("\n Today is ");
	printCurrentTimeAndDate();

	printf("\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=                              Parked Vehicle                              -=\n");
	printf(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=\n");

	if(in == NULL){
		printf(" -= Couldn't open ParkedLogs.txt\n");
		printf(" -=\n");

		fflush();

		return;
	}

	while(fscanf(in, "%[^\n]\n", buffer) != EOF){
		printf(" -= %s\n", buffer);
	}

	printf(" -= END OF LOG FILE\n");

	fclose(in);

	fflush();
}

int findVehicle(char *plate){
	curr = head;

	while(curr != NULL && strcmp(curr->plate, plate) != 0){
		curr = curr->next;
	}

	if(curr == NULL)
		return 0;

	return 1;
}

void vehicleIn(){
	char plate[15];
	char parkInfo[25] = "";

	clear();

	printf("\n Today is ");
	printCurrentTimeAndDate();

	printf("\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=                                Vehicle In                                -=\n");
	printf(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=\n");
	printf(" -= Input Plate Number : ");
	
	fgets(plate, sizeof(plate), stdin);

	plate[strlen(plate) - 1] = '\0';

	printf(" -=\n");

	if(findVehicle(plate)){
		printf(" -= Vehicle with plate number %s already parked.\n", plate);

		fflush();

		return;
	}

	addVehicle(plate);
	
	printf(" -= Vehicle with plate number %s parked.\n", plate);

	curr = tail;

	time_t timer = time(NULL);
	struct tm tmCurr = curr->tmInTime;

	sprintf(parkInfo, "[ %-12s ] parked @%s, %02d/%02d/%04d - %02d:%02d:%02d\n",
		plate,
		weekday[tmCurr.tm_wday],
		tmCurr.tm_mday,
		tmCurr.tm_mon + 1,
		tmCurr.tm_year + 1900,
		tmCurr.tm_hour,
		tmCurr.tm_min,
		tmCurr.tm_sec);

	updateLogs(parkInfo, 1);
	
	fflush();
}

void vehicleOut(){
	char plate[15];
	char parkInfo[25] = "";
	struct tm tmCurr;

	clear();

	printf("\n Today is ");
	printCurrentTimeAndDate();

	printf("\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=                               Vehicle Out                                -=\n");
	printf(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=\n");
	printf(" -= Input Plate Number : ");

	fgets(plate, sizeof(plate), stdin);

	plate[strlen(plate) - 1] = '\0';

	curr = head;

	while(curr != NULL && strcmp(curr->plate, plate) != 0){
		curr = curr->next;
	}

	if(curr != NULL){
		tmCurr = curr->tmInTime;
	}else{
		printf(" -=\n");
		printf(" -= No vehicle with plate number %s is found.", plate);

		fflush();

		return;
	}

	removeVehicle(plate);

	printf(" -=\n");
	printf(" -=\n");
	printf(" -= Vehicle parked\t@%s, %02d/%02d/%04d - %02d:%02d:%02d\n",
		weekday[tmCurr.tm_wday],
		tmCurr.tm_mday,
		tmCurr.tm_mon + 1,
		tmCurr.tm_year + 1900,
		tmCurr.tm_hour,
		tmCurr.tm_min,
		tmCurr.tm_sec);

	printf(" -= Vehicle is leaving\t@");
	printCurrentTimeAndDate();

	printf(" -=\n");
	
	int hoursParked = printParkedHour(curr->inSecond, time(NULL));

	printf(" -= Vehicle parked for %d hour(s)\n", hoursParked);

	printf(" -=\n");
	printf(" -=\n");
	printf(" -= Total fee = Rp. %d\n", hoursParked > 0 ? 2000 * hoursParked : 2000);

	time_t timer = time(NULL);
	struct tm * tmNow = localtime(&timer);

	sprintf(parkInfo, "[ %-12s ] left   @%s, %02d/%02d/%04d - %02d:%02d:%02d\n",
		plate,
		weekday[tmNow->tm_wday],
		tmNow->tm_mday,
		tmNow->tm_mon + 1,
		tmNow->tm_year + 1900,
		tmNow->tm_hour,
		tmNow->tm_min,
		tmNow->tm_sec);

	updateLogs(parkInfo, 0);

	fflush();
}

void showChargingRules(){
	clear();

	printf("\n Today is ");
	printCurrentTimeAndDate();

	printf("\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=                             Charging Rules                               -=\n");
	printf(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -= For the first hour, customer will be charged 2k, and 2k for each hour    =-\n");
	printf(" -= afterwards                                                               =-\n");
	printf(" -= Please take care of your belongings                                      =-\n");

	fflush();
}

void saveAndExit(){
	FILE *out = fopen("Parked.txt", "w");

	if(out == NULL){
		printf("Couldn't find Parked.txt");

		fflush();

		return;
	}

	curr = head;

	if(curr == NULL){
		fclose(out);

		return;
	}

	while(curr != NULL){
		struct tm tmCurr = curr->tmInTime;

		fprintf(out, "%s#%d#%d#%d#%d#%d#%d#%d#%d#\n", curr->plate,
			tmCurr.tm_wday,
			tmCurr.tm_mday,
			tmCurr.tm_mon,
			tmCurr.tm_year,
			tmCurr.tm_hour,
			tmCurr.tm_min,
			tmCurr.tm_sec,
			curr->inSecond);

		curr = curr->next;
	}

	fclose(out);
}

int showMenu(){
	int inputChoice;

	clear();

	printf("\n Today is ");
	printCurrentTimeAndDate();

	printf("\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -=                                   Menu                                   -=\n");
	printf(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf(" -= 1. Vehicle In                                                            -=\n");
	printf(" -= 2. Vehicle Out                                                           -=\n");
	printf(" -= 3. Parked Vehicles                                                       -=\n");
	printf(" -= 4. Parking Logs                                                          -=\n");
	printf(" -= 5. Charging Rules                                                        -=\n");
	printf(" -= 6. Save & Exit                                                           -=\n");
	printf(" -= =========================================================================-=\n");

	do{
		printf(" >> ");
	}while(scanf("%d", &inputChoice) != 1);

	fflush();

	return inputChoice;
}

int main(){
	int menuChoice;

	readVehicles();

	showSplash();

	do{
		menuChoice = showMenu();

		switch(menuChoice){
			case 1:
				vehicleIn();
				break;

			case 2:
				vehicleOut();
				break;

			case 3:
				viewParkedVehicles();
				break;

			case 4:
				showLogs();
				break;

			case 5:
				showChargingRules();
				break;

			case 6:
				saveAndExit();
				break;
		}
	}while(menuChoice != 6);
}
