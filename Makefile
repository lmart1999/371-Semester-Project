all: RUFS.o Text.o Program.o Directory.o
	g++ -o RUFS Text.o Program.o Directory.o RUFS.o
	make clean	
RUFS.o: RUFS.cpp
	g++ -c RUFS.cpp
Text.o: Text.cpp
	g++ -c Text.cpp
Program.o: Program.cpp
	g++ -c Program.cpp
Directory.o: Directory.cpp
	g++ -c Directory.cpp
clean:
	rm *.o
