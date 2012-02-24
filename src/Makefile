
CC=g++
CFLAGS := -O3 -Wall 
DEBUG_CFLAGS := -g -Wall 
LDLIBS := -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lpng -ljpeg 
BIN_OUTPUT := ../bin/
BIN_FILE := bridgecom

linux64: game.o rtscamera.o ship.o body.o system.o pugixml/pugixml.o event.o ../lib/linux64/libBox2d.a
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

rtscamera.o: rtscamera.cpp

ship.o: ship.cpp

body.o: body.cpp

system.o: system.cpp

pugixml/pugixml.o: pugixml/pugixml.cpp

event.o: event.cpp

#CSceneNodeAnimatorMovableFlyCircle.o: CSceneNodeAnimatorMovableFlyCircle.cpp

clean:
	rm -rf game.o rtscamera.o ship.o body.o system.o pugixml/pugixml.o event.o  ../run.sh ../bin
	#rm -rf game.o rtscamera.o ship.o body.o system.o pugixml/pugixml.o CSceneNodeAnimatorMovableFlyAnimator.o ../run.sh ../bin
