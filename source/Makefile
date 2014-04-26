OPTS = -Wall -Wno-write-strings -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

start: start.o texture.o text.o button.o
	g++ $(OPTS) -o start $^ $(LIBS)

start.o: start.cpp button.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c start.cpp

texture.o: texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp

button.o: button.cpp button.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c button.cpp

text.o: text.cpp text.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c text.cpp

clean:
	rm -f *.o start
