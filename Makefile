
output: mainB.o betris.o 
	g++ mainB.o betris.o -o output
	

mainB.o: mainB.cpp
	g++ -c mainB.cpp

betris.o: betris.cpp betris.hpp
	g++ -c betris.cpp

clean: 
	rm *.o output