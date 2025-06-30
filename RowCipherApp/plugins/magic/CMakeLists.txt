add_library(magic_cipher SHARED
    MagicSquareCipherFactory.cpp
    ../../../Entities/MagicSquareCipher.cpp
    ../../../Entities/MagicSquareUtils.cpp
)

target_include_directories(magic_cipher PRIVATE
    ../../../Entities
    ../../../include
)

set_target_properties(magic_cipher PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/magic
    OUTPUT_NAME "magic"
)
