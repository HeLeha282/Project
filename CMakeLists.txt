cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message(STATUS "Building for Windows")
else()
    message(STATUS "Building for Unix-like system")
endif()


project(scanner)#имя проекта

add_executable(scanner_exe src/testTask.cpp )#имя исполняемого файла


# GoogleTest подключаю
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(scanner_library SHARED src/Application.cpp src/Database.cpp
src/Report.cpp src/StringUtils.cpp src/Application.h
    src/FileHandler.h
    src/FileHandler.cpp
    src/Database.h
    src/HashCalculator.cpp
    src/Logger.cpp
    src/DirectoryScanner.cpp
    src/HashCalculator.h
    src/DirectoryScanner.h
    src/Logger.h
    src/Report.h
    src/StringUtils.h)


source_group("Header Files" FILES
    src/Application.h
    src/Database.h
    src/HashCalculator.h
    src/DirectoryScanner.h
    src/FileHandler.h
    src/Logger.h
    src/Report.h
    src/StringUtils.h
)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)#делаю макросы в коде Application.h и Report.h 
# Для библиотеки - определяем макрос экспорта
target_compile_definitions(scanner_library PRIVATE SCANNER_LIBRARY_EXPORTS)#добавляет препроцессорный макрос SCANNER_LIBRARY_EXPORTS

target_include_directories(scanner_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)#где искать .h файлы
target_include_directories(scanner_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)#где искать .h файлы


# Находим установленный OpenSSL
find_package(OpenSSL REQUIRED)
# Линкуем OpenSSL с нашей библиотекой
target_link_libraries(scanner_library OpenSSL::Crypto)
target_link_libraries(scanner_exe PRIVATE scanner_library)


# Исполняемый файл для тестов
add_executable(scanner_tests
    tests/test_database.cpp
    tests/test_hash_calculator.cpp
    tests/test_report.cpp
    tests/test_main.cpp  # точка входа для тестов
)



# 1. Подключаем заголовочные файлы
target_include_directories(scanner_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
# 2. ПРАВИЛЬНО линкуем тесты
target_link_libraries(scanner_tests
    scanner_library  # Наша библиотека
    GTest::gtest     # Основная библиотека GTest
    GTest::gtest_main # Библиотека с main() для GTest
    OpenSSL::Crypto   # Если тесты используют хеширование
)


include(GoogleTest)
gtest_discover_tests(scanner_tests)


include(GoogleTest)
gtest_discover_tests(scanner_tests)