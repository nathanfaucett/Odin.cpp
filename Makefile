

build:
	g++ -std=c++0x main.cpp


ASTYLE_OPTIONS = --style=attach --suffix=none --indent=tab --indent-classes --indent-modifiers --indent-switches --indent-cases --indent-namespaces \
	--indent-labels --indent-col1-comments --break-blocks=all --pad-oper --pad-header \
	--align-pointer=type --align-reference=type --add-brackets
astyle:
	astyle $(ASTYLE_OPTIONS) src/**/*.h src/**/*.cpp src/**/**/*.h src/**/**/*.cpp src/odin.h
	
clean:
	$(RM) a.out

all:
	make build
	make astyle