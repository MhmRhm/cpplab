add_executable(type_erasure main.cpp type_erasure.h)

target_compile_options(type_erasure
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
