add_executable(sfinae main.cpp sfinae.h)

target_compile_options(sfinae
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
