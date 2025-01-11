# gh-action-clang19

Test repo for Clang-19 with libc++ on GH action runner for MacOS15 and Ubuntu devcontainer

## Issues

### Ubuntu devcontainer can't install from llvm.org

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
