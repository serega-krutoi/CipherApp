cmake_minimum_required(VERSION 3.16)

project(CipherAppApp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    LoginDialog.cpp
    LoginDialog.h
    LoginDialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CipherApp ${SOURCES})
else()
    add_executable(CipherApp ${SOURCES})
endif()

target_include_directories(CipherApp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(CipherApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_custom_command(TARGET CipherApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:CipherApp>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/plugins/codeword/libcodeword.so
        ${CMAKE_BINARY_DIR}/plugins/magic/libmagic.so
        ${CMAKE_BINARY_DIR}/plugins/skitala/libskitala.so
        $<TARGET_FILE_DIR:CipherApp>/plugins
    COMMENT "Копирование плагинов в папку plugins/"
)
