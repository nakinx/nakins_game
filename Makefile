CXX=g++
CXXFLAGS=-Wall -g --std=c++14
LDFLAGS=-lncurses

all: intomessage nakins

intomessage:	
	@echo "Initializing compilation..."

nakins: src/main.o src/engine.o src/snake.o src/map.o src/log.o		
		@echo "Creating final executable."
		$(CXX) -o nakins src/main.o src/engine.o src/snake.o src/map.o src/log.o $(LDFLAGS)

clean:
	@echo "Cleaning project..."
	rm -r src/*.o
	rm nakins
