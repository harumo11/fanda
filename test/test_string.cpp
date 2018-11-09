#include <iostream>
#include "../include/String.hpp"

int main(int argc, char const* argv[])
{
	std::string sentence = "This : is : good : news :";

	auto itr = String::split(sentence, ':');

	for (auto&& e : itr ){
		std::cout << e << std::endl;
	}
	return 0;
}
