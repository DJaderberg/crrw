CXX      = g++
CFLAGS  = -Wall -Wextra -std=c++11 -Iinclude
LDFLAGS = 
OBJECTS = $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.c,bin/%.o,$(wildcard src/*.c))
all: random-walk
VPATH := src:include

random-walk: $(OBJECTS)
	$(CXX) -o random-walk $^ $(LDFLAGS)

bin/%.o: src/%.cpp include/%.h
	$(CXX) -c $(CFLAGS) $< -o $@

.PHONY: clean cleanest

clean:
	rm bin/*.o

cleanest: clean
	rm random-walk
