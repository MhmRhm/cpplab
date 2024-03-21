include(FetchContent)
FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.8.3
)
option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)
option(BENCHMARK_ENABLE_EXCEPTIONS "Enable the use of exceptions in the benchmark library." ON)
option(BENCHMARK_ENABLE_LTO "Enable link time optimisation of the benchmark library." OFF)
option(BENCHMARK_USE_LIBCXX "Build and test using libc++ as the standard library." OFF)
option(BENCHMARK_ENABLE_WERROR "Build Release candidates with -Werror." OFF)
option(BENCHMARK_FORCE_WERROR "Build Release candidates with -Werror regardless of compiler issues." OFF)
option(BENCHMARK_ENABLE_INSTALL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)" OFF)
option(BENCHMARK_ENABLE_DOXYGEN "Build documentation with Doxygen." OFF)
option(BENCHMARK_INSTALL_DOCS "Enable installation of documentation." OFF)
option(BENCHMARK_ENABLE_GTEST_TESTS "Enable building the unit tests which depend on gtest" OFF)
FetchContent_MakeAvailable(googlebenchmark)

macro(AddBenchmarks target)
	target_link_libraries(${target} PRIVATE benchmark::benchmark benchmark::benchmark_main)
endmacro()
