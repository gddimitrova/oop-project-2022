#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "DataBase.h"
#include <fstream>
#include "PersonalDB.h"

#define MAX_LEN 1024

char* createFileName(const char* username) {
	size_t newLen = strlen(".db") + strlen(username);
	char* newName = new char[newLen + 1];
	strcpy_s(newName, newLen + 1, username);
	strcpy_s(newName + strlen(username), newLen + 1, ".db");

	return newName;
}

bool askQuestion(const char* question) {
	char answer[MAX_LEN];
	std::cout << question << std::endl;
	std::cin >> answer;

	return (strcmp(answer, "yes") == 0);
}

char* readArgument(const char* description) {
	char* argument = new char[MAX_LEN];
	std::cout << description;
	std::cin.getline(argument, MAX_LEN);

	return argument;
}


bool checkChar(std::ifstream& in, const char* destination) {
	size_t len;
	in >> len;
	in.ignore();
	char* name = new char[MAX_LEN];
	in.get(name, len + 1);

	return (strcmp(name, destination)==0);
}

void addToDestinations(const char* destination, const char* user) {
	std::fstream destFile;
	destFile.open("Destination.txt", std::ios::in | std::ios::out | std::ios::app);
	bool found = false;
	bool emptyFile = destFile.peek() == EOF;

	while (!emptyFile && !destFile.eof()) {
		size_t len;
		destFile >> len;
		destFile.ignore();
		char* dest = new char[len + 1];
		destFile.get(dest, len + 1);

		
		if(strcmp(dest, destination) == 0)
		{
			size_t len;
			destFile >> len;
			destFile.ignore();
			char* name = new char[len + 1];
			destFile.get(name, len + 1);

			if (strcmp(name, user) == 0) {
				found = true;
				break;
			}
			delete[] name;
		}
		else {
			destFile.ignore(MAX_LEN, '\n');
		}
		delete[] dest;
	}
	destFile.clear();

	if (!found) {
		destFile << strlen(destination) << " " << destination << " " << strlen(user) << " " << user << std::endl;
	}

	destFile.close();

}


void dateValidation(const char* description, Date& argument) {
	bool caught;
	do {
		caught = false;
		std::cout << description;
		std::cin >> argument;

		try {
			Date newArgument = argument;
		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
			caught = true;
		}
	} while (caught);
}


void addNewExperience(const char* userName) {
	char* newName = createFileName(userName);
	std::ofstream outFile(newName, std::ios::app);
	char* destination;
	char** photos;
	size_t grade, size;
	Date start, end;
	PersonalDB newPerson;

	std::cin.ignore();
	destination = readArgument("Please enter destination: ");
	newPerson.setDestination(destination);

	std::cout << "Please enter time period in the following format - YYYY-MM-DD!" << std::endl;

	bool exCaught;
	do {
		exCaught = false;
		dateValidation("Start: ", start);
		dateValidation("End: ", end);

		try {
			if (!newPerson.validDates(start, end))
				throw std::exception("End date must be after start date");
			else
				break;
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			exCaught = true;
		}
	} while (true);
	newPerson.setStart(start);
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
	char* comment = readArgument("Please leave a comment about this destination: ");
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

	addToDestinations(destination, userName);

	outFile.close();

	delete[] destination;
	delete[] comment;
	for (size_t i = 0; i < size; i++) {
		delete photos[i];
	}
	delete[] photos;
}


void askForAddingDest(const char* newName) {

	if (askQuestion("Would you like to add your new experience: yes / no?")) {
		addNewExperience(newName);
	}
	else {
		std::ofstream perosnalOutFile(newName, std::ios::app);
		perosnalOutFile.close();
	}
}

