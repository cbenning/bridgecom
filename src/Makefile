

CC=g++
CFLAGS := -O3 -g -Wall 
LDLIBS := -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lpng -ljpeg 
BIN_OUTPUT := ../bin/
BIN_FILE := bridgecom

all: game.o rtscamera.o
	mkdir -p $(BIN_OUTPUT)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $(BIN_OUTPUT)$(BIN_FILE)
	cp template_runscript.sh ../run.sh
	chmod +x ../run.sh

game.o: game.cpp

rtscamera.o: rtscamera.cpp

clean:
	rm -rf game.o rtscamera.o ../run.sh ../bin
