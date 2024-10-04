add_executable(streams main.cpp)

target_compile_options(streams
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)

target_compile_definitions(streams
	PRIVATE FILE_ADDRESS="${CMAKE_CURRENT_SOURCE_DIR}/file.txt"
)
