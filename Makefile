CC=g++
CFLAGS=-I -g

slinger: HMC5983.o main.o
	$(CC) -o slinger HMC5983.o main.o -g -std=c++11