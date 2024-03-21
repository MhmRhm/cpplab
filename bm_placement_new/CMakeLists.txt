add_executable(bm_placement_new benchmarks.cpp)
Format(bm_placement_new .)
AddBenchmarks(bm_placement_new)
