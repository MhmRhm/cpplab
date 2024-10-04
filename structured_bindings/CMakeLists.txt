add_executable(structured_bindings main.cpp)

target_compile_options(structured_bindings
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
