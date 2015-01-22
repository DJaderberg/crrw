crrw
===========

Shortest path finder using current reinforced random walks

## Installation ##

Currently, the only option to install crrw is to build from source, 
which can be done by following the steps listed here.

1. Install a C++ compiler with support for C++11 and OpenMP, such as 
[GCC](https://gcc.gnu.org).
2. Download the source files for crrw.
3. Navigate to the newly created folder containing the source files.
4. Run the command ```make crrw```.

To be able to partition graphs, which is not strictly necessary, install 
[METIS](http://glaros.dtc.umn.edu/gkhome/views/metis). In particular, the 
stand-alone program ```gpmetis``` should be available.

If you want to be able to generate graphs of the solutions there are few more 
steps.
1. Install [Cairomm](http://cairographics.org/cairomm/) 
with C++11 support and all its dependencies.
2. Run the command ```. src/configure```. This 
attempts to add all necessary libraries to the path.
3. Run the command ```make clean```.
4. Run the command ```make all```, which builds the graphics 
generating tool as well as the computation tool.

## Usage ##

The installation may create two different binary files (depending on if it's 
build with graphic capabilities or not), which have different usage.

### crrw ###

After installation, the binary file ```crrw``` will have been created. 
This file is used for performing simulations of random walks, but before this 
can be done, you will probably have to create a graph in the correct format, 
see [Graph format](#graph-format).

A description of how to use the ```crrw``` binary can be found by 
running ```./crrw -h```. Here, an example is shown and explained.

	./crrw -i input/graph/lattice_example.txt -o output/result.txt -n 2000 -w 100 -t 0.5 -p 2 -e input/parameters/parameters_example.txt

First, the input file is given as an argument, ```-i input/graph/lattice_example.txt```, then 
the location to store the data in is given, ```-o output/result.txt```. After 
that follows several different parameters for the simulation.
+ ```-n 2000``` the number of time steps/iterations to perform. The simulation
will stop after 2000 iterations.
+ ```-w 100``` The algorithm will write data to ```output/result.txt```every 
100 iterations. Note that the data from the last iteration will always be 
stored in another file where _LAST has been added to the filename before the 
file extension, in this case ```simulation_LAST.txt```.
+ ```-t 0.5``` How large (in time units) each time step is.
+ ```-p 2``` The number of threads to perform the computation with.
+ ```-e input/parameters/parameters_example.txt``` The file to read parameter values from, format 
specified below.

#### Parameter file format ####

This format consists of a single line specifying 4 parameters. The order is

	q lambda mu Dmin

So an example file is

	0.0001 0.001 1.0 0.05

#### Output file format ####

The output file format can seem quite complicatied, but is relatively simple 
for a computer to parse. From a large scale perspective, the file contains 
data for each node separated by a ```|```. Each node data is then started by 
listing the number of particles in the node, followed by a semicolon. After 
this, all the neighbors of the node and the conductivity and mean flow to that 
neighbor is listed, all neighbors are separated by a semicolon. Such a whole 
line represents one stored time step in the file. If there are more lines, 
they represent other, later, time steps.

An example of what one node may be described as is

	12; 1 0.05 0.24; 2 0.07 0.34

This would mean that the node contains ```12``` particles. And on the edge to 
the node with ID ```1```, the conductivity is ```0.05``` and the mean flow is 
```0.24```. On the edge to the node with ID ```2```, the conductivity is 
```0.07``` and the mean flow is ```0.34```.

An example of a whole file could be 

	12; 1 0.05 0.24; 2 0.07 0.34|4; 0 0.03 0|6; 0 0.06 0
	10; 1 0.06 0.29; 2 0.08 0.39|5; 0 0.03 0|7; 0 0.06 0

This would be a file containing three nodes, where the first node has ```12``` 
particles and the others have ```4``` and ```5```, in the first time step. 
In the second time step two particles have moved from the first node to the 
others, increasing the conductivity and mean flow along the edges from the 
first node to the others.

NOTE: This format implicitly numbers the nodes by the order that they appear 
in the file. The first node has ID 0, the second ID 1 and so on.


### graphics ###

The graphics binary has several different modes.

#### Image generation ####

The main mode generates a sequence of images of different states in a 
simulation. An example of thi usage is as follows.

	./graphics -i input/graph/lattice_example.txt -d output/result.txt -o img/ -n 20 -w 2

+ ```-i input/graph/lattice_example.txt``` This is the graph file, which should be the same one as 
was used to run the simulation (with ```crrw```).
+ ```-d output/result.txt``` This is a file containing data from a simulation.
It can also be a ```_LAST``` file.
+ ```-o img/``` This the beginning of name of each image.
+ ```-n 20``` The number of lines to read from the ```-d```file.
+ ```-w 2``` The program will generate an image for every other line that it 
reads from the ```-d``` file.

#### Graph sorting ####

The ```graphics``` binary can be used to partition graphs using 
[METIS](http://glaros.dtc.umn.edu/gkhome/views/metis). The can be done by 
calling the program as below.

	./graphics -i input/graph/lattice_example.txt -o input/graph/sorted_lattice_example.txt -m output/metis.txt -q 8

+ ```-i input/graph/lattice_example.txt``` This is the input graph file, which is not partitioned 
correctly.
+ ```-o input/graph/sorted_lattice_example.txt``` This is the output graph file, which is partitioned
using [METIS](http://glaros.dtc.umn.edu/gkhome/views/metis). 
+ ```-m output/metis.txt``` This is a temporary file which contains the output from 
when ```graphics``` called ```gpmetis```. This file can be discarded after 
running the program.
+ ```-q 8``` The number of partitions that 
[METIS](http://glaros.dtc.umn.edu/gkhome/views/metis) should use for 
partitioning the graph.

## Graph format ##

The graph format used by crrw can be considered as consisting of two 
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

There are a few tools included with the crrw source code that help with 
generating different graph files.

### Road data ###

It is possible to input data from OpenStreetMap and convert it to the graph 
format that can be handled by ```crrw```. This is done by using the 
script ```osm2tgf.sh```located in the folder ```data/osm```. This script has a 
few dependencies. First of all, ```python``` must be installed, since it makes 
use of the ```python``` script ``nodesFromWays.py``` (located in the same 
folder). Furthermore, there are two OSM specific tools that need to be 
available, the script ```osmconvert```, found 
[here](http://wiki.openstreetmap.org/wiki/Osmconvert), which must be placed in 
the same folder as the ```osm2tgf.sh``` script. Furthermore, Osmosis tool, 
found [here](http://wiki.openstreetmap.org/wiki/Osmosis), must be installed.

When all those depenencies are fulfilled, the script can be run with

	./osm2tgf osm_database.pbf graph.txt

Please note that the input file must be in the PBF format that Osmosis handles.

## Generating documentation ##

To generate the documentation, make sure that you have 
[Doxygen](http://www.doxygen.org) installed and then run

	make docs

After this you can open the file ```documentation/html/index.html``` in a web 
browser to read the documentation.
