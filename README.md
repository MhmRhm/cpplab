How I run the code:
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

sudo apt-get remove cmake
sudo apt-get autoremove

tar -xvpf cmake-3.28.3.tar.gz
cd cmake-3.28.3/
mkdir build
cd build/

../configure
gmake -j $(nproc)
sudo gmake install
ctest --rerun-failed --output-on-failure

tree . -L 1
# .
# ├── cmake-3.28.3
# └── cpplab

cd ../../cpplab
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/clang-17 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-17 -B build -G Ninja
cmake --build build/ -j $(nproc)
./build/modules/modules
```
