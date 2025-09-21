cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR)



project(scaner)#имя проекта

add_executable(scanner_exe src/testTask.cpp)#имя исполняемого файла

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(scanner_library SHARED src/Application.cpp src/Database.cpp
src/Report.cpp src/StringUtils.cpp src/Application.h
    src/Database.h
    src/HashCalculator.cpp
    src/Logger.cpp
    src/FileScanner.cpp
    src/HashCalculator.h
    src/FileScanner.h
    src/Logger.h
    src/Report.h
    src/StringUtils.h)


source_group("Header Files" FILES
    src/Application.h
    src/Database.h
    src/HashCalculator.h
    src/FileScanner.h
    src/Logger.h
    src/Report.h
    src/StringUtils.h
)

target_link_libraries(scanner_exe PRIVATE scanner_library)


include(FetchContent)

FetchContent_Declare(
    CryptoPP
    GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
)
FetchContent_MakeAvailable(CryptoPP)

target_include_directories(scanner_library PRIVATE ${cryptopp_SOURCE_DIR})
message(STATUS "CryptoPP source dir: ${cryptopp_SOURCE_DIR}")

set(CRYPTOPP_LIB_PATH "C:\\Users\\Lesha\\Desktop\\TestTaskKaspersky\\Project\\build\\_deps\\cryptopp-src\\x64\\Output\\Release\\cryptlib.lib")
target_link_libraries(scanner_library PRIVATE ${CRYPTOPP_LIB_PATH})
