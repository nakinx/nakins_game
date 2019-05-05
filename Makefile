.PHONY := info clean

CXX=g++
CXXFLAGS=-Wall -g --std=c++14
LDFLAGS=-lncurses
MAKEFLAGS+=--no-builtin-rules

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=%.o)

all: info nakins

info: 
	@echo "======Compilation Info======"	
	@echo "Compiler:" $(CXX)
	@echo "Flags:" $(CXXFLAGS)
	@echo "Sources:" $(SRCS)
	@echo "Objects:" $(OBJS)
	@echo "External Librarys:" $(LDFLAGS)
	@echo "============================"

nakins: $(OBJS)
	@echo "======Linking Objects======"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o : %.d
	@echo "====== Creating Object:" $@ "======" 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $(@:.o=.cpp) -o $@	

%.d :
	@echo "====== Creating Dependacy:" $@ "======"
	@$(CXX) $(CXXFLAGS) $(@:.d=.cpp) -MM 
	$(CXX) $(CXXFLAGS) $(@:.d=.cpp) -MM -MF $@

clean:
	@echo "======Cleaning Project======"
	-rm -r src/*.o src/*.d
	-rm -r *.o *.d
	-rm nakins
