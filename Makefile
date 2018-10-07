output: main.o
	g++ -g main.o -o slinger

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm *.o slinger