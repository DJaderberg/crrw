random-walk
===========

Shortest path finder using current reinforced random walks

## Installation ##

Currently, the only option to install random-walk is to build from source, 
which can be done by following the steps listed here.

1. Install a C++ compiler with support for C++11 and OpenMP, such as 
[GCC](https://gcc.gnu.org).
2. Download the source files for random-walk.
3. Navigate to the newly created folder containing the source files.
4. Run the command ```make random-walk```.

If you want to be able to generate graphs of the solutions, also follow
these steps.
	1. Install [Cairomm](http://cairographics.org/cairomm/) 
	with C++11 support and all its dependencies.
	2. Run the command ```. ./configure```. This 
	attempts to add all necessary libraries to the path.
	3. Run the command ```make clean```.
	4. Run the command ```make graphics```, which builds the graphics 
	generating tool.

First run ```. ./configure``` (```. ./configure_fish``` if runnning in the fish shell) then ```make all```

## GRAPH GENERATION ##

Consider that there exists a file simple.node, which contains on its first line the number of nodes 
and each following line is the node id followed by the node's x and y position.

A graph can then be created (in test/nodes.txt) using the following command (if dct has been built)
```./findEdges.sh test/simple.node test/nodes.txt```
