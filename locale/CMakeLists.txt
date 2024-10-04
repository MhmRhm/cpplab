add_executable(locale main.cpp comma_separator.h)

target_compile_options(locale
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
