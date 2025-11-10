cmake_minimum_required(VERSION 4.0)
project(SimpleCryptograph)

set(CMAKE_CXX_STANDARD 20)


find_package(OpenSSL REQUIRED)

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
)
set_target_properties(SimpleCryptograph PROPERTIES OUTPUT_NAME cp)

target_link_libraries(SimpleCryptograph PRIVATE OpenSSL::SSL OpenSSL::Crypto)