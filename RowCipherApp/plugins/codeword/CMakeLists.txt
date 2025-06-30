add_library(codeword_cipher SHARED
    CodeWordCipherFactory.cpp
    ../../../Entities/CodeWordCipher.cpp
)

target_include_directories(codeword_cipher PRIVATE
    ../../../Entities
    ../../../include
)

set_target_properties(codeword_cipher PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/codeword
    OUTPUT_NAME "codeword"
)
