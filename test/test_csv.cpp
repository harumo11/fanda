#include "../include/fanda/Csv.hpp"

int main(int argc, char const* argv[])
{
	CSV::CsvFile csv("./test.csv");
	std::cout << "raw size " << csv.raw_size() << std::endl;
	std::cout << "collumn size " << csv.collumn_size() << std::endl;

	std::cout << "0, 0 double " << csv(0,0).get_as_double() << std::endl;;
	std::cout << "0, 0 int " << csv(0,0).get_as_int() << std::endl;
	std::cout << "0, 0 string " << csv(0,0).get_as_string() << std::endl;

	std::cout << "===============================" << std::endl;

	std::cout << "1, 1 string " << csv(1,1).get_as_string() << std::endl;
	std::cout << "1, 1 double " << csv(1,1).get_as_double() << std::endl;;
	std::cout << "1, 1 int " << csv(1,1).get_as_int() << std::endl;
	return 0;
}
