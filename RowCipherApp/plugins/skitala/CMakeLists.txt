add_library(skitala_cipher SHARED
    SkitalaCipherFactory.cpp
    ../../../Entities/SkitalaCipher.cpp
)

target_include_directories(skitala_cipher PRIVATE
    ../../../Entities
    ../../../include
)

set_target_properties(skitala_cipher PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/skitala
    OUTPUT_NAME "skitala"
)
