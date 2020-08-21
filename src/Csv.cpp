#include "../include/fanda/Csv.hpp"
#include "../include/fanda/String.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

namespace CSV {

double Data::get_as_double()
{
    return std::stod(this->value);
}

std::string Data::get_as_string()
{
    return this->value;
}

int Data::get_as_int()
{
    return std::stoi(this->value);
}

template <typename T>
void Data::set(const T value)
{
    this->value = std::to_string(value);
}
void Data::set(const std::string value)
{
    this->value = value;
}
void Data::set(const char* value)
{
    std::string value_string = value;
    this->value = value_string;
}

CsvFile::CsvFile()
{
}

CsvFile::CsvFile(const std::string file_path)
{
    // get file path
    this->file_path = file_path;

    // read csv file
    this->reload();
}

bool CsvFile::is_open()
{
    return this->did_open;
}

bool CsvFile::open(const std::string file_path)
{
    // get file path
    this->file_path = file_path;

    // read csv file and return open or not open
    return this->reload();
}

bool CsvFile::reload()
{
    //read csv file with file_path
    std::ifstream csv_file(this->file_path);
    if (!csv_file.is_open()) {
        std::cout << "[ Fanda Error ] CSV file is could not open.\t" << this->file_path << " is realy exist?" << std::endl;
        this->did_open = false;
        return false;
    } else {
        this->did_open = true;
    }

    std::string one_line;
    while (std::getline(csv_file, one_line)) {
        // split one line of csv file to each single word
        auto each_words = String::split(one_line, ',');

        // prepare each one line of table
        std::vector<Data> one_line_data;
        Data data_;
        for (auto&& e : each_words) {
            data_.set(e);
            one_line_data.push_back(data_);
        }

        // add one line to table
        this->table.push_back(one_line_data);
    }

    return true;
}

Data& CsvFile::operator()(const unsigned int row, const unsigned int column)
{
    if (column >= this->column_size()) {
        std::cout << "[ fanda ERROR ] The range over is occured. You tried to read beyond the column range of the CSV file. column index must be under " << this->column_size() << std::endl;
        return this->table[0][0];
    } else if (row >= this->row_size()) {
        std::cout << "[ fanda ERROR ] The range over is occured. You tried to read beyond the row range of CSV file. row index must be under " << this->row_size() << std::endl;
        return this->table[0][0];
    } else {
        return this->table[row][column];
    }
}

int CsvFile::column_size()
{
    return this->table.front().size();
}

int CsvFile::row_size()
{
    return this->table.size();
}

void CsvFile::print()
{
    for (int i = 0; i < this->table.size(); i++) {
        std::cout << "[ " << i << " ] ";
        for (auto e : this->table.at(i)) {
            std::cout << e.get_as_string() << ", ";
        }
        std::cout << std::endl;
        std::cout.flush();
    }
}

void CsvFile::connect(CsvFile another_csv)
{
    this->table.insert(this->table.end(), another_csv.table.begin(), another_csv.table.end());
}

bool CsvFile::add_line(const std::vector<std::string> new_line)
{
    //もし何もデータが入っていなかったとき，与えられたデータを新しく加える．
    //もしくは，新しいデータのサイズが，CsvFileの列数と同じかどうかチェック
    if (this->table.size() == 0 || new_line.size() == this->column_size()) {
        std::vector<CSV::Data> new_line_; //新たに加える１行
        CSV::Data new_data_; //新たに加える１行の１データ
        for (auto& e : new_line) {
            new_data_.set(e); //CSV::Data形式に与えられたデータを変換
            new_line_.push_back(new_data_); //std::vector<CSV::Data>にデータを追加
        }
        this->table.push_back(new_line_); //テーブルに新しい行を追加
        return true;
    } else {
        //新しいデータのサイズがCsvFileの列数と同じでなかったとき
        std::cout << "[Error fanda] in CsvFile::add_line(). added std::vector data size is not same as CsvFile column size. Please check added vector size." << std::endl;
        return false;
    }
}

bool CsvFile::add_line(const std::vector<int> new_line)
{
    //もし何もデータが入っていなかったとき，与えられたデータを新しく加える．
    //もしくは新しいデータのサイズが，CsvFileの列数と同じかどうかチェック
    if (this->table.size() == 0 || new_line.size() == this->column_size()) {
        std::vector<CSV::Data> new_line_; //新たに加える１行
        CSV::Data new_data_; //新たに加える１行の１データ
        for (auto e : new_line) {
            new_data_.set(std::to_string(e));
            new_line_.push_back(new_data_);
        }
        this->table.push_back(new_line_); //テーブルに新しい行を追加
        return true;
    } else {
        //新しいデータのサイズがCsvFileの列数と同じでなかったとき
        std::cout << "[error] in CsvFile::add_line(). added vector data size is not same as CsvFile column size. Please check added vector size." << std::endl;
        return false;
    }
}

bool CsvFile::add_line(const std::vector<double> new_line)
{
    //もし何もデータが入っていなかったとき，与えられたデータを新しく加える．
    //もしくは新しいデータのサイズが，CsvFileの列数と同じかどうかチェック
    if (this->table.size() == 0 || new_line.size() == this->column_size()) {
        std::vector<CSV::Data> new_line_; //新たに加える１行
        CSV::Data new_data_; //新たに加える１行の１データ
        for (auto e : new_line) {
            new_data_.set(std::to_string(e));
            new_line_.push_back(new_data_);
        }
        this->table.push_back(new_line_); //テーブルに新しい行を追加
        return true;
    } else {
        //新しいデータのサイズがCsvFileの列数と同じでなかったとき
        std::cout << "[error] in CsvFile::add_line(). added vector data size is not same as CsvFile row size. Please check added vector size." << std::endl;
        return false;
    }
}

bool CsvFile::save(const std::string file_name)
{
    std::ofstream file_(file_name);
    if (!file_.is_open()) {
        std::cout << "[error] in CsvFile::save(), can't open the file." << std::endl;
        return false;
    } else {
        for (auto&& row : this->table) {
            for (auto&& value : row) {
                file_ << value.get_as_string() << ",";
            }
            file_ << std::endl;
        }
        return true;
    }
}

bool CsvFile::save(const std::string file_name, const std::vector<std::string> header)
{
    std::ofstream file_(file_name);
    if (!file_.is_open()) {
        std::cout << "[error] in CsvFile::save(), can't open the file." << std::endl;
        return false;
    } else {
        for (auto&& e : header) {
            file_ << e << ",";
        }
        file_ << std::endl;

        for (auto&& row : this->table) {
            for (auto&& value : row) {
                file_ << value.get_as_string() << ",";
            }
            file_ << std::endl;
        }
        return true;
    }
}

CsvFile CsvFile::get_random_sampling(const unsigned int sampling_size)
{

    // 乱数の準備
    std::random_device rnd;
    std::mt19937 mt(rnd());
    CsvFile return_csv; //返却用のCsvテーブル

    //condition check
    //sampling_sizeが全体のサイズより小さい場合は，何も入っていないCsvFileを返す
    if (sampling_size > this->row_size()) {
        std::cout << "[Error] in CsvFile::get_random_sampling(). the requested sampling data size is begger than table size. The emplty CsvFile is returned. " << std::endl;
        return return_csv;
    }

    std::uniform_int_distribution<int> dist(0, this->row_size() - sampling_size); //0からテーブルの行数の範囲の乱数を作成する準備
    const unsigned int random_row_index = dist(mt);

    //連続した行を選択する
    for (int i = 0; i < sampling_size; i++) {
        return_csv.table.push_back(this->table.at(random_row_index + i));
    }

    return return_csv;
}

bool CsvFile::remove_line(const unsigned int column_index)
{
    // Check range over. If overd, return false.
    if (column_index > this->row_size()) {
        std::cout << "||| fanda error in CsvFile::remove_line(). You try to remove out of range data" << std::endl;
        std::cout << "||| You tried to remove " << column_index << "th data, but there are only " << this->row_size() << " pieces of data" << std::endl;
        return false;
    }
    // Remove data with colmn_index
    this->table.erase(this->table.begin() + column_index);
    return true;
}
}
