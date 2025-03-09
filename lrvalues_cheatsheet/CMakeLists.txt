add_executable(lrvalues_cheatsheet main.cpp)

target_compile_options(lrvalues_cheatsheet
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
