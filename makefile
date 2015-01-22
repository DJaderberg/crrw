CXX     		= g++-4.9
LD				= g++-4.9
CXX_GRAPHICS 	= g++-4.9
LD_GRAPHICS		= g++-4.9
CFLAGS_BASE  = -Wall -Wextra -std=c++11 -Isrc/include -O3 -Wno-overloaded-virtual
CFLAGS = $(CFLAGS_BASE) -fopenmp  
LDFLAGS_BASE = -O3
LDFLAGS = $(LDFLAGS_BASE) -fopenmp   
OBJECTS = $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.c,bin/%.o,$(wildcard src/*.c))
OBJECTS_GRAPHICS = $(patsubst src/%.cpp,bin/gfx/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.c,bin/gfx/%.o,$(wildcard src/*.c))
all: directories crrw graphics
VPATH := src:src/include

graphics: CFLAGS = $(CFLAGS_BASE) -DGRAPHICS $(shell pkg-config --cflags cairomm-1.0 cairo cairomm-png-1.0 cairo-png)
graphics: LDFLAGS = $(LDFLAGS_BASE) -DGRAPHICS $(shell pkg-config --libs cairomm-1.0 cairo cairomm-png-1.0 cairo-png)
graphics: $(OBJECTS_GRAPHICS) directories
	$(LD_GRAPHICS) -o graphics $(OBJECTS_GRAPHICS) $(LDFLAGS)

crrw: directories $(OBJECTS)
	$(LD) -o crrw $(OBJECTS) $(LDFLAGS)

bin/%.o: src/%.cpp src/include/%.h
	$(CXX) -c $(CFLAGS) $< -o $@
bin/gfx/%.o: src/%.cpp src/include/%.h
	$(CXX_GRAPHICS) -c $(CFLAGS) $< -o $@

directories:
	mkdir -p bin bin/gfx output output/images

documentation: docs

docs: $(wildcard src/*.cpp) $(wildcard src/include/*.h) README.md .Doxyfile
	doxygen .Doxyfile

.PHONY: clean cleanest all directories

clean:
	rm bin/*.o bin/gfx/*.o

cleanest: clean
	rm crrw graphics
