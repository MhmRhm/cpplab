How you can run the code anywhere:
```bash
cd cpplab/
docker build -t cpplab:latest .
docker run -it cpplab:latest
./build/modules/modules
```
Dockerfile used to create the image is basically same as the following section.

How I run the code on Linux:
- Setup an Ubuntu Server 23.10
- Install clang-17
- Build cmake 3.28.0 or above
- Install Ninja

```bash
sudo apt-get install build-essential
sudo apt-get install clang-17 clang-format-17 clang-tidy-17 clang-tools-17
sudo apt-get install doxygen graphviz cppcheck valgrind lcov
sudo apt-get install libssl-dev
sudo apt-get install ninja-build
sudo apt-get install libtbb-dev

sudo apt-get remove cmake
sudo apt-get autoremove

git clone --depth=1 --recurse-submodules https://gitlab.kitware.com/cmake/cmake.git
mkdir cmake-build
cd cmake-build
../cmake/bootstrap --parallel=$(nproc) && make && sudo make install
ctest --rerun-failed --output-on-failure

tree .. -L 1
# .
# ├── cmake
# ├── cmake-build
# └── cpplab

cd ../cpplab
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/clang-17 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-17 -B build -G Ninja
cmake --build build/ -j $(nproc)
./build/modules/modules
```

How I run the code on Windows:
- Install Visual Studio 2022
- Install clang-17 or above and add to path
- Install cmake 3.28.0 or above
- Install Ninja and add to path
- Install Intel's TBB

```bash
cd cpplab/

"C:\Program Files\CMake\bin\cmake.exe" -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE "-DCMAKE_C_COMPILER:FILEPATH=C:\Program Files\LLVM\bin\clang.exe" "-DCMAKE_CXX_COMPILER:FILEPATH=C:\Program Files\LLVM\bin\clang++.exe" -S . -B build "-DCMAKE_MAKE_PROGRAM=C:\Ninja\ninja.exe" -G Ninja

"C:\Program Files\CMake\bin\cmake.exe" --build build
```
