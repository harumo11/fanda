cmake_minimum_required(VERSION 3.12)

add_executable(test_file test_file.cpp ../src/File.cpp)
add_executable(test_zip test_zip.cpp ../src/Zip.cpp)
add_executable(test_string test_string.cpp ../src/String.cpp)

