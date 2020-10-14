#pragma once

#include <iostream>
#include <optional>
#include <tuple>
#include <vector>

namespace CSV {
class Data {
public:
    /**
		 * @brief Get the CSV data as double
		 * Commonly, use with CSV::CsvFile class.
		 *
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * //value of row = 1 and column = 1 is specified. CSV::CsvFile::() operator return CSV::Data type.
		 * double val = csv_file(1,1).get_as_double();
		 * ```
		 *
		 * @return Get CSV data as double. If you try to convert string to double, you get error.
		 */
    double get_as_double();

    /**
		 * @brief Get the CSV data as std::string
		 * Commonly, use with CsvFile class.
		 *
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * // value of row = 1 and column = 1 is specified. CSV::CsvFile::() operator return CSV::Data type.
		 * std::string val = csv_file(1,1).get_as_string();
		 * ```
		 *
		 * @return Get the CSV data as std::string. No error occured.
		 */
    std::string get_as_string();

    /**
		 * @brief Get the CSV data as int
		 * Commonly, use with CsvFile class.
		 *
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * // value of row = 1 and column = 1 is specified. CSV::CsvFile::() operator return CSV::Data type.
		 * int = csv_file(1,1).get_as_int();
		 * ```
		 *
		 * @return Get the CSV data as int. If you try to convert string to double, you get error.
		 */
    int get_as_int();

    /**
		 * @brief Change the CSV data.
		 * Commonly, use with CsvFile class.
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * csv_file(4,4).set('p');
		 * csv_file(5,5).set("pi");
		 * csv_file(6,6).set(3.1415);
		 * csv_file(7,7).set(3);
		 * ```
		 *
		 * @param value You should use this function to change data in csv file.
		 */
    template <typename T>
    void set(const T value);
    void set(const std::string value);
    void set(const char* value);

private:
    std::string value = "";
};

class CsvFile {
public:
    /**
		 * @brief Constructor. 
		 */
    CsvFile();

    /**
		 * @brief Constructor. If the CSV file can't open, the error occured.
		 *
		 * @param file_path The path of CSV file
		 */
    CsvFile(const std::string file_path);

    /**
		 * @brief Open CSV file If you use constructor without arguments, you should use this function to open CSV file.
		 * If the CSV file can open, this class load CSV file data at the same time.
		 *
		 * @param file_path The path of CSV file
		 *
		 * @return If the CSV file opened succssfuly, return true. Otherwize return false.
		 */
    bool open(const std::string file_path);

    /**
		 * @brief Re-read CSV file. If data in CSV file change dynamically, you should use this function to follow that change.
		 *
		 * @return If the CSV file can open, return true. Otherwise, return false.
		 */
    bool reload();

    /**
		 * @brief Get the Data which CsvFile has.
		 *
		 * You can get specified a data in the CSV::CsvFile class.
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * CSV::Data one_data = csv_file(1,1);
		 * double d = one_data.get_as_double();
		 * std::string = one_data.get_as_string();
		 * ```
		 *
		 * Commonly, You can get specified data easily using CSV::Data::get_as_double(), CSV::Data::get_as_int(), and CSV::Data::get_as_string().
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * double d = csv_file(1,1).get_as_double();
		 * int i = csv_file(1,1).get_as_int();
		 * std::string = csv_file(1,1).get_as_string();
		 * ```
		 *
		 * @param column The number of column
		 * @param row The number of row
		 *
		 * @return A mutable data locate in (column, row)
		 */
    Data& operator()(const unsigned int column, const unsigned int row);

    /**
		 * @brief Get the column size of CSV file
		 *
		 * @return The column size of CSV file
		 */
    int column_size();

    /**
		 * @brief Get the row size of CSV file
		 *
		 * @return The row size of CSV file
		 */
    int row_size();

    /**
		 * @brief Display all CSV data.
		 */
    void print();

    /**
		 * @brief If CSV file opend successflly, return true. Otherwize, false.
		 *
		 * @return The CSV file could open : true, Could not open : false
		 */
    bool is_open();

