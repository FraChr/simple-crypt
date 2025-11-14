cmake_minimum_required(VERSION 4.0)
project(SimpleCryptograph)

set(CMAKE_CXX_STANDARD 20)


find_package(OpenSSL REQUIRED)
find_package(Catch2 3 REQUIRED)

add_executable(SimpleCryptograph main.cpp
        Data/UI/UiText.h
        ArgumentHandler/ArgsHandler.cpp
        ArgumentHandler/ArgsHandler.h
        FileHandling/FileHandler.cpp
        FileHandling/FileHandler.h
        POD/File.h
        commands/CommandTypes.h
        commands/Commands.cpp
        commands/Commands.h
        Interfaces/ICommands.h
        Interfaces/IFileHandler.h
        Render/RenderCmd.cpp
        Render/RenderCmd.h
        Data/UI/ErrorText.h
        Logger/Logger.cpp
        Logger/Logger.h
        Interfaces/ILogger.h
        Builder/Builder.cpp
        Builder/Builder.h
        SimpleCrypt.cpp
        SimpleCrypt.h
        huffman/INode.h
        huffman/LeafNode.cpp
        huffman/LeafNode.h
        huffman/InternalNode.cpp
        huffman/InternalNode.h
        huffman/CompareTree.h
        huffman/Tree.h
        huffman/BuildTree.h
)

target_link_libraries(SimpleCryptograph PRIVATE OpenSSL::SSL OpenSSL::Crypto)
set_target_properties(SimpleCryptograph PROPERTIES OUTPUT_NAME cp)



add_executable(SimpleCryptographTests Tests/test.cpp
        Interfaces/IFileHandler.h
        FileHandling/FileHandler.cpp
        FileHandling/FileHandler.h
        Render/RenderCmd.cpp
        Render/RenderCmd.h
        Tests/TestMocks.h
        Logger/Logger.cpp
        Logger/Logger.h
        Interfaces/IFileHandler.h
        Interfaces/ILogger.h
)

target_link_libraries(SimpleCryptographTests PRIVATE
    Catch2::Catch2WithMain
    OpenSSL::SSL
    OpenSSL::Crypto
)

include(CTest)
include(Catch)
catch_discover_tests(SimpleCryptographTests)

