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
4. If you do not need support for generating graphics, simply run the command 
```make random-walk```. Otherwise, follow the steps below.

If you want to be able to generate graphs of the solutions there are few more 
steps, which are listed below.
1. Install [Cairomm](http://cairographics.org/cairomm/) 
with C++11 support and all its dependencies.
2. Run the command ```. ./configure```. This 
attempts to add all necessary libraries to the path.
3. Run the command ```make clean```.
4. Run the command ```make all```, which builds the graphics 
generating tool as well as the computation tool.

## Usage ##

The installation may create two different binary files (depending on if it's 
build with graphic capabilities or not), which have different usage.

### random-walk ###

After installation, the binary file ```random-walk``` will have been created. 
This file is used for performing simulations of random walks, but before this 
can be done, you will probably have to create a graph in the correct format, 
see [Graph format](#graph-format).

A description of how to use the ```random-walk``` binary can be found by 
running ```./random-walk -h```. Here, an example is shown and explained.

	./random-walk -i graph.txt -o simulation.txt -n 2000 -w 1000 -t 0.5 -u 1.05 -p 2

First, the input file is given as an argument, ```-i graph.txt```, then 
the location to store the data in is given, ```-o simulation.txt```. After 
that follows several different parameters for the simulation.
+ ```-n 2000``` the number of time steps/iterations to perform. The simulation
will stop after 2000 iterations.
+ ```-w 1000``` The algorithm will write data to ```simulation.txt```every 
1000 iterations. Note that the data from the last iteration will always be 
stored in another file where _LAST has been added to the filename before the 
file extension, in this case ```simulation_LAST.txt```.
+ ```-t 0.5``` How large (in time units) each time step is.
+ ```-u 1.05```The value of the non-linearity parameter μ.
+ ```-p 2``` The number of threads to perform the computation with.

Other parameters regarding the simulation can be set by changing the parameters
when constructing the Element, but this currently requires recompiling the 
program after each change.

### graphics ###

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
