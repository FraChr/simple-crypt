# Simple Cryptograph

## Description:

SimpleCryptograph is a terminal-based program for encrypting and decrypting individual files.  
It uses the OpenSSl cryptographic library. 

windows build using msys2 mingw

### Features:

* Encrypts and decrypts files using a password
* Uses OpenSSL for cryptographic operations
* Simple command-line interface for file encryption/decryption

## Dependencies

* CMake: version 4.0 or higher
* Compiler:
    * GCC 15.2 or heigher
* Libraries:
    * OpenSSL 3.6 or higher

## Build Instructions Windows:
### Get dependencies

download and install msys2 https://www.msys2.org/

using msys2 mingw 64 shell

update:
```
pacman -Syu
```
install dependencies

gcc compiler:
```
pacman -S mingw-w64-x86_64-gcc
```

OpenSSl:
```
pacman -S mingw-w64-x86_64-openssl
```

Cmake:
```
pacman -S mingw-w64-x86_64-cmake
```

git:
```
pacman -S git
```

open msys2 mingw64 in wanted directory

Clone Repository:

```
git clone https://github.com/FraChr/simple-crypt.git
```

```
cd simple-crypt
```

Clone Repository:

```
git clone https://github.com/FraChr/simple-crypt.git
```

```
cd simple-crypt
```

Run CMake to configure the build system:
```
cmake ..
```

makefile:
```
pacman -S ninja
```
```
make
```

build.ninja:
```
pacman -S make
```  
```
ninja
```



Run the program

```
./crypt -h
```

## Build Instructions Linux:

terminal in wanted directory

Clone Repository:

```
git clone https://github.com/FraChr/simple-crypt.git
```

```
cd simple-crypt
```

Create a build directory:

```
mkdir build
```

```
cd build
```

Run CMake to configure the build system:

```
cmake ..
```

```
make
```

Run the program

```
./crypt -h
```