add_executable(bm_placement_new benchmarks.cpp)

target_compile_options(bm_placement_new
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)

AddBenchmarks(bm_placement_new)
