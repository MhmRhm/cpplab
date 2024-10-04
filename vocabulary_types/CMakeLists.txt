add_executable(vocabulary_types main.cpp)

target_compile_options(vocabulary_types
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
