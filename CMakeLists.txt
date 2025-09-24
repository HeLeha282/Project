cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message(STATUS "Building for Windows")
else()
    message(STATUS "Building for Unix-like system")
endif()


project(scaner)#имя проекта

add_executable(scanner_exe src/testTask.cpp )#имя исполняемого файла




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
target_compile_definitions(scanner_library PRIVATE SCANNER_LIBRARY_EXPORTS)

target_include_directories(scanner_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(scanner_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Находим установленный OpenSSL
find_package(OpenSSL REQUIRED)
# Линкуем OpenSSL с нашей библиотекой
target_link_libraries(scanner_library OpenSSL::Crypto)
target_link_libraries(scanner_exe PRIVATE scanner_library)




add_custom_command(TARGET scanner_exe
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           "${CMAKE_CURRENT_SOURCE_DIR}/src/text.csv"
                           $<TARGET_FILE_DIR:scanner_exe>/text.csv
                   COMMENT "Copying txt file")