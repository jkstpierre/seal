# Introduction
The Simple Encryption ALgorithm (SEAL) is a 128-bit symmetric key block cipher that was designed to be fast without
any hardware acceleration. As of August 2017, SEAL is undergoing academic review, and as such is not ready to be used for a
professional application. The implementation released here should only be used for educational purposes.

# Overview
The Simple Encryption ALgorithm permutes a 128-bit block against a 128-bit key. Based off of statistical analysis,
the algorithm possesses both strong avalanche properties and uniformly distributed output. Any change in the bits of either the
key or the plaintext block will result in drastically different cipher-text blocks.

You will notice that the implementation has no error checking or handling whatsoever. This was done in order to maximize the
speed at which the algorithm runs as repeatedly checking for errors for every block processed would unnecessarily harm the
performance of the cipher. It is your responsibility to write code around the usage of SEAL in a manner that protects it
from encountering any errors. The comments within the source files will detail the exact manner in which the cipher is to be used.

You may also notice that the implementation does not provide any mode of operation for SEAL to be used for multi-block
encryption/decryption against the same key. This was omitted as a means of deterrence against using the algorithm
for protecting sensitive data. Once the cipher has completed academic review, standardized implementations for
block cipher modes of operation will be provided here.

In order to use the complementary utilities as well as the tester program, you must have libsodium installed.
You can find libsodium here: https://github.com/jedisct1/libsodium

# Performance
The average rate of encryption for SEAL is 48 MB/s.
This benchmark was taken on a standard laptop using an i7-7500U 2.7 Ghz Quad Core Processor.

# Contact
Name: Joseph St. Pierre

School: Worcester Polytechnic Institute

Email: jkstpierre@wpi.edu

Please contact me if you discover any bugs in the implementation, or any vulnerabilities in the cipher design.
