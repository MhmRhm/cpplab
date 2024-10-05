add_executable(format_cheatsheet main.cpp)

target_compile_options(format_cheatsheet
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
