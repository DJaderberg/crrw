#!/bin/bash
# Argument order: Data file (must be understood by osmosis), output file

if [ $# > 2 ]
then
	orig=$1
	output=$2
else
	orig="polacks.pbf"
	output="output.txt"
fi

# Extract roads
echo "Creating roads.pbf via osmosis..."
`osmosis --read-pbf "$orig" --tf accept-ways highway=* --tf reject-ways highway=pedestrian,footway,steps,cycleway,bridleway,service,path --tf reject-relations --used-node --write-pbf roads.pbf`
# Convert to roads to .osm, so that the python script can read the XML
echo "Creating roads.osm via ./osmconvert..."
`./osmconvert roads.pbf --drop-relations --drop-nodes --out-osm > roads.osm`
# Extract nodes (id, lat,lon) in a CSV-file
echo "Creating nodes.csv via ./osmconvert..."
`./osmconvert "$orig" --drop-relations --drop-ways --csv="@id @lat @lon" -o=nodes.csv`
# Change tab delimited CSV to space delimited
echo "Creating nodes_space.csv via awk..."
`awk '{print $1, $2, $3}' nodes.csv > nodes_space.csv`
# Run python script to generate TGF that is compatible with random-walk
echo "Creating "$output" via python ./nodesFromWays.py..."
`python ./nodesFromWays.py roads.osm nodes_space.csv ""$output".tmp" > "$output"`
# Remove files that were created by this script
echo "Finishing up by removing files that are no longer needed..."
`rm roads.pbf roads.osm nodes.csv nodes_space.csv ""$output".tmp"`

