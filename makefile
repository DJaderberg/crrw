CXX      = g++
#CFLAGS  = -Wall -Wextra -std=c++11 -Iinclude -I/opt/X11/include/cairo -I/usr/local/Cellar/cairomm/1.10.0_1/lib/cairomm-1.0/include -I/usr/local/Cellar/cairomm/1.10.0_1/include/cairomm-1.0 -I/usr/local/Cellar/libsigc++/2.4.0/include/sigc++-2.0 -I/usr/local/Cellar/libsigc++/2.4.0/lib/sigc++-2.0/include
CFLAGS  = -Wall -Wextra -std=c++11 -Iinclude `pkg-config --cflags --libs cairomm-1.0`
LDFLAGS = `pkg-config --cflags --libs cairomm-1.0`
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
