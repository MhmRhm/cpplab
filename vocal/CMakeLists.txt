add_executable(vocal main.cpp inner_outer.h)

target_compile_options(vocal
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
