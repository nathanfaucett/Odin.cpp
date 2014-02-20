

build:
	g++ -std=c++0x main.cpp

ASTYLE_STYLE = --style=java --style=attach --indent-classes --indent-namespaces -A2
astyle:
	astyle $(ASTYLE_STYLE) **/*.h **/*.cpp odin.h
	$(RM) **/*.orig *.orig
	
clean:
	$(RM) main
	$(RM) **/*.orig

all:
	make build
	make astyle
	make clean
	