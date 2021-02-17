all: RUSH.o Text.o Program.o Directory.o DiskManager.o Maker.o UserInterface.o 
	g++ -o RUSH Text.o Program.o Directory.o DiskManager.o Maker.o UserInterface.o RUSH.o 
	make clean	
RUSH.o: RUSH.cpp
	g++ -c RUSH.cpp
Text.o: Text.cpp
	g++ -c Text.cpp
Program.o: Program.cpp
	g++ -c Program.cpp
Directory.o: Directory.cpp
	g++ -c Directory.cpp
DiskManager.o: DiskManager.cpp
	g++ -c DiskManager.cpp
Maker.o: Maker.cpp
	g++ -c Maker.cpp
UserInterface.o: DiskManager.o UserInterface.cpp 
	g++ -c UserInterface.cpp

clean:
	rm *.o
