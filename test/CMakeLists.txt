cmake_minimum_required(VERSION 3.12)

add_executable(test_file test_file.cpp ../src/File.cpp)
add_executable(test_zip test_zip.cpp ../src/Zip.cpp)
add_executable(test_string test_string.cpp ../src/String.cpp)
add_executable(test_tcp_client test_tcp_client.cpp)
add_executable(test_tcp_server test_tcp_server.cpp)

