CC = g++

LIBS = -lm 
CCFLAGS = -std=c++11 -Wall -ggdb

OBJ = Mot.o tinyxml2.o #1PhraseLigne.o

all: sensPhrase

sensPhrase: main.cpp $(OBJ)
	$(CC) $(CCFLAGS) -o main main.cpp $(OBJ)

#1PhraseLigne.o: 1PhraseLigne.cpp
#	$(CC) $(CCFLAGS) -c 1PhraseLigne.cpp

Mot.o: Mot.cpp
	$(CC) $(CCFLAGS) -c Mot.cpp

tinyxml2.o: tinyxml2.cpp
	$(CC) $(CCFLAGS) -c tinyxml2.cpp

.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f main
