COMPILE_FLAG = -Wall -Wextra -pedantic -ansi -g
OTHER = -std=c++14
SOURCES = Main.cpp Options.cpp HandleFiles.cpp Loading.cpp Utilities.cpp GrowingTree.cpp GeneratePrim.cpp GenerateRecursive.cpp MazeRouting.cpp
HEADERS = Main.h Options.h HandleFiles.h Loading.h Utilities.h GrowingTree.h GeneratePrim.h GenerateRecursive.h MazeRouting.h cell.h CustomSet.h CustomTemplateSet.h
OBJS = Main.o Options.o HandleFiles.o Loading.o Utilities.o GrowingTree.o GeneratePrim.o GenerateRecursive.o MazeRouting.o
PROG = mazer
CC = g++
	
	
all : $(PROG)
	$(CC) $(OBJS) $(HELPER) $(COMPILE_FLAG) $(OTHER) -o $(PROG)
	
$(PROG): $(OBJS)
	$(CC) $(COMPILE_FLAGS) $(OTHER) $(OBJS) -o $(PROG)
	
Main.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) Main.cpp
	
Options.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) Options.cpp
	
HandleFiles.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) HandleFiles.cpp

Loading.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) Loading.cpp

Utilities.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) Utilities.cpp
	
GrowingTree.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) GrowingTree.cpp
	
GeneratePrim.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) GeneratePrim.cpp
	
GenerateRecursive.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) GenerateRecursive.cpp
	
MazeRouting.o: $(HEADERS)
	$(CC) -c $(COMPILE_FLAG) $(OTHER) MazeRouting.cpp
	
clean :
	rm *.maze *.svg *.o $(PROG)
