OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
OS := $(shell uname -n)
ifeq ($(ARCH), Linux)
else
MACOSX_DEFINE = -DMACOSX -I/sw/include
LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

ifeq ($(OS), colin)
# for building on Bryan's Machine (64-bit Arch Linux)
FMOD_DIR1 = /usr/include/fmodex
FMOD_DIR2 = /usr/share/doc/fmodex/examples/common
FMOD_INCLUDE = -I$(FMOD_DIR1) -I$(FMOD_DIR2)
FMOD_LIB = /usr/lib/libfmodex64.so
else
# for building on the lab machines, uncomment these
FMOD_DIR = /usr/local/dept/apps/fmod
FMOD_INCLUDE = -I$(FMOD_DIR)/api/inc -I$(FMOD_DIR)/examples/common
FMOD_LIB = $(FMOD_DIR)/api/lib/libfmodex64.so
endif

# opengl section
start: start.o texture.o text.o button.o InstructionLines.o target.o draw.o koala.o date.o physics.o sorcerer.o sound.o
	g++ $(OPTS) -o start $^ $(LIBS) $(FMOD_LIB) 

start.o: start.cpp start.h button.h globaldefs.h ColorPoint2.h InstructionLines.o target.h koala.o text.o date.o sorcerer.o sound.o

	g++ $(OPTS) $(MACOSX_DEFINE) $(FMOD_INCLUDE) -c start.cpp

InstructionLines.o: InstructionLines.cpp InstructionLines.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c InstructionLines.cpp

button.o: button.cpp button.h globaldefs.h ColorPoint2.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c button.cpp

texture.o: texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp

text.o: text.cpp text.h draw.o
	g++ $(OPTS) $(MACOSX_DEFINE) -c text.cpp

draw.o: draw.cpp draw.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c draw.cpp

koala.o: koala.cpp koala.h physics.o
	g++ $(OPTS) $(MACOSX_DEFINE) -c koala.cpp

sorcerer.o: sorcerer.h sorcerer.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c sorcerer.cpp
sound.o: sound.h sound.cpp
	g++ $(OPTS) $(FMOD_INCLUDE) -c sound.cpp


# makefile parser
target-driver: target-driver.o target.o draw.o physics.o
	g++ $(OPTS) -o target-driver $^ $(LIBS)

target.o: target.cpp target.h draw.o physics.o globaldefs.h
	g++ $(OPTS) -c target.cpp

target-driver.o: target-driver.cpp target.h
	g++ $(OPTS) -c target-driver.cpp

# dater
dates: date-driver.o date.o
	g++ $(OPTS) $^ -o date-driver $(LIBS)

date.o: date.cpp date.h
	g++ $(OPTS) -c date.cpp

date-driver.o: date-driver.cpp date.h
	g++ $(OPTS) -c date-driver.cpp

clean:
	rm -f *.o start
	rm -f target-driver
	rm -f date-driver
	rm -f physics-driver

# physics
physics-driver: physics-driver.o physics.o
	g++ $(OPTS) -o physics-driver $^ $(LIBS)

physics.o: physics.cpp physics.h globaldefs.h
	g++ $(OPTS) -c physics.cpp

physics-driver.o: physics-driver.cpp
	g++ $(OPTS) -c physics-driver.cpp
