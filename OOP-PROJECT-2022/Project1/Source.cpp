#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "DataBase.h"
#include <fstream>
#include "PersonalDB.h"

#define MAX_LEN 1024

void login() {

}

void freeMemory(const char* user, const char* pass, const char* email) {
	delete[] user;
	delete[] pass;
	delete[] email;
}

void signUp() {

	std::cout << "Please create your username: ";
	char* username = new char[MAX_LEN];
	char* password = new char[MAX_LEN];
	char* email = new char[MAX_LEN];

	//char username[1024], password[1024], email[1024];

	//std::cin.ignore();
	std::cin.getline(username, MAX_LEN);
	std::cout << "Please create your password: ";
	std::cin.getline(password, MAX_LEN);
	std::cout << "Please enter your email: ";
	std::cin.getline(email, MAX_LEN);

	bool caught = false;
	try {
		DataBase test(username, password, email);
	}
	catch (const std::exception& ex) {
		caught = true;
		freeMemory(username, password, email);
		std::cerr <<ex.what() << std::endl;
	}

	if (caught) {
		signUp();
	}
	else {
		DataBase newOne(username, password, email);
		std::cout << newOne;

		freeMemory(username, password, email);
	}
	
}

int main() {

	
	//try {
	//	
	//	DataBase two("GERI&", "7372", "sjhaj@gmai.com");
	//}
	//catch (const std::exception& ex) {
	//	std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	//}


	//DataBase one("GERII", "1234", "ggdd@gmail.com");
	//std::ofstream outFile("DataBase.db", std::ios::app);
	//outFile << one;

	//const char* photos[] = { "photoOne.png", "photoTwo.jpeg"};
	//PersonalDB one("Burgas", 1, 12, 2001, 12, 12, 2001, 5, "lovely place", photos, 2);
	//std::cout << one << std::endl;

	//const char* photos1[] = { "newPhoto.png", "another.jpeg" };
	//PersonalDB two = one;
	//std::cout << two;

	/*try {
		Date one(2022, 5, 5);
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	}*/

	/*try {
		Date two(2022, 2, 29);
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	}*/

	/*try {
		PersonalDB one("Burgas", 28, 04, 2022, 28, 03, 2023, 1, "lovely place", photos, 2);
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	}*/


	/*const char* photos2[] = { "photoOne.png", "photoTwo.jpeeg" };
	try {
		PersonalDB one("Burgas", 28, 04, 2022, 28, 03, 2023, 1, "lovely place", photos2, 2);
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	}*/

	std::cout << "Hello! Welcome to the travellers diary" << std::endl;
	std::cout << "Choose your next operation: login / register" << std::endl;

	char operation[9];
	std::cin >> operation;
	std::cin.ignore();

	(strcmp(operation, "login") == 0) ? login() : signUp();
	


	return 0;
}