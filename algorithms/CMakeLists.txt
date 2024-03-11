find_package(Threads REQUIRED)
find_package(TBB REQUIRED)

add_executable(algorithms main.cpp)

target_link_libraries(algorithms PRIVATE Threads::Threads)
target_link_libraries(algorithms PRIVATE TBB::tbb)
target_compile_options(algorithms PRIVATE "-o3")

Format(algorithms .)
