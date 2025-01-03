# gh-action-clang19

Test repo for Clang-19 with libc++ on GH action runner for MacOS15 and Ubuntu devcontainer

## Issues

- Ubuntu devcontainer can't install from llvm.org
    ```sh
    $ wget https://apt.llvm.org/llvm.sh -O - | sudo bash -s -- 19 all 
    ...
    + add-apt-repository -y 'deb http://apt.llvm.org/noble/  llvm-toolchain-noble-19 main'
    Repository: 'deb http://apt.llvm.org/noble/ llvm-toolchain-noble-19 main'
    Description:
    Archive for codename: llvm-toolchain-noble-19 components: main
    More info: http://apt.llvm.org/noble/
    Adding repository.
    Found existing deb entry in /etc/apt/sources.list.d/archive_uri-http_apt_llvm_org_noble_-noble.list
    Adding deb entry to /etc/apt/sources.list.d/archive_uri-http_apt_llvm_org_noble_-noble.list
    Found existing deb-src entry in /etc/apt/sources.list.d/archive_uri-http_apt_llvm_org_noble_-noble.list
    Adding disabled deb-src entry to /etc/apt/sources.list.d/archive_uri-http_apt_llvm_org_noble_-noble.list
    Hit:2 http://archive.ubuntu.com/ubuntu noble InRelease                                                                    
    Hit:3 http://archive.ubuntu.com/ubuntu noble-updates InRelease                                                                                    
    Hit:5 https://dl.yarnpkg.com/debian stable InRelease                                                                                              
    Hit:6 http://archive.ubuntu.com/ubuntu noble-backports InRelease                                 
    Hit:7 http://security.ubuntu.com/ubuntu noble-security InRelease           
    Ign:1 https://apt.llvm.org/noble noble-llvm-toolchain-19 InRelease   
    Hit:4 https://apt.llvm.org/noble llvm-toolchain-noble-19 InRelease    
    Err:8 https://apt.llvm.org/noble noble-llvm-toolchain-19 Release      
    404  Not Found [IP: 199.232.194.49 443]
    Reading package lists... Done
    E: The repository 'http://apt.llvm.org/noble noble-llvm-toolchain-19 Release' does not have a Release file.
    N: Updating from such a repository can't be done securely, and is therefore disabled by default.
    N: See apt-secure(8) manpage for repository creation and user configuration details.
    + apt-get update
    Hit:2 http://security.ubuntu.com/ubuntu noble-security InRelease                                                         
    Hit:4 https://dl.yarnpkg.com/debian stable InRelease                                                                                            
    Hit:5 http://archive.ubuntu.com/ubuntu noble InRelease                     
    Ign:1 https://apt.llvm.org/noble noble-llvm-toolchain-19 InRelease   
    Hit:3 https://apt.llvm.org/noble llvm-toolchain-noble-19 InRelease
    Hit:7 http://archive.ubuntu.com/ubuntu noble-updates InRelease
    Err:6 https://apt.llvm.org/noble noble-llvm-toolchain-19 Release
    404  Not Found [IP: 199.232.194.49 443]
    Hit:8 http://archive.ubuntu.com/ubuntu noble-backports InRelease
    Reading package lists... Done
    E: The repository 'http://apt.llvm.org/noble noble-llvm-toolchain-19 Release' does not have a Release file.
    N: Updating from such a repository can't be done securely, and is therefore disabled by default.
    N: See apt-secure(8) manpage for repository creation and user configuration details.
    ```

- On macOS, even I set explicit Include and Linker path at `~/.config/clang` 
    ```sh
    # See note on brew install llvm@19
    -I/opt/homebrew/opt/llvm/include
    -L/opt/homebrew/opt/llvm/lib/c++
    -L/opt/homebrew/opt/llvm/lib/unwind -lunwind
    ```
  and/or `CMakePresets.json`
    ```json
            {
                "name": "settings-stdlib-libc++",
                "description": "Settings to compile and link with libc++",
                "hidden": true,
                "cacheVariables": {
                    "CMAKE_CXX_FLAGS_INIT": "-stdlib=libc++ -I/opt/homebrew/opt/llvm/include",
                    "CMAKE_EXE_LINKER_FLAGS_INIT": "-stdlib=libc++ -L/opt/homebrew/opt/llvm/lib",
                    "CMAKE_SHARED_LINKER_FLAGS_INIT": "-stdlib=libc++ -L/opt/homebrew/opt/llvm/lib"
                }
            },
    ```
   the dylib loaded isn't the one shipped with brew (libc++ shall be version `19000.`)
    ```sh
    $ otool -L .../gh-action-clang19/build/source/Release/gha-clang19
        .../gh-action-clang19/build/source/Release/gha-clang19:
        /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 1800.101.0)
        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1351.0.0)
    ```