# simonr
The first idea of a SimonR cipher based on our enhanced implementation of the SpeckR cipher described in https://link.springer.com/article/10.1007/s11042-020-09625-8

We're doing the same thing but with Simon cipher primitives where we have longer expanded keys.

We managed to produce random output with only 5 rounds, testing with AIS31 tests and STS v3.2.6 from NIST; if resources are very limited use #define SIMONR_ROUNDS 5 in simonr.h file. 186 out of 188 STS randomness tests pass, AIS31 tests pass with flying colors.

