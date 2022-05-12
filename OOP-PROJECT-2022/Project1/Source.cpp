#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "DataBase.h"
#include <fstream>
#include "PersonalDB.h"

#define MAX_LEN 1024

bool askQuestion(const char* question) {
	char answer[4];
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
	std::ofstream outFile(userName, std::ios::app);
	char* destination;// * comment;
	char** photos;
	size_t grade, size;
	Date start, end;
	PersonalDB newPerson;

	std::cin.ignore();
	//std::cout << "Please enter destination: ";
	// destination = new char[MAX_LEN];
	//std::cin.getline(destination, MAX_LEN);
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
	/*std::cout << "Please leave a comment about this destination: ";
	comment = new char[MAX_LEN * 2];
	std::cin.getline(comment, MAX_LEN * 2);*/
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
char* createFileName(const char* username) {
	size_t newLen = strlen(".db") + strlen(username);
	char* newName = new char[newLen + 1];
	strcpy_s(newName, newLen + 1, username);
	strcpy_s(newName + strlen(username), newLen + 1, ".db");

	return newName;
}

void askForAddingDest(const char* newName) {
	
	//char* answer = new char[4];
	//std::cout << "Would you like to add new destination: yes / no?" << std::endl;
	//std::cin >> answer;
	//char* answer = askQuestion("Would you like to add your new experience: yes / no?");
	//if (strcmp(answer, "yes") == 0)
	if (askQuestion("Would you like to add your new experience: yes / no?")) {
		addNewExperience(newName);
	}
	else {
		std::ofstream perosnalOutFile(newName, std::ios::app);
		perosnalOutFile.close();
	}
	//delete[] answer;
}

void printInfo(const char* destination);
void searchForDestination() {
	/*char* answer = new char[4];
	std::cout << "Would you like to search for a destination: yes / no?" << std::endl;
	std::cin >> answer;*/
	//answer = askQuestion("Would you like to search for a destination: yes / no?");
	//if (strcmp(answer, "yes") == 0) {
	if(askQuestion("Would you like to search for a destination: yes / no?")){
		//std::cout << "Please enter a destination: ";
		/*char destination[MAX_LEN];
		std::cin >>destination;*/
		// 
		/*std::cin.ignore();
		char* destination = new char[MAX_LEN];
		std::cin.getline(destination, MAX_LEN);*/
		std::cin.ignore();
		char* destination = readArgument("Please enter a destination: ");
		std::cout <<std::endl<<"--------------------------------";
		try {
			printInfo(destination);

		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
	//delete[] answer;
}
void openPersonalDb(const char* user, const bool searchingDest=false, const char* destination=nullptr) {
	std::ifstream inFile(user, std::ios::in);
	if (!inFile.is_open()) {
		std::cerr << "There are no registered destinations yet!" << std::endl;
	}
	else {
		bool emptyFile = inFile.peek() == EOF;
		bool isDoneReading = false;
		while (!inFile.eof() && !emptyFile) {
			PersonalDB newPerson;

			newPerson.readFromFile(inFile);

			if (searchingDest) {
				if (newPerson.getDestination() == destination) {
					std::cout<<"--------------------------------"<<std::endl;
					std::cout << "User: " << user << std::endl;
					std::cout << newPerson ;
				}
			}
			else {
				std::cout << "--------------------------------"<<std::endl;
				std::cout << newPerson;
			}


			inFile.ignore(2);
			if (inFile.eof()) {
				isDoneReading = true;
			}
			else {
				size_t currtel = inFile.tellg();
				inFile.seekg(currtel - 2, std::ios::beg);
			}
		}
	}
	inFile.close();

	std::cout << "--------------------------------" << std::endl;
	//askForAddingDest(user);
	//searchForDestination();

	//повторение на код с функцията signUp(), да се оправи
	/*char answer[4];
	std::cout << "Would you like to add your new experience: yes / no?" << std::endl;
	std::cin >> answer;

	if (strcmp(answer, "yes") == 0)
		addNewExperience(user);*/
}

void printInfo(const char* destination) {
	std::ifstream inDestFile("Destination.txt", std::ios::in);
	bool found = false;
	bool emptyFile = inDestFile.peek() == EOF;

	while (!inDestFile.eof() && !emptyFile) {
		/*size_t len;
		inDestFile >> len;
		inDestFile.ignore();
		char* name = new char[MAX_LEN];
		inDestFile.get(name, len + 1);*/
		if (checkChar(inDestFile, destination)) {
			found = true;
			size_t len;
			inDestFile >> len;
			inDestFile.ignore();
			char* user = new char[MAX_LEN];
			inDestFile.get(user, len + 1);

			openPersonalDb(user, true, destination);
		}
		/*if (strcmp(name, destination) == 0) {
			found = true;
			inDestFile >> len;
			inDestFile.ignore();
			char* user = new char[MAX_LEN];
			inDestFile.get(user, len + 1);

			openPersonalDb(user, true, destination);
		}*/
		else
		{
			inDestFile.ignore(MAX_LEN, '\n');
		}

	}
	if (!found) {
		throw std::exception("There is no such destination yet!");
	}
}






//TODO добавяне на опция за преглед/добавяне на снимка и тн., оправяне на цялостната абстракция
void login() {
	/*char* username = new char[MAX_LEN];
	std::cout << "To login please enter a valid username: ";
	std::cin.getline(username, MAX_LEN);*/
	char* username = readArgument("To login please enter a valid username: ");

	/*char* password = new char[MAX_LEN];
	std::cout << "Please enter a valid password: ";
	std::cin.getline(password, MAX_LEN);*/
	char* password = readArgument("Please enter a valid password: ");


	std::ifstream dataFile("DataBase.dat", std::ios::in);
	//if (!dataFile.is_open())
	//	throw std::exception("There is no such user");

	bool found = false;
	size_t len = strlen(username);


	while (!dataFile.eof()) {
		/*size_t lenName;
		char* name = new char[MAX_LEN];
		dataFile >> lenName;
		dataFile.ignore();
		dataFile.get(name, lenName + 1);*/

		if (checkChar(dataFile, username)) {
			/*size_t lenPass;
			char* pass = new char[MAX_LEN];
			dataFile >> lenPass;
			dataFile.ignore();
			dataFile.get(pass, lenPass + 1);*/
			if (checkChar(dataFile, password)) {
				found = true;
				//try {
				openPersonalDb(createFileName(username));
				//}
				//catch (std::exception& ex) {
				//	std::cerr << ex.what() << std::endl;
				//	askForAddingDest(createFileName(username));
				//	searchForDestination();
				////}
				
				break;
			}
			/*if (strcmp(pass, password) == 0) {
				found = true;
				openPersonalDb(createFileName(username));
				break;
			}*/
			else {
				dataFile.ignore(MAX_LEN, '\n');
			}
		}

		/*if (strcmp(name, username) == 0) {
			size_t lenPass;
			char* pass = new char[MAX_LEN];
			dataFile >> lenPass;
			dataFile.ignore();
			dataFile.get(pass, lenPass + 1);
			if (strcmp(pass, password) == 0) {
				found = true;
				openPersonalDb(createFileName(username));
				break;
			}
			else {
				dataFile.ignore(MAX_LEN, '\n');
			}
		}*/
		else {
			dataFile.ignore(MAX_LEN, '\n');
		}
	}

	dataFile.close();

	char* newName = createFileName(username);
	if (!found) {
		throw std::exception("There is no such user!");
	}
	//char answer[4];
	do {
		askForAddingDest(newName);
		searchForDestination();
	
		/*std::cout << "Would you like to continue: yes / no?"<<std::endl;
		std::cin >> answer;*/
	} while (askQuestion("Would you like to continue: yes / no?"));

}

void freeMemory(const char* arg1, const char* arg2, const char* arg3) {
	delete[] arg1;
	delete[] arg2;
	delete[] arg3;
}

void getStarted();

void signUp() {

	/*std::cout << "Please create your username: ";
	char* username = new char[MAX_LEN];
	std::cin.getline(username, MAX_LEN);*/

	char* username = readArgument("Please create your username: ");


	/*char* password = new char[MAX_LEN];
	std::cout << "Please create your password: ";
	std::cin.getline(password, MAX_LEN);*/
	char* password = readArgument("Please create your password: ");
	
	/*char* email = new char[MAX_LEN];
	std::cout << "Please enter your email: ";
	std::cin.getline(email, MAX_LEN);*/

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
			/*std::cout << "Would you like to continue - yes / no?" << std::endl;
			char answer[4];
			std::cin >> answer;*/
			//const char* answer = askQuestion("Would you like to continue - yes/no");
			/*if (strcmp(answer, "yes") == 0) {
				getStarted();
			}*/
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
	
	//TODO do{}while() loop не работи след повторна грешка както и do while loop при функцията getStarted();
	bool caught = false;
	do {
		try {
			getStarted();
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what();
			/*std::cout << std::endl << "Would you like to continue - yes/no" << std::endl;
			char answer[4];
			std::cin >> answer;*/
			//const char* answer = askQuestion("Would you like to continue - yes / no?");
			//if (strcmp(answer, "yes") == 0) {
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