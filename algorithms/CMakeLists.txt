find_package(Threads REQUIRED)
find_package(TBB REQUIRED)

add_executable(algorithms main.cpp)

target_compile_options(algorithms
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)

target_link_libraries(algorithms PRIVATE Threads::Threads)
target_link_libraries(algorithms PRIVATE TBB::tbb)
