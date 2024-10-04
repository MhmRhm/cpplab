add_executable(multiple_inheritance main.cpp)

target_compile_options(multiple_inheritance
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
