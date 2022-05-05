#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "DataBase.h"
#include <fstream>
#include "PersonalDB.h"

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

	const char* photos[] = { "photoOne.png", "photoTwo.jpeg"};
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


	const char* photos2[] = { "photoOne.png", "photoTwo.jpeeg" };
	try {
		PersonalDB one("Burgas", 28, 04, 2022, 28, 03, 2023, 1, "lovely place", photos2, 2);
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	}


	return 0;
}