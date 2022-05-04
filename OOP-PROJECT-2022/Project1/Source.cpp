#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "DataBase.h"

int main() {

	try {
		DataBase one("GERII", "1234", "ggdd@gmail.com");
		DataBase two("GERI&", "7372", "sjhaj@gmai.com");
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception has been caught: " << ex.what() << std::endl;
	}

	return 0;
}