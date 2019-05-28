LDLIBS = -lglut -lGLEW -lGL -lGLU

.PHONY: clean cleanall

all: maze

maze: $(INIT_SHADER_OBJ)
	g++ -std=c++17 -Wall -g -O3 BaseObject.cpp Wall.cpp Door.cpp Tropy.cpp Path.cpp Camera.cpp World.cpp InitShader.cpp main.cpp $(LDLIBS) -o maze

clean:
	rm maze
