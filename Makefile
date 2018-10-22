output: main.o hmc5983.o
	g++ -g main.o mc5983.o -o slinger

main.o: main.cpp
	g++ -c -g main.cpp

hmc5983.o: HMC5983.h HMC5983.cpp
	g++ -c -g main.cpp HMC5983.h HMC5983.cpp

clean:
	rm *.o slinger