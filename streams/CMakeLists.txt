add_executable(streams main.cpp)
target_compile_definitions(streams
    PRIVATE FILE_ADDRESS="${CMAKE_CURRENT_SOURCE_DIR}/file.txt")
Format(streams .)
