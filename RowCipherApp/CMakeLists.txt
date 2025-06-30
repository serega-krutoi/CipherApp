cmake_minimum_required(VERSION 3.12)
project(CipherPlugins)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(plugins/codeword)
add_subdirectory(plugins/skitala)
add_subdirectory(plugins/magic)
add_subdirectory(app)
