
CPP = g++
IDIR = ./include
CPPFLAGS = -std=c++17 -lgtest -lpthread -I $(IDIR)
SRC_DIR = source
INCL_DIR = include
SOURCES = main.cpp unit_tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all unittests triangles *.o
all: main.o triangles.o
	$(CPP) $(CPPFLAGS) main.o triangles.o -o triangles


unittests: triangles.o unit_tests.o
	$(CPP) $(CPPFLAGS) unit_tests.o triangles.o -o unittests

main.o:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/main.cpp -c -o  main.o

unit_tests.o:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/unit_tests.cpp -c -o unit_tests.o

triangles.o:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/triangles.cpp -c -o triangles.o

.PHONY: clean
clean:
	-rm *.o
	-rm triangles
	-rm unittests