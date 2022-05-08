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

template <typename T>
void dateValidation(const char* description, T& argument) {
	bool caught;
	do {
		caught = false;
		std::cout << description;
		std::cin >> argument;

		try {
			T newArgument = argument;
		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
			caught = true;
		}
	} while (caught);
}


void addNewExperience(const char* userName) {
	std::ofstream outFile(userName, std::ios::app);
	char* destination, * comment, ** photos;
	size_t grade, size;
	Date start, end;
	PersonalDB newPerson;

	std::cin.ignore();
	std::cout << "Please enter destination: ";
	destination = new char[MAX_LEN];
	std::cin.getline(destination, MAX_LEN);
	newPerson.setDestination(destination);

	std::cout << "Please enter time period in the following format - YYYY-MM-DD!" << std::endl;

	bool exCaught;
	dateValidation<Date>("Start: ", start);
	newPerson.setStart(start);

	dateValidation<Date>("End: ", end);
	newPerson.setEnd(end);

	do {
		exCaught = false;
		std::cout << "Grade: ";
		std::cin >> grade;

		try {
			newPerson.setGrade(grade);
		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
			exCaught = true;
		}
	} while (exCaught);
	newPerson.setGrade(grade);

	std::cin.ignore();
	std::cout << "Please leave a comment about this destination: ";
	comment = new char[MAX_LEN * 2];
	std::cin.getline(comment, MAX_LEN * 2);
	newPerson.setComment(comment);

	std::cout << "How many photos would you like to upload? : ";
	std::cin >> size;
	std::cin.ignore();
	do {
		exCaught = false;
		photos = new char* [size];
		for (size_t i = 0; i < size; i++) {
			std::cout << "Add new photo: ";
			photos[i] = new char[MAX_LEN];
			std::cin.getline(photos[i], MAX_LEN);
		}
		try {
			newPerson.setPhotos(photos, size);
		}
		catch (std::exception& ex)
		{
			for (size_t i = 0; i < size; i++) {
				delete photos[i];
			}
			delete[] photos;
			std::cerr << ex.what() << std::endl;
			exCaught = true;
		}
	} while (exCaught);
	
	outFile << newPerson;
	
	/*outFile<<newPerson;

	outFile.close();*/

	delete[] destination;
	delete[] comment;
	for (size_t i = 0; i < size; i++) {
		delete photos[i];
	}
	delete[] photos;
}

void signUp() {

	std::cout << "Please create your username: ";
	char* username = new char[MAX_LEN];
	char* password = new char[MAX_LEN];
	char* email = new char[MAX_LEN];


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
		DataBase newOneDB(username, password, email);
		
		std::ofstream outFile("DataBase.dat", std::ios::app);
		outFile << newOneDB;
		outFile.close();


		size_t newLen = strlen(".db") + strlen(username);
		char* newName = new char[newLen + 1];
		strcpy_s(newName, newLen + 1, username);
		strcpy_s(newName + strlen(username), newLen + 1, ".db");


		PersonalDB newPersonal;
		char answer[4];
		std::cout << "Would you like to add your new experience: yes / no?" << std::endl;
		std::cin >> answer;
		
		if (strcmp(answer, "yes") == 0)
			addNewExperience(newName);
		else {
			std::ofstream perosnalOutFile(newName, std::ios::app);
			perosnalOutFile.close();
		}
			
		//(strcmp(answer, "yes") == 0) ? addNewExperience() : (std::ofstream perosnalOutFile(newName, std::ios::app));

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