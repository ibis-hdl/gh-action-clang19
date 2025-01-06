# https://github.com/devcontainers/images/tree/main/src/cpp
ARG VARIANT="ubuntu-24.04"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:${VARIANT}

# Install CMake version different from what base image has already installed.
# CMake reinstall choices: none, 3.28.5 etc., or versions from https://cmake.org/download/
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

COPY ./scripts/reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# spell-checker: disable
# `add-apt-repository` command is part of package `software-properties-common`
# devcontainer's cpp is shipped with tools (build-essential cmake, cppcheck, valgrind,
# clang, lldb, llvm, gdb; vcpkg)
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
       software-properties-common \
    && apt-get install -y --no-install-recommends \
       libc++-dev clang-tools clang-format clang-tidy \
       iwyu \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Problem working on, see https://github.com/llvm/llvm-project/issues/121496
#     wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add - \
#     && add-apt-repository -y 'deb http://apt.llvm.org/noble/ llvm-toolchain-noble-19 main' \
# clang-19 lldb-19 lld-19 clang-tools-19 clang-format-19 clang-tidy-19 libc++-19-dev 
# $ wget https://apt.llvm.org/llvm.sh -O - | sudo bash -s -- 19 all 
#    PKG="$PKG clang-tidy-19 clang-format-19 clang-tools-19 llvm-19-dev lld-19 lldb-19 llvm-19-tools libomp-19-dev libc++-19-dev libc++abi-19-dev libclang-common-19-dev libclang-19-dev libclang-cpp19-dev libunwind-19-dev"
# https://askubuntu.com/questions/1286131/how-do-i-install-llvm-10-on-ubuntu-18-04'