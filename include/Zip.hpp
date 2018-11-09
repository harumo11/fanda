#include <iostream>
#include <cstdlib>

namespace Zip {
	void extract_tar(const std::string path);
	void extract_zip(const std::string path);
	void extract_tar_gz(const std::string path);

	void compress_tar(   const std::string from_directory, const std::string to_compress);
	void compress_zip(   const std::string from_directory, const std::string to_compress);
	void compress_tar_gz(const std::string from_directory, const std::string to_compress);
} // namespace Zip
