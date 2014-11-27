import xml.etree.ElementTree as ET
import csv
import sys
from subprocess import call
tree_file = "roads.osm"
csv_file = "nodes_space.csv"
output_file = "output.txt"
temp_output_file = output_file + '.tmp'

tree = ET.parse(tree_file)

root = tree.getroot()

used_nodes = []
i = 0
id_dict = dict()
for ways in root:
    if ways.tag == "way":
        for way in ways:
            if way.tag == "nd":
                ref = way.attrib['ref']
                used_nodes.append(int(ref))
                if int(ref) not in id_dict:
                    id_dict[int(ref)] = i
                    #print "Own id:", i, "OSM id:", int(ref)
                    i = i + 1

#print i
# Only use unique values in the node list
#used_nodes = list(set(used_nodes))
#used_nodes.sort()

csv = csv.reader(open(csv_file), delimiter=' ')
i = 0
match = 0
#print id_dict
#for d in id_dict:
#    print d
#    print id_dict[d]

temp_output = open(temp_output_file, 'w')
# Print all used nodes to the beginning of the file
for data in csv:
    if int(data[0]) in id_dict:
        #print id_dict[int(data[0])]
        temp_output.write(("%d" % (id_dict[int(data[0])])) + ' ' + data[1] + ' ' + data[2] + '\n') 
        #temp_output.write(("%d %s" % (id_dict[int(data[0])], data[0])) + ' ' + data[1] + ' ' + data[2] + '\n') 
        i = i + 1
        match = match + 1
temp_output.close()
#print call(["sort", "-n", temp_output_file], stdout=open(output_file, 'w'), shell=True)
call(["sort", "-n", temp_output_file])


#output = open(output_file, 'w')
output = sys.stdout

output.write("#\n")
# Print all edges
for ways in root:
    if ways.tag == "way":
        prev = -1
        for way in ways:
            if way.tag == "nd":
                ref = way.attrib['ref']
                #print way.attrib
                if prev == -1:
                    prev = int(ref)
                else:
                    cur = int(ref)
                    output.write("%d %d\n%d %d\n" % (id_dict[prev], id_dict[cur], id_dict[cur], id_dict[prev]))
                    prev = cur




#output.close()

#print i
#print "Match: "
#print match



#tree.write("roadsAfterPy.osm")



# osmosis --read-pbf polacks.pbf --tf accept-ways highway="*" --tf reject-ways highway=pedestrian,footway,steps,cycleway,bridleway,service,path --tf reject-relations --used-node --write-pbf roads.pbf
# ./osmconvert roads.pbf --drop-relations --drop-nodes --out-osm > roads.osm
# ./osmconvert roads.pbf --drop-relations --drop-ways --out-osm > nodes.osm
# ./osmconvert polacks.pbf --drop-relations --drop-ways --csv="@id @lat @lon" -o=nodes.csv
# awk "{print \$1, \$2, \$3}" nodes.csv > nodes_space.csv
