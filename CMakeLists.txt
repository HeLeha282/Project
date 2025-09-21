cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR)

project(scaner)#имя проекта

add_executable(scaner src/testTask.cpp)#имя исполняемого файла

add_executable(scaner_library src/Application.cpp src/Database.cpp
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