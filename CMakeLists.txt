cmake_minimum_required(VERSION 4.0)
project(SimpleCryptograph)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(SimpleCryptograph main.cpp
        Data/UiText.h
        crypto.cpp
        crypto.h
        ArgsParser.cpp
        ArgsParser.h
        ArgsHandler.cpp
        ArgsHandler.h)

target_link_libraries(SimpleCryptograph PRIVATE OpenSSL::SSL OpenSSL::Crypto)