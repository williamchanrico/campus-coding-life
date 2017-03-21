/*
* Title: Soal01
* Description: Soal latihan lab kelas Object Oriented Programming sesi 01
* Date: 15-February-2016
* Author: William Chanrico
*/

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

int totalPrice;
std::vector<std::pair<int, int> > pizza;

void resetShop();
void clear();
void orderPizza();
void payPizza();
void exitShop();
void showMenu();
int inputInt();

int main(){
	resetShop();
		
	clear();

	showMenu();
}

void resetShop(){
	totalPrice = 0;

	pizza.clear();

	pizza.push_back(std::make_pair(80000, 0));
	pizza.push_back(std::make_pair(50000, 0));
}

void clear(){
	for(int a = 0; a < 25; a++)
		std::cout << '\n';
}

int inputInt(){
	int ret;
	std::string s;

	getline(std::cin, s);

	std::stringstream ss(s);

	ss >> ret;

	return ret;
}

void orderPizza(){
	int inputOrder;

	clear();

	std::cout << "Choose an order\n";
	std::cout << "===============\n";
	std::cout << "1. Meat Lover Pizza (@ Rp. 80000,-)\n";
	std::cout << "2. Vegetarian Pizza (@ Rp. 50000,-)\n\n";

	do{
		std::cout << "Which pizza do you want to order[1-2]: ";
		
		inputOrder = inputInt();
	}while(inputOrder < 1 || inputOrder > 2);

	totalPrice += pizza[inputOrder - 1].first;
	++pizza[inputOrder - 1].second;

	std::cout << "Thank you...";

	std::cin.get();
}

void payPizza(){
	if(totalPrice == 0){
		std::cout << "You haven't buy anything.";

		std::cin.get();

		return;
	}

	int inputPayment;

	clear();

	std::cout << "You have ordered " << pizza[0].second << " Meat Lover Pizza(s) and " << pizza[1].second << " Vegetarian Pizza(s).\n\n\n";
	std::cout << "Total price: Rp. " << totalPrice << '\n';

	do{
		std::cout << "Input your money [minimum Rp. " << totalPrice << "] :Rp. ";

		inputPayment = inputInt();
	}while(inputPayment < totalPrice);

	std::cout << "Your change : Rp. " << inputPayment - totalPrice << '\n';
	std::cout << "Thank you...";

	resetShop();

	std::cin.get();
}

void exitShop(){
	clear();

	std::cout << "Thank you for buying our pizza...";

	std::cin.get();
}

void showMenu(){
	int inputMenu;

	do{
		clear();

		std::cout << "Welcome to Yummmy Delivery Pizza\n";
		std::cout << "================================\n";
		std::cout << "1.Order Pizza\n";
		std::cout << "2.Pay\n";
		std::cout << "3.Exit\n\n";

		do{
			std::cout << "Choose: ";

			inputMenu = inputInt();
		}while(inputMenu < 1 || inputMenu > 3);

		switch(inputMenu){
		case 1:
			orderPizza();
			break;

		case 2:
			payPizza();
			break;

		case 3:
			exitShop();
			break;
		}

	}while(inputMenu != 3);
}