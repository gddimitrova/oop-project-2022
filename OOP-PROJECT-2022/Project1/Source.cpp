#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "DataBase.h"
#include <fstream>

int main() {

	DataBase one("GERII", "1234", "ggdd@gmail.com");
	//try {
	//	
	//	DataBase two("GERI&", "7372", "sjhaj@gmai.com");
	//}
	//catch (const std::exception& ex) {
	//	std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	//}

	std::ofstream outFile("DataBase.db", std::ios::app);
	outFile << one;

	return 0;
}