add_executable(expression_templates main.cpp modified_vector.h)

target_compile_options(expression_templates
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
