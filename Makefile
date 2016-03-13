INCLUDES = -I lib

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 ${INCLUDES}

OBJS =		Floor.o Sphere.o Shader.o Triangle.o Particle.o Constraint.o Cloth.o main.o

LIBS =     -lm -lGLEW -lGL -lGLU -lglut

TARGET =	main

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
