#include <iostream>
#include <cstdlib>
#include <vector>

namespace File {
	bool copy(const std::string from, const std::string to);
	bool move(const std::string from, const std::string to);
	bool remove(const std::string path);
	std::vector<std::string> list(const std::string path);
	std::vector<std::string> locate(const std::string file_name);
	bool make_dir(const std::string path);
	std::string current_path();
	std::string who_am_i();
} // namespace File

