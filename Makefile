all: RATCH.o Text.o Program.o Directory.o Simulator.o DiskManager.o Maker.o UserInterface.o 
	g++ -o RATCH Text.o Program.o Simulator.o Directory.o DiskManager.o Maker.o UserInterface.o RATCH.o 
	make clean	
RATCH.o: RATCH.cpp
	g++ -c RATCH.cpp
Text.o: Text.cpp
	g++ -c Text.cpp
Program.o: Program.cpp
	g++ -c Program.cpp
Directory.o: Directory.cpp
	g++ -c Directory.cpp
Simulator.o: Simulator.cpp
	g++ -c Simulator.cpp
DiskManager.o: DiskManager.cpp
	g++ -c DiskManager.cpp
Maker.o: Maker.cpp
	g++ -c Maker.cpp
UserInterface.o: DiskManager.o UserInterface.cpp 
	g++ -c UserInterface.cpp

clean:
	rm *.o
