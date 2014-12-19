CXX     		= g++-4.9
LD				= g++-4.9
CXX_GRAPHICS 	= g++
LD_GRAPHICS		= g++
CFLAGS_BASE  = -Wall -Wextra -std=c++11 -Iinclude -O3 -Wno-overloaded-virtual
CFLAGS = $(CFLAGS_BASE) -fopenmp  
LDFLAGS_BASE = -O3
LDFLAGS = $(LDFLAGS_BASE) -fopenmp   
OBJECTS = $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.c,bin/%.o,$(wildcard src/*.c))
OBJECTS_GRAPHICS = $(patsubst src/%.cpp,gfx/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.c,gfx/%.o,$(wildcard src/*.c))
all: directories random-walk graphics
VPATH := src:include

graphics: CFLAGS = $(CFLAGS_BASE) -DGRAPHICS $(shell pkg-config --cflags cairomm-1.0 cairo cairomm-png-1.0 cairo-png)
graphics: LDFLAGS = $(LDFLAGS_BASE) -DGRAPHICS $(shell pkg-config --libs cairomm-1.0 cairo cairomm-png-1.0 cairo-png)
graphics: $(OBJECTS_GRAPHICS) directories
	$(LD_GRAPHICS) -o graphics $(OBJECTS_GRAPHICS) $(LDFLAGS)

random-walk: $(OBJECTS) directories
	$(LD) -o random-walk $(OBJECTS) $(LDFLAGS)

bin/%.o: src/%.cpp include/%.h
	$(CXX) -c $(CFLAGS) $< -o $@
gfx/%.o: src/%.cpp include/%.h
	$(CXX_GRAPHICS) -c $(CFLAGS) $< -o $@

directories:
	mkdir -p bin gfx
	

.PHONY: clean cleanest all directories

clean:
	rm bin/*.o gfx/*.o

cleanest: clean
	rm random-walk img/*
