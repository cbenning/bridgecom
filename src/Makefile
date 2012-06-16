
PWD := $(shell pwd)
CC=g++
CFLAGS := -Wall -I.
#CFLAGS := -O3 -Wall -I.
DEBUG_CFLAGS := -g -Wall 
LDLIBS := -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lpng -ljpeg
BIN_OUTPUT := ../bin/
BIN_FILE := bridgecom

linux64: game.o followcamera.o ship.o body.o system.o grid/CGridSceneNode.o pugixml/pugixml.o event.o util.o targets.o ../lib/linux64/libBox2D.a
	mkdir -p $(BIN_OUTPUT)
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $(BIN_OUTPUT)$(BIN_FILE)
	cp template_runscript.sh ../run.sh
	chmod +x ../run.sh

#debug: game.o rtscamera.o ship.o body.o system.o pugixml/pugixml.o event.
#	mkdir -p $(BIN_OUTPUT)
#	$(CC) $^ $(DEBUG_CFLAGS) $(LDLIBS) -o $(BIN_OUTPUT)$(BIN_FILE)
#	cp template_debugscript.sh ../run.sh
#	chmod +x ../run.sh

game.o: game.cpp 
	$(CC) $(CFLAGS) -c game.cpp 

targets.o: targets.cpp 
	$(CC) $(CFLAGS) -c targets.cpp 

followcamera.o: followcamera.cpp
	$(CC) $(CFLAGS) -c followcamera.cpp

ship.o: ship.cpp
	$(CC) $(CFLAGS) -c ship.cpp

util.o: util.cpp
	$(CC) $(CFLAGS) -c util.cpp

body.o: body.cpp
	$(CC) $(CFLAGS) -c body.cpp

system.o: system.cpp
	$(CC) $(CFLAGS) -c system.cpp

event.o: event.cpp
	$(CC) $(CFLAGS) -c event.cpp

pugixml/pugixml.o: pugixml/pugixml.cpp

grid/CGridSceneNode.o: grid/CGridSceneNode.cpp


#CSceneNodeAnimatorMovableFlyCircle.o: CSceneNodeAnimatorMovableFlyCircle.cpp

clean:
	rm -rf *.o ../run.sh ../bin
	#rm -rf game.o rtscamera.o ship.o body.o system.o pugixml/pugixml.o CSceneNodeAnimatorMovableFlyAnimator.o ../run.sh ../bin
