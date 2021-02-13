all: RUFS.o Text.o Program.o Directory.o DiskManager.o Maker.o UserInterface.o 
	g++ -o RUFS Text.o Program.o Directory.o DiskManager.o Maker.o UserInterface.o RUFS.o 
	make clean	
RUFS.o: RUFS.cpp
	g++ -c RUFS.cpp
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
