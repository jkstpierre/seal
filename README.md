# Introduction
The Simple Encryption ALgorithm (SEAL) is a 128-bit symmetric key block cipher that was designed to be fast without
any hardware acceleration. As of August 2017, SEAL is undergoing academic review, and as such is not ready to be used for a
professional application. The implementation released here should only be used for educational purposes.

#Overview
The Simple Encryption ALgorithm permutes a 128-bit block against a 128-bit key. Based off of statistical analysis,
the algorithm possesses both strong avalanche properties and uniformly distributed output. Any change in the bits of either the
key or the plaintext block will result in drastically different cipher-text blocks. 
