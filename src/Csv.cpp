#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/fanda/Csv.hpp"
#include "../include/fanda/String.hpp"

namespace CSV{

	double Data::get_as_double(){
		return std::stod(this->value);
	}

	std::string Data::get_as_string(){
		return this->value;
	}

	int Data::get_as_int(){
		return std::stoi(this->value);
	}

	void Data::set(const std::string value){
		this->value = value;
	}


	CsvFile::CsvFile(){
	}

	CsvFile::CsvFile(const std::string file_path){
		// get file path 
		this->file_path = file_path;

		// read csv file
		this->reload();
	}

	bool CsvFile::open(const std::string file_path){
		// get file path
		this->file_path = file_path;

		// read csv file and return open or not open
		return this->reload();
	}

	bool CsvFile::reload(){
		//read csv file with file_path
		std::ifstream csv_file(this->file_path);
		if (!csv_file) {
			std::cout << "[ Fanda Error ] CSV file is could not open" << std::endl;
			return false;
		}

		std::string one_line;
		while (std::getline(csv_file, one_line)) {
			// split one lien of csv file to each single word
			auto each_words = String::split(one_line, ',');

			// prepare each one lien of table
			std::vector<Data> one_lien_data;
			Data data_; 
			for (auto&& e : each_words){
				data_.set(e);
				one_lien_data.push_back(data_);
			}

			// set one line to table
			this->table.push_back(one_lien_data);
		}

		return true;
	}

	Data CsvFile::operator()(const unsigned int collumn, const unsigned int raw){
		if (collumn >= this->collumn_size()) {
			std::cout << "[ fanda ERROR ] You try to read over the collumn range of CSV file. collumn size should be under " << this->collumn_size() << std::endl;
			return this->table[0][0];
		}
		else if (raw >= this->raw_size()){
			std::cout << "[ fanda ERROR ] You try to read over the raw range of CSV file. raw size should be under " << this->raw_size() << std::endl;
			return this->table[0][0];
		}
		else {
			return this->table[collumn][raw];
		}
	}

	int CsvFile::collumn_size(){
		return this->table.size();
	}

	int CsvFile::raw_size(){
		return this->table.front().size();
	}

	void CsvFile::print(){

		int counter = 0;
		for (auto&& line : this->table){
			for (auto&& e : line){
				std::cout << "[ " << counter++ << " ] " << e.get_as_string() << " , ";
			}
			std::cout << std::endl;
		}
	}

}

