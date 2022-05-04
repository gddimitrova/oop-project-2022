#include <iostream>
#include "MyString.h"
int main() {
	const char* temp = "Geri";
	MyString str(temp);

	std::cout << str.getLength() << std::endl;

	str = "Dimitrova";

	std::cout << str.getLength() << std::endl;

	std::cout << str;
	return 0;
}