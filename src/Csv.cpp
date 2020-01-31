#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
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

	bool CsvFile::is_open(){
		return this->did_open;
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
		else {
			this->did_open = true;
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

	//FIXME ,, となって歯抜けになることがある．実際は歯抜けになっていない
	void CsvFile::print(){
		for (int i = 0; i < this->table.size(); i++) {
			std::cout << "[ " << i << " ] ";
			for (auto e : this->table.at(i)){
				std::cout << e.get_as_string() << ", ";
			}
			std::cout << std::endl;
		}
	}

	void CsvFile::connect(CsvFile another_csv_file){
		this->table.insert(this->table.end(), another_csv_file.table.begin(), another_csv_file.table.end());
	}

	void CsvFile::add(const std::vector<std::string> new_line){
		//もし何もデータが入っていなかったとき，与えられたデータを新しく加える．
		//もしくは，新しいデータのサイズが，CsvFileの列数と同じかどうかチェック
		if (this->collumn_size() == 0 || new_line.size() == this->raw_size()) {
			std::vector<CSV::Data> new_line_;	//新たに加える１行
			CSV::Data new_data_;				//新たに加える１行の１データ
			for (auto e : new_line){
				new_data_.set(e);	//CSV::Data形式に与えられたデータを変換
				new_line_.push_back(new_data_);	//std::vector<CSV::Data>にデータを追加
			}
			this->table.push_back(new_line_);	//テーブルに新しい行を追加
		}
		else {
			//新しいデータのサイズがCsvFileの列数と同じでなかったとき
			std::cout << "[error] in CsvFile::add(). added vector data size is not same as CsvFile raw size. Please check added vector size." << std::endl;
		}
	}

	void CsvFile::add(const std::vector<double> new_line){
		//もし何もデータが入っていなかったとき，与えられたデータを新しく加える．
		//もしくは新しいデータのサイズが，CsvFileの列数と同じかどうかチェック
		if (this->collumn_size() == 0 || new_line.size() == this->raw_size()) {
			std::vector<CSV::Data> new_line_;	//新たに加える１行
			CSV::Data new_data_;				//新たに加える１行の１データ
			for (auto e : new_line){
				new_data_.set(std::to_string(e));
				new_line_.push_back(new_data_);
			}
			this->table.push_back(new_line_);	//テーブルに新しい行を追加
		}
		else {
			//新しいデータのサイズがCsvFileの列数と同じでなかったとき
			std::cout << "[error] in CsvFile::add(). added vector data size is not same as CsvFile raw size. Please check added vector size." << std::endl;
		}
	}

	void CsvFile::add(const std::vector<int> new_line){
		//もし何もデータが入っていなかったとき，与えられたデータを新しく加える．
		//もしくは新しいデータのサイズが，CsvFileの列数と同じかどうかチェック
		if (this->collumn_size() == 0 || new_line.size() == this->raw_size()) {
			std::vector<CSV::Data> new_line_;	//新たに加える１行
			CSV::Data new_data_;				//新たに加える１行の１データ
			for (auto e : new_line){
				new_data_.set(std::to_string(e));
				new_line_.push_back(new_data_);
			}
			this->table.push_back(new_line_);	//テーブルに新しい行を追加
		}
		else {
			//新しいデータのサイズがCsvFileの列数と同じでなかったとき
			std::cout << "[error] in CsvFile::add(). added vector data size is not same as CsvFile raw size. Please check added vector size." << std::endl;
		}
	}


	CsvFile CsvFile::get_random_sampling(const unsigned int sampling_size){
		// 乱数の準備
		std::random_device rnd;
		std::mt19937 mt(rnd());
		std::uniform_int_distribution<int> dist(0, this->collumn_size()-1);	//0からテーブルの行数の範囲の乱数を作成する準備

		CsvFile new_csv;	//返却用のCsvテーブル
		for (int i = 0; i < sampling_size; i++) {
			//乱数を生成
			const int random_itr = dist(mt);
			new_csv.table.push_back(this->table.at(random_itr));
		}

		return new_csv;
	}
}

