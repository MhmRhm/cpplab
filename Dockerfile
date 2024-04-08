FROM ubuntu:rolling
LABEL maintainer="rahimi.mhmmd@yahoo.com"

RUN apt-get update && apt-get -y upgrade && apt-get -y install build-essential \
    clang-17 clang-format-17 clang-tidy-17 clang-tools-17 git \
    doxygen graphviz cppcheck valgrind lcov libssl-dev ninja-build libtbb-dev
RUN sudo apt-get -y autoremove cmake || echo "cmake not pre-installed."

WORKDIR /src
RUN git clone --depth=1 --recurse-submodules \
    https://gitlab.kitware.com/cmake/cmake.git
RUN mkdir cmake-build && mkdir cpplab
WORKDIR /src/cmake-build
RUN ../cmake/bootstrap --parallel=$(nproc) && make && make install
# RUN ctest --rerun-failed --output-on-failure
WORKDIR /src
RUN rm -rf cmake-build/ cmake/


COPY . /src/cpplab
WORKDIR /src/cpplab
RUN rm -rf build && cmake -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_COMPILER=/usr/bin/clang-17 \
    -DCMAKE_CXX_COMPILER=/usr/bin/clang++-17 -B build -G Ninja
RUN cmake --build build/ -j $(nproc)

ENTRYPOINT ["/bin/bash"]
