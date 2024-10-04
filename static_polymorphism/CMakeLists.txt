add_executable(static_polymorphism main.cpp crtp.h)

target_compile_options(static_polymorphism
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
