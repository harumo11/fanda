#pragma once

#include <iostream>
#include <vector>
#include <optional>

namespace CSV{
class Data {
	public:
		/**
		 * @brief Get the CSV data as double
		 *
		 * @return Get CSV data as double. If you try to convert string to double, you get error.
		 */
		double get_as_double();

		/**
		 * @brief Get the CSV data as std::string
		 *
		 * @return Get the CSV data as std::string. No error occured.
		 */
		std::string get_as_string();

		/**
		 * @brief Get the CSV data as int
		 *
		 * @return Get the CSV data as int. If you try to convert string to double, you get error.
		 */
		int get_as_int();

		/**
		 * @brief Change the CSV data.
		 *
		 * @param value You should use this function to change data in csv file.
		 */
		template<typename T>
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
		 *
		 * @param another_csv_file The csv file which will be concatenate to this csv file.
		 *
		 */
		void connect(const CsvFile another_csv);

		/**
		 * @brief add new row to this CsvFile. new line will be a part of this CsvFile.
		 *
		 * @param new_line new row will be added to the CsvFile.
		 */
		bool add_line(const std::vector<double> new_line);
		bool add_line(const std::vector<int> new_line);
		bool add_line(const std::vector<std::string> new_line);

		/**
		 * @brief do random sampling and get those data as new CsvFile.
		 *
		 * @param sample_size How many line should be return. Returned Csv is composed of continued line. Default size is 1.
		 *
		 * @return new CsvFile which is the result of random sampling. If sampling_size > 1, returned new CSV is done sampling with serial row in the original CSV file.
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

