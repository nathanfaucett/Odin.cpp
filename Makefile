CXX = g++
CXXFLAGS = -Wall -std=c++0x
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lGLU

LIB_DIR = -L/usr/lib
INC_DIR = -I/usr/include

SOURCE = main.cpp
EXECUTABLE = build

all:
	make astyle
	make $(EXECUTABLE)

$(EXECUTABLE):
	$(CXX) $(SOURCE) $(LDFLAGS) $(LDLIBS) $(CXXFLAGS) -o a.out

clean:
	@rm -rf $(EXECUTABLE)


ASTYLE_OPTIONS = --style=attach --suffix=none --indent=tab --indent-classes --indent-modifiers --indent-switches --indent-cases --indent-namespaces \
	--indent-labels --indent-col1-comments --break-blocks=all --pad-oper --pad-header \
	--align-pointer=type --align-reference=type --add-brackets
astyle:
	astyle $(ASTYLE_OPTIONS) main.cpp src/odin.hpp src/**/*.h src/**/*.cpp src/**/*.hpp src/core/**/*.h src/core/**/*.cpp src/core/**/*.hpp