cmake_minimum_required(VERSION 4.0)
project(SimpleCryptograph)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(SimpleCryptograph main.cpp
        Data/UI/UiText.h
        ArgsHandler.cpp
        ArgsHandler.h
        FileHandling/FileHandler.cpp
        FileHandling/FileHandler.h
        Data/UI/ErrorText.h
        POD/File.h
        commands/CommandTypes.h
        commands/Commands.cpp
        commands/Commands.h)

target_link_libraries(SimpleCryptograph PRIVATE OpenSSL::SSL OpenSSL::Crypto)