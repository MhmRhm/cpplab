How I run the code on Linux:

- Setup an Ubuntu Server 24.04
- Install Clang
- Install Ninja
- Install TBB for `execution::par_unseq`
- Install CMake from [Kitware APT Repository](https://apt.kitware.com)
- Run CMake workflows

```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install clang clang-format clang-tools
sudo apt-get install ninja-build
sudo apt-get install libtbb-dev

# Install CMake from Kitware APT Repository

cmake --workflow --preset linux-default-debug
../cpplab-build-linux-default-debug/modules/modules
```

How I run the code on Windows:

- Install latest [Git](https://git-scm.com/downloads)
- Install latest [CMake](https://cmake.org/download/)
- Install Visual Studio 2022
- Install Clang-format with [LLVM](https://github.com/llvm/llvm-project/releases/tag/llvmorg-18.1.8)
- Install [Intel's TBB](https://www.intel.com/content/www/us/en/developer/articles/tool/oneapi-standalone-components.html#onetbb)

After the installations are completed:

```powershell
cmake --workflow --preset windows-default-debug
..\cpplab-build-windows-default-debug\modules\Debug\modules.exe
```

You can skip installing TBB and LLVM. Just remember to comment out the relevant
lines in the CMakeLists.txt files.
