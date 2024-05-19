all : encrypt.o simonr.o encrypt
encrypt.o : encrypt.c simonr.h
	cc -c encrypt.c
speckr.o : simonr.c simonr.h
	cc -c simonr.c
encrypt : encrypt.c
	cc -Wall -o encrypt encrypt.c simonr.o -largon2
clean :
	rm -rf encrypt encrypt.o simonr.o 
