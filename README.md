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

To be able to partition graphs, which is not strictly necessary, install 
[METIS](http://glaros.dtc.umn.edu/gkhome/views/metis). In particular, the 
stand-alone program ```gpmetis``` should be available.

If you want to be able to generate graphs of the solutions there are few more 
steps.
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

	./random-walk -i graph.txt -o simulation.txt -n 2000 -w 100 -t 0.5 -u 1.05 -p 2

First, the input file is given as an argument, ```-i graph.txt```, then 
the location to store the data in is given, ```-o simulation.txt```. After 
that follows several different parameters for the simulation.
+ ```-n 2000``` the number of time steps/iterations to perform. The simulation
will stop after 2000 iterations.
+ ```-w 100``` The algorithm will write data to ```simulation.txt```every 
100 iterations. Note that the data from the last iteration will always be 
stored in another file where _LAST has been added to the filename before the 
file extension, in this case ```simulation_LAST.txt```.
+ ```-t 0.5``` How large (in time units) each time step is.
+ ```-u 1.05```The value of the non-linearity parameter μ.
+ ```-p 2``` The number of threads to perform the computation with.

Other parameters regarding the simulation can be set by changing the parameters
when constructing the Element, but this currently requires recompiling the 
program after each change.

### graphics ###

The graphics binary has several different modes.

#### Image generation ####

The main mode generates a sequence of images of different states in a 
simulation. An example of thi usage is as follows.

	./graphics -i graph.txt -d simulation.txt -o img/ -n 20 -w 2

+ ```-i graph.txt``` This is the graph file, which should be the same one as 
was used to run the simulation (with ```random-walk```).
+ ```-d simulation.txt``` This is a file containing data from a simulation.
It can also be a ```_LAST``` file.
+ ```-o img/``` This the beginning of name of each image.
+ ```-n 20``` The number of lines to read from the ```-d```file.
+ ```-w 2``` The program will generate an image for every other line that it 
reads from the ```-d``` file.

#### Graph sorting ####

The ```graphics``` binary can be used to partition graphs using 
[METIS](http://glaros.dtc.umn.edu/gkhome/views/metis). The can be done by 
calling the program as below.

	./graphics -i graph.txt -o sorted_graph.txt -m metis.txt -q 8

+ ```-i graph.txt``` This is the input graph file, which is not partitioned 
correctly.
+ ```-o sorted_graph.txt``` This is the output graph file, which is partitioned
using [METIS](http://glaros.dtc.umn.edu/gkhome/views/metis). 
+ ```-m metis.txt``` This is a temporary file which contains the output from 
when ```graphics``` called ```gpmetis```. This file can be discarded after 
running the program.
+ ```-q 8``` The number of partitions that 
[METIS](http://glaros.dtc.umn.edu/gkhome/views/metis) should use for 
partitioning the graph.

## Graph format ##

The graph format used by random-walk can be considered as consisting of two 
parts. The first part lists each node and its (2D) position. The second part 
lists connections between two nodes. There is also an optional way to specify 
a graph partitioning, which is done before everything else.

More formally each graph file can begin with a line defining the graph 
partitioning, if such a partitioning exist. This one line must begin with
```METIS``` followed by ```n+1``` integer numbers, when using ```n```
partitions. Each number specifies the lower (inclusive) or upper (exclusive) 
limit or the partitions. This means that the first number must be ```0``` and 
the last number must be the number of nodes in the file. An example for 
partitioning a graph with 1024 nodes into 4 partitions is 

	METIS: 0 252 509 764 1024

If there is no line describing the partitioning, the file begins with lines 
defining all the nodes; otherwise, the lines describing the nodes begin on 
line two. Each such line starts with an integer number (the ID of the node), 
followed by two real numbers (x and y position of the node), e.g. 
```0 0.75 2.32```. It is important to note that the IDs should start at zero 
and increase by one for each line.

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

## Creating graph files ##

There are a few tools included with the random-walk source code that help with 
generating different graph files.

Consider that there exists a file simple.node, which contains on its first line the number of nodes 
and each following line is the node id followed by the node's x and y position.

A graph can then be created (in test/nodes.txt) using the following command (if dct has been built)
```./findEdges.sh test/simple.node test/nodes.txt```
