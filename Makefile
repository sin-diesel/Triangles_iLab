.PHONY: all
all:
	g++ -std=c++11 -Wall -I ./include/ ./source/main.cpp ./source/triangles.cpp -o triangles
	