

CC=g++
CFLAGS := -O3 -g -Wall 
LDLIBS := -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lpng -ljpeg 

all: game.o rtscamera.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION) 

game.o: game.cpp

rtscamera.o: rtscamera.cpp
