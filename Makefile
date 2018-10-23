CC=g++
CFLAGS=-I

slinger: HMC5983.o main.o
	$(CC) -g -o slinger HMC5983.o main.o