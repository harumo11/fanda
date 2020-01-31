#define BOOST_TEST_MODULE CSV MODULE
#include <boost/test/included/unit_test.hpp>

#include "../include/fanda/Csv.hpp"

BOOST_AUTO_TEST_CASE(open_csv)
{
	CSV::CsvFile csv("./test.csv");
	BOOST_TEST(csv.is_open());
}

BOOST_AUTO_TEST_CASE(size)
{
	CSV::CsvFile csv("./test.csv");
	BOOST_TEST(csv.raw_size() == 3); 
	BOOST_TEST(csv.collumn_size() == 10);
	BOOST_TEST(csv.raw_size() != 5); 
	BOOST_TEST(csv.collumn_size() != 5);
}

BOOST_AUTO_TEST_CASE(get_value)
{
	CSV::CsvFile csv("./test.csv");
	BOOST_TEST(csv(0,0).get_as_string() == "1");
	BOOST_TEST(csv(0,0).get_as_int() == 1);
	BOOST_TEST(csv(0,0).get_as_double() == 1.0);
}

BOOST_AUTO_TEST_CASE(connect)
{
	CSV::CsvFile csv1("./test.csv");
	CSV::CsvFile csv2("./test.csv");
	csv1.connect(csv2);
	csv1.print();
}

BOOST_AUTO_TEST_CASE(add0)
{
	CSV::CsvFile csv("./test.csv");
	std::vector<std::string> vec = {"a", "b", "c"};
	csv.add(vec);
	csv.print();
}

BOOST_AUTO_TEST_CASE(add1)
{
	CSV::CsvFile csv;
	std::vector<std::string> vec = {"a", "b", "c"};
	csv.add(vec);
	csv.print();
}
