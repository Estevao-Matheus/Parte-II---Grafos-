CC=g++
CFLAGS=-c -std=c++11 -O2 
LDFLAGS=-lm
SOURCES=main.cpp No.cpp Metodo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Solve

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o Solve