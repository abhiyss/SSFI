CC = g++
CPP_FLAGS = -Wall -w -fopenmp -std=c++17 -pthread
FILE = SSFI.cpp Files.cpp Worker.cpp HashTable.cpp FileReader.cpp
EXE = ssfi

build: $(FILE)
	$(CC) $(CPP_FLAGS) -o $(EXE) $(FILE)
clean:
	rm -f *.o *~ $(EXE)
package:
	tar -cvzf SSFI-Abhishek-Yeluri.tar *.cpp *.hpp Makefile README.txt