void printInfo(const char* destination);
void searchForDestination() {
	if(askQuestion("Would you like to search for a destination: yes / no?")){
		std::cin.ignore();
		char* destination = readArgument("Please enter a destination: ");
		try {
			printInfo(destination);
		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
}

template <typename T>
T openPersonalDb(const char* user,const bool searchingDest=false, const char* destination=nullptr) {
	char* newName = createFileName(user);
	std::ifstream inFile(newName, std::ios::in);
	if (!inFile.is_open()) {
		std::cerr << "There are no registered destinations yet!" << std::endl;
	}
	else {
		bool emptyFile = inFile.peek() == EOF;
		double countGrades = 0;
		double sumGrades = 0;
		while (!inFile.eof() && !emptyFile) {
			PersonalDB newPerson;

			newPerson.readFromFile(inFile);

			if (searchingDest) {
				if (newPerson.getDestination() == destination) {
					std::cout << "--------------------------------" << std::endl;
					std::cout << "User: " << user << std::endl;
					std::cout << newPerson;
					std::cout << "--------------------------------" << std::endl;
					countGrades++;
					sumGrades += newPerson.getGrade();
				}
			}
			else {
				std::cout << "--------------------------------" << std::endl;
				std::cout << newPerson;
				std::cout << "--------------------------------" << std::endl;
			}

			inFile.ignore(2);
			if (!inFile.eof()) {
				size_t currtel = inFile.tellg();
				inFile.seekg(currtel - 2, std::ios::beg);
			}

		}
		inFile.close();
		if (searchingDest) {
			return sumGrades / countGrades;
		}
	}
	
}

void printInfo(const char* destination) {
	std::ifstream inDestFile("Destination.txt", std::ios::in);
	bool found = false;
	bool emptyFile = inDestFile.peek() == EOF;
	double count = 0, sum = 0;

	while (!inDestFile.eof() && !emptyFile) {
		if (checkChar(inDestFile, destination)) {
			found = true;
			size_t len;
			inDestFile >> len;
			inDestFile.ignore();
			char* user = new char[MAX_LEN];
			inDestFile.get(user, len +1);
		//	inDestFile.ignore(2);

			sum += openPersonalDb<double>(user, true, destination);
			count++;
		}
		else
		{
			inDestFile.ignore(MAX_LEN, '\n');
		}

	}
	if (!found) {
		throw std::exception("There is no such destination yet!");
	}
	else {
		std::cout << "Average grade from the users for this destination is: " << sum / count << std::endl;
	}
}

void login() {
	char* username = readArgument("To login please enter a valid username: ");
	char* password = readArgument("Please enter a valid password: ");


	std::ifstream dataFile("DataBase.dat", std::ios::in);

	bool found = false;
	size_t len = strlen(username);

	bool emptyFile = dataFile.peek() == EOF;

	while (!dataFile.eof() && !emptyFile) {
		if (checkChar(dataFile, username)) {
			if (checkChar(dataFile, password)) {
				found = true;
				openPersonalDb<bool>(username);
				break;
			}
			else {
				dataFile.ignore(MAX_LEN, '\n');
			}
		}
		else {
			dataFile.ignore(MAX_LEN, '\n');
		}
	}

	dataFile.close();

	if (!found) {
		throw std::exception("There is no such user!");
	}

	//char* newName = createFileName(username);
	do {
		askForAddingDest(username);
		searchForDestination();
	} while (askQuestion("Would you like to continue: yes / no?"));

}

void freeMemory(const char* arg1, const char* arg2, const char* arg3) {
	delete[] arg1;
	delete[] arg2;
	delete[] arg3;
}

void getStarted();

void signUp() {

	char* username = readArgument("Please create your username: ");
	char* password = readArgument("Please create your password: ");
	char* email = readArgument("Please enter your email: ");

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
			
		freeMemory(username, password, email);

		getStarted();
	}
	
}

void getStarted() {
	
	std::cout << "Choose your next operation: login / register" << std::endl;

	char operation[9];
	std::cin >> operation;
	std::cin.ignore();

	if (strcmp(operation, "login") == 0) {
		try {
			login();
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;

			if (askQuestion("Would you like to continue - yes / no")) {
				getStarted();
			}
		}
	}
	else if (strcmp(operation, "register") == 0) {
		signUp();
	}
	else {
		throw std::exception("Invalid operation!");
	}
}

int main() {

	std::cout << "Hello! Welcome to the travellers diary" << std::endl;
	
	bool caught = false;
	do {
		try {
			getStarted();
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what();

			if(askQuestion("Would you like to continue - yes / no?")){
				caught = true;
			}
			else {
				break;
			}
		}
	} while (caught);

	return 0;
}