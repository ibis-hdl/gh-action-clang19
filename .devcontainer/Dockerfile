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
       iwyu \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Problem working on ...
#     && add-apt-repository -y 'deb http://apt.llvm.org/noble/   noble-llvm-toolchain-19  main' \
# clang-tools-19 clang-format-19 clang-tidy-19 libc++-19-dev 