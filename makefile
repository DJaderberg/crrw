CXX     = g++-4.9
LD		= g++-4.9
CFLAGS_BASE  = -Wall -Wextra -std=c++11 -Iinclude -fopenmp
CFLAGS = $(CFLAGS_BASE) 
LDFLAGS_BASE = -fopenmp
LDFLAGS = $(LDFLAGS_BASE) 
OBJECTS = $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.c,bin/%.o,$(wildcard src/*.c))
all: random-walk
allest: graphics
VPATH := src:include

graphics: CFLAGS = $(CFLAGS_BASE)-DGRAPHICS $(shell pkg-config --cflags cairomm-1.0 cairo cairomm-png-1.0 cairo-png)
graphics: LDFLAGS = $(LDFLAGS_BASE)-DGRAPHICS $(shell pkg-config --libs cairomm-1.0 cairo cairomm-png-1.0 cairo-png)
graphics: $(OBJECTS) 
	$(LD) -o random-walk $^ $(LDFLAGS)

random-walk: $(OBJECTS)
	$(LD) -o random-walk $^ $(LDFLAGS)

bin/%.o: src/%.cpp include/%.h
	$(CXX) -c $(CFLAGS) $< -o $@

.PHONY: clean cleanest

clean:
	rm bin/*.o

cleanest: clean
	rm random-walk img/*
