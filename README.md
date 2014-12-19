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

## Usage ##

After installation, the binary file ```random-walk``` will have been created. 
This file is used for performing simulations of random walks, but before this 
can be done, you will probably have to create a graph in the correct format, 
see [Graph format](#graph-format).

## Graph format ##

The graph format used by random-walk can be considered as consisting of two 
parts. The first part lists each node and its (2D) position. The second part 
lists connections between two nodes.

More formally each graph file should begin with lines defining all the nodes.
Each such line starts with an integer number (the ID of the node), followed by
two real numbers (x and y position of the node), e.g. ```0 0.75 2.32```. It is 
important to note that the IDs should start at zero and increase by one for 
each line.

After all nodes and positioned have been listed a line containing a single 
```#``` follows, as a marker that the next part of the file is about to begin.

After that each line contains only two node IDs, representing a connection from
the first ID to the second ID, e.g. ```3 14``` Note: You need to specify two 
lines to get a symmetric connection between two nodes.

An example of a small graph file, representing a triangle, is shown below.

	0 0.0 0.0
	1 0.0 0.5
	2 0.25 0.25
	#
	0 1
	1 0
	0 2
	2 0
	1 2
	2 1

### Creating graph files ###

There are a few tools included with the random-walk source code that help with 
generating different graph files.

Consider that there exists a file simple.node, which contains on its first line the number of nodes 
and each following line is the node id followed by the node's x and y position.

A graph can then be created (in test/nodes.txt) using the following command (if dct has been built)
```./findEdges.sh test/simple.node test/nodes.txt```
