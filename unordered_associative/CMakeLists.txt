add_executable(unordered_associative main.cpp)

target_compile_options(unordered_associative
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
