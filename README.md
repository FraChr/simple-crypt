# Simple Cryptograph

## Description:
SimpleCryptograph is a terminal-based program for encrypting and decrypting individual files.  
It uses the OpenSSl cryptographic library.  

### Features:
* Encrypts and decrypts files using a password
* Uses OpenSSL for cryptographic operations
* Simple command-line interface for file encryption/decryption

## Dependancies
* CMake: version 4.0 or higher
* Compiler:
    * GCC 15.2 or heigher
* Libraries:
    * OpenSSL 3.6 or higher

## Build Instructions:
Open cmd / terminal in wanted directory  
  

Clone Repository:
```
git https://github.com/FraChr/simple-crypt.git
```
```
cd SimpleCryptograph
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
./SimpleCryptograph -h
```