add_executable(policy main.cpp policies.h improved_policies.h)

target_compile_options(policy
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
