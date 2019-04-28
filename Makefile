CXX=g++
CXXFLAGS=-Wall -g --std=c++14
LDFLAGS=-lncurses

OBJS=	src/main.o \
		src/engine.o \
		src/snake.o \
		src/map.o \
		src/log.o \

all: intomessage nakins

intomessage:	
	@echo "Initializing compilation..."

nakins: $(OBJS)
		@echo "Creating final executable."
		$(CXX) -o nakins $(OBJS) $(LDFLAGS)

clean:
	@echo "Cleaning project..."
	rm -r src/*.o
	rm nakins