    /**
		 * @brief connect another csv file to this csv file.
		 * ```
		 * CSV::CsvFile a_csv("log.csv");
		 * CSV::CsvFile b_csv("log.csv");
		 * // log.csv has following data
		 * // 1 1 1
		 * // 2 2 2
		 *
		 * a_csv.connect(b_csv);
		 * // After connection(), a_csv has following data
		 * // 1 1 1
		 * // 2 2 2
		 * // 1 1 1
		 * // 2 2 2
		 *
		 * @param another_csv_file The csv file which will be concatenate to this csv file.
		 *
		 */
    void connect(const CsvFile another_csv);

    /**
		 *
		 */
    /**
	 * @brief add new row to this CsvFile. new line will be a part of this CsvFile.
	 *
     * @param new_line new row will be added to the CsvFile.
	 *
	 * @return If given data is added successfuly to CsvFile, return true. Otherwise if given new_line's collumn is not same, return false.
	 */
    bool add_line(const std::vector<double> new_line);
    bool add_line(const std::vector<int> new_line);
    bool add_line(const std::vector<std::string> new_line);

    /**
	 * @brief remove specified line from CSV::CsvFile. 
	 * You can speficy the column whcih you want to remove from CSV::CsvFile.
	 *
	 * @param column_index specify the column(line) which you want to delete.
	 * 
	 * @return If specifed column(line) is removed successfully, return true.
	 *         Otherwise, specified column index is range over(column_index > CSV::CsvFile::row_size()), return false. And nothing to change in CSV::CsvFile data.
	 */
    bool remove_line(const unsigned int column_index);

    /**
		 *
		 *
		 *
		 *
		 * **Original CSV**
		 *
		 * |0|a|alpha|
		 * |1|b|beta|
		 * |2|c|gamma|
		 * 
		 * Do sampling with sampling size 2
		 *
		 * **New CSV**
		 * |0|a|alpha|
		 * |1|b|beta|
		 * 
		 * OR
		 *
		 * |1|b|beta|
		 * |2|c|gamma|
		 *
		 * If you want to get completely randamized new csv as below,
		 *
		 * |0|a|alpha|
		 * |2|c|gamma|
		 *
		 * write the code as below.
		 *
		 * ```
		 * CSV::CsvFile original_csv("excellent.csv");
		 * CSV::CsvFile new_csv;
		 * for (int i = 0, i < 2, i++){
		 *     new_csv.connect(original_csv.get_random_sampling());
		 * }
		 * ```
		 *
		 */
    /**
	 * @brief do random sampling and get those data as new CsvFile.
	 *
	 * @param sample_size How many line should be return. Returned Csv is composed of continued line. Default size is 1.
	 *
	 * @return 
	 */
    CsvFile get_random_sampling(const unsigned int sampling_size = 1);

    /**
		 * @brief Save the csv file with specified name.
		 *
		 * @param file_name New csv file name like "gread_data.csv".
		 *
		 * @return If the file is saved successfully, return true. Otherwise retuen false.
		 */
    bool save(const std::string file_name);

    /**
		 * @brief Save the csv file with specified name.
		 * ```
		 * CSV::CsvFile csv_file("log.csv");
		 * // csv_file has following data
		 * //boy 0x1231 1
		 * //girl 0x3231 2
		 * 
		 * csv_file.save("new_log.csv", {"name", "id", "nubmer"});
		 * // new_log.csv is writen following data
		 * //name  id      number 
		 * //boy   0x1231  1
		 * //girl  0x3231  2
		 *
		 * @param file_name New csv file name like "gread_data.csv".
		 * @param header A header of csv file like {"name", "id", "number"}.
		 *
		 * @return If the file is saved successfully, return true. Otherwise retuen false.
		 */
    bool save(const std::string file_name, const std::vector<std::string> header);

private:
    /**
		 * @brief A table containing all CSV data
		 */
    std::vector<std::vector<Data>> table;

    /**
		 * @brief A path to the CSV file
		 */
    std::string file_path;

    /**
		 * @brief Flag whether the file could open or not
		 */
    bool did_open = false;
};
}
