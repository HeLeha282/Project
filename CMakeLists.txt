cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR)

if(WIN32)
    message(STATUS "Building for Windows")
else()
    message(STATUS "Building for Unix-like system")
endif()


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

#-------------------------------------------------------
##include(FetchContent)

##FetchContent_Declare(
##    CryptoPP
##    GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
##)
##FetchContent_MakeAvailable(CryptoPP)

##target_include_directories(scanner_library PRIVATE ${cryptopp_SOURCE_DIR})
##message(STATUS "CryptoPP source dir: ${cryptopp_SOURCE_DIR}")

##set(CRYPTOPP_LIB_PATH "C:\\Users\\Lesha\\Desktop\\TestTaskKaspersky\\Project\\build\\_deps\\cryptopp-src\\x64\\Output\\Release\\cryptlib.lib")
##target_link_libraries(scanner_library PRIVATE ${CRYPTOPP_LIB_PATH})

#-------------------------------------------------------
include(ExternalProject)

set(CRYPTOPP_INSTALL_DIR ${CMAKE_BINARY_DIR}/third_party/cryptopp)
set(CRYPTOPP_SOURCE_DIR ${CMAKE_BINARY_DIR}/third_party/cryptopp-src)

# Для Windows используем MSBuild вместо make
if(WIN32)
    # Ищем msbuild.exe
    set(PROGRAM_FILES_X86 $ENV{ProgramFiles\(x86\)})

    find_program(MSBUILD_EXE msbuild PATHS
        "$ENV{ProgramFiles}/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin"
        "$ENV{ProgramFiles}/Microsoft Visual Studio/2022/Professional/MSBuild/Current/Bin"
        "$ENV{ProgramFiles}/Microsoft Visual Studio/2022/Enterprise/MSBuild/Current/Bin"
        "${PROGRAM_FILES_X86}/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin"
        "${PROGRAM_FILES_X86}/Microsoft Visual Studio/2019/Professional/MSBuild/Current/Bin"
        "${PROGRAM_FILES_X86}/Microsoft Visual Studio/2019/Enterprise/MSBuild/Current/Bin"
    )

    if(NOT MSBUILD_EXE)
        message(FATAL_ERROR "MSBuild not found. Please ensure Visual Studio is installed.")
    endif()

    ExternalProject_Add(
        cryptopp
        GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
        GIT_TAG CRYPTOPP_8_9_0
        SOURCE_DIR ${CRYPTOPP_SOURCE_DIR}
        CONFIGURE_COMMAND ""
        # Собираем cryptest.sln в конфигурации Release
        BUILD_COMMAND ${MSBUILD_EXE} <SOURCE_DIR>/cryptest.sln
                /p:Configuration=Release
                /p:Platform=x64
        BUILD_IN_SOURCE 1
        # Копируем файлы вручную, так как .sln может не иметь цели install
    )
else()
    message(WARNING "CryptoPP build not configured for non-Windows platforms")
endif()


# После того как проект cryptopp добавлен, мы можем объявить импортированную библиотеку,
# которая указывает на файлы прямо в каталоге сборки (SOURCE_DIR).

#add_library(CryptoPP::CryptoPP SHARED IMPORTED)

# Указываем, где находится скомпилированная библиотека *прямо в каталоге сборки cryptopp*.
#set_target_properties(CryptoPP::CryptoPP PROPERTIES
#    IMPORTED_IMPLIB "${CRYPTOPP_SOURCE_DIR}/x64/Output/Release/cryptopp.lib"
 #   IMPORTED_LOCATION "${CRYPTOPP_SOURCE_DIR}/x64/Output/Release/cryptopp.dll"
#)

# Указываем, где находятся заголовки (include директории) *прямо в исходниках cryptopp*.
#target_include_directories(CryptoPP::CryptoPP INTERFACE "${CRYPTOPP_SOURCE_DIR}")

# Теперь ваша основная программа может использовать target_link_libraries(main CryptoPP::CryptoPP)
#target_link_libraries(scanner_library PRIVATE CryptoPP::CryptoPP)
# и она будет знать, откуда брать и библиотеки, и заголовки.


#-------------------------------------------------------
# Включаем модуль ExternalProject
#include(ExternalProject)

# Устанавливаем путь для установки Crypto++
#set(CRYPTOPP_INSTALL_DIR ${CMAKE_BINARY_DIR}/third_party/cryptopp)

# Правильный хеш для версии CRYPTOPP_8_9_0 (нужно получить актуальный)
#set(CRYPTOPP_SHA256 "a4bc939910edd3e29f819aafaa9f8be5748a2c5f8bdf5a6a6d6a97b3c5a7c0a1")

#ExternalProject_Add(
  #  cryptopp
  ##  GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
 #   GIT_TAG master
 #   CMAKE_ARGS
   #     -DCMAKE_INSTALL_PREFIX=${CRYPTOPP_INSTALL_DIR}
  #      -DBUILD_SHARED=ON
   #     -DBUILD_STATIC=OFF
  #      -DBUILD_TESTING=OFF
   #     -DBUILD_DOCUMENTATION=OFF
  #  BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config Release
  #  INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config Release
#)

# Создаем импортированную цель для использования в проекте
#add_library(CryptoPP::CryptoPP SHARED IMPORTED)

# Устанавливаем свойства библиотеки
#set_target_properties(CryptoPP::CryptoPP PROPERTIES
 #   IMPORTED_LOCATION ${CRYPTOPP_INSTALL_DIR}/lib/cryptopp.dll
 #   IMPORTED_IMPLIB ${CRYPTOPP_INSTALL_DIR}/lib/cryptopp.lib
 #   INTERFACE_INCLUDE_DIRECTORIES ${CRYPTOPP_INSTALL_DIR}/include
#)



