OPTS = -Wall -Wno-write-strings -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

# opengl section
start: start.o texture.o text.o button.o
	g++ $(OPTS) -o start $^ $(LIBS)

start.o: start.cpp start.h button.h globaldefs.h ColorPoint2.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c start.cpp

button.o: button.cpp button.h globaldefs.h ColorPoint2.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c button.cpp

texture.o: texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp

text.o: text.cpp text.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c text.cpp

# makefile parser
target-driver: target-driver.o target.o
	g++ $(OPTS) -o target-driver $^ $(LIBS)

target.o: target.cpp
	g++ $(OPTS) -c target.cpp

target-driver.o: target-driver.cpp
	g++ $(OPTS) -c target-driver.cpp

clean:
	rm -f *.o start
	rm -f target-driver
