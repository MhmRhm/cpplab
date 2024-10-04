add_executable(explicit_instantiation main.cpp)

target_compile_options(explicit_instantiation
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
