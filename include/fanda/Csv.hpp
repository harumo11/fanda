#pragma once

#include <iostream>
#include <vector>

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
		 * @param value You should use this function to change data.
		 */
		void set(const std::string value);

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
		 * @param collumn The number of Collumn
		 * @param raw The number of Raw
		 *
		 * @return Data locate in (collumn, raw)
		 */
		Data operator()(const unsigned int collumn, const unsigned int raw);

		/**
		 * @brief Get the collumn size of CSV file
		 *
		 * @return The collumn size of CSV file
		 */
		int collumn_size();

		/**
		 * @brief Get the raw size of CSV file
		 *
		 * @return The raw size of CSV file
		 */
		int raw_size();

		/**
		 * @brief Display all CSV data.
		 */
		void print();

	private:

		/**
		 * @brief A table containing all CSV data
		 */
		std::vector<std::vector<Data>> table;

		/**
		 * @brief A path to the CSV file
		 */
		std::string file_path;
};
}

