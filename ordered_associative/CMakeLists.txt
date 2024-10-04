add_executable(ordered_associative main.cpp)

target_compile_options(ordered_associative
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
