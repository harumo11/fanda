#define BOOST_TEST_MODULE CSV MODULE
#include <boost/test/included/unit_test.hpp>

#include "../include/fanda/Csv.hpp"

BOOST_AUTO_TEST_CASE(open_csv_success)
{
    CSV::CsvFile csv("../test/test.csv");
    BOOST_TEST(csv.is_open());
}

BOOST_AUTO_TEST_CASE(open_csv_fail)
{
    CSV::CsvFile csv("not_exist.csv");
    BOOST_TEST(!csv.is_open());
}

BOOST_AUTO_TEST_CASE(size)
{
    CSV::CsvFile csv("../test/test.csv");
    BOOST_TEST(csv.row_size() == 10);
    BOOST_TEST(csv.column_size() == 3);
    BOOST_TEST(csv.row_size() != 5);
    BOOST_TEST(csv.column_size() != 5);
}

BOOST_AUTO_TEST_CASE(get_value)
{
    CSV::CsvFile csv("../test/test.csv");
    BOOST_TEST(csv(1, 0).get_as_string() == "1");
    BOOST_TEST(csv(1, 0).get_as_int() == 1);
    BOOST_TEST(csv(1, 0).get_as_double() == 1.0);
}

BOOST_AUTO_TEST_CASE(connect)
{
    CSV::CsvFile csv1("../test/test.csv");
    CSV::CsvFile csv2("../test/test.csv");
    csv1.connect(csv2);
    csv1.print();
}

BOOST_AUTO_TEST_CASE(add0)
{
    CSV::CsvFile csv("../test/test.csv");
    std::vector<std::string> vec = { "a", "b", "c" };
    csv.add_line(vec);
    csv.print();
}

BOOST_AUTO_TEST_CASE(add1)
{
    CSV::CsvFile csv;
    std::vector<std::string> vec = { "a", "b", "c" };
    BOOST_TEST(csv.add_line(vec) == true);
    csv.print();
}

BOOST_AUTO_TEST_CASE(add2)
{
    CSV::CsvFile csv;
    std::vector<int> vec = { 1, 2, 3 };
    BOOST_TEST(csv.add_line(vec) == true);
    csv.print();
}

BOOST_AUTO_TEST_CASE(add3)
{
    CSV::CsvFile csv;
    std::vector<double> vec = { 1.2, 2.2, 3.2 };
    BOOST_TEST(csv.add_line(vec) == true);
    csv.print();
}

BOOST_AUTO_TEST_CASE(add4)
{
    CSV::CsvFile csv;
    std::vector<double> v1 = { 1.1, 2.1, 3.1, 4.1 };
    BOOST_TEST(csv.add_line(v1) == true);
    std::vector<double> v2 = { 1.2, 2.2, 3.2 };
    BOOST_CHECK_EQUAL(csv.add_line(v2), false);
    csv.print();
}

BOOST_AUTO_TEST_CASE(random_sampling1)
{
    CSV::CsvFile csv("../test/test.csv");
    auto new_csv = csv.get_random_sampling();
    new_csv.print();

    new_csv = csv.get_random_sampling(2);
    new_csv.print();
}

BOOST_AUTO_TEST_CASE(random_sampling2)
{
    CSV::CsvFile original_csv("../test/test.csv");
    CSV::CsvFile new_csv;
    for (int i = 0; i < 5; i++) {
        new_csv.connect(original_csv.get_random_sampling());
    }
    new_csv.print();
}

BOOST_AUTO_TEST_CASE(set_data1)
{
    CSV::CsvFile csv;
    std::vector<double> v1 = { 1.1, 2.1, 3.1, 4.1 };
    csv.add_line(v1);
    csv(0, 0).set("2.2");
    csv.print();
    BOOST_TEST(csv(0, 0).get_as_double() == 2.2);
}

BOOST_AUTO_TEST_CASE(set_data2)
{
    CSV::CsvFile csv;
    std::vector<double> v1 = { 1.1, 2.1, 3.1, 4.1 };
    csv.add_line(v1);
    BOOST_TEST(csv(0, 0).get_as_int() == 1);
}

BOOST_AUTO_TEST_CASE(save2)
{
    CSV::CsvFile csv;
    std::vector<double> v1 = { 1.1, 2.1, 3.1, 4.1 };
    csv.add_line(v1);
    BOOST_TEST(csv.save("new1.csv"));
    BOOST_TEST(csv.save("new2.csv", { "name", "id", "code", "gender" }));
}

BOOST_AUTO_TEST_CASE(display)
{
    CSV::CsvFile csv;
    for (int i = 0; i < 1000; i++) {
        std::vector<int> vec = { 1, 2, 3, 4, 5, 6 };
        csv.add_line(vec);
    }
    csv.print();
}

BOOST_AUTO_TEST_CASE(remove_)
{
    CSV::CsvFile csv("../test/test.csv");
    csv.print();
    std::cout << "---------------------------" << std::endl;
    csv.remove_line(2);
    csv.print();
}
