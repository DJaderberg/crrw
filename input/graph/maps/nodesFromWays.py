import xml.etree.ElementTree as ET
import csv
import sys
from subprocess import call
# Default values for storing files

# Tree file is a file containing only OSM ways, in XML.
tree_file = "roads.osm"
# Contains all nodes in the format "@id @lon @lat"
csv_file = "nodes_space.csv"
temp_output_file = '.tmp'
# Overwrite default values
if len(sys.argv) > 1:
    tree_file = sys.argv[1]
if len(sys.argv) > 2:
    csv_file = sys.argv[2]
if len(sys.argv) > 2:
    temp_output_file = sys.argv[3]


tree = ET.parse(tree_file)

root = tree.getroot()

i = 0
# Keep track of ids of all nodes that are in the ways
id_dict = dict()
# Traverse the XML tree
for ways in root:
    if ways.tag == "way":
        for way in ways:
            if way.tag == "nd":
                # For each attribute 'ref'
                ref = way.attrib['ref']
                # Add the node to the dictionary, if it doesn't already exist
                if int(ref) not in id_dict:
                    id_dict[int(ref)] = i
                    # Imcrement id for next node
                    i = i + 1

csv = csv.reader(open(csv_file), delimiter=' ')
i = 0
match = 0
# The temporary output file stores all nodes (unsorted)
temp_output = open(temp_output_file, 'w')
# Print all used nodes to the temporary file
for data in csv:
    if int(data[0]) in id_dict:
        temp_output.write(("%d" % (id_dict[int(data[0])])) + ' ' + data[1] + ' ' + data[2] + '\n') 
        i = i + 1
        match = match + 1
# Temporary file now contains all used nodes, we're done with it
temp_output.close()

# Sort based on the first number on each line (the id) and output to stdout
call(["sort", "-n", temp_output_file])


output = sys.stdout

# Write separator to file
output.write("#\n")
# Print all edges to stdout
for ways in root:
    if ways.tag == "way":
        # For each way, reset the id of the previous node
        prev = -1
        for way in ways:
            if way.tag == "nd":
                # For each 'ref'
                ref = way.attrib['ref']
                # If this is the first node in the way, only store it as the previous node
                if prev == -1:
                    prev = int(ref)
                # Else, write edges to output
                else:
                    # Write prev to cur and cur to prev
                    cur = int(ref)
                    output.write("%d %d\n%d %d\n" % (id_dict[prev], id_dict[cur], id_dict[cur], id_dict[prev]))
                    # Update previous node for next iteration (unless this is the lst node of the way, in which case prev will be set to -1 again
                    prev = cur

