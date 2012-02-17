

CC=g++
CFLAGS := -O3 -Wall 
LDLIBS := -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lpng -ljpeg 
BIN_OUTPUT := ../bin/
BIN_FILE := bridgecom

all: game.o rtscamera.o ship.o planet.o libNewton.a 	
	mkdir -p $(BIN_OUTPUT)
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $(BIN_OUTPUT)$(BIN_FILE)
	cp template_runscript.sh ../run.sh
	chmod +x ../run.sh

game.o: game.cpp

rtscamera.o: rtscamera.cpp

ship.o: ship.cpp

planet.o: planet.cpp

clean:
	rm -rf game.o rtscamera.o ship.o planet.o ../run.sh ../bin
