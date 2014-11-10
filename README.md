random-walk
===========

Shortest path finder using current reinforced random walks

BUILD:

First run ". ./configure" (". ./configure_fish" if runnning in the fish shell) then "make all"

GRAPH GENERATION:
Consider that there exists a file simple.node, which contains on its first line the number of nodes 
and each following line is the node id followed by the node's x and y position.

A graph can then be created (in test/nodes.txt) using the following command (if dct has been built)
'''./findEdges.sh test/simple.node test/nodes.txt'''
