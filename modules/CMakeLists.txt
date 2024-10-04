add_executable(modules translation_unit.cpp main.cpp)

target_compile_options(modules
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)

target_sources(modules
	PUBLIC
		FILE_SET CXX_MODULES FILES
			tlp.cppm
)
