#!/bin/bash
# Argument order: filename, number of nodes, distance, production rate
if [ $# > 4 ]
then
	filename=$1
	size=$2
	distance=$3
	prodRate=$4
else
	filename="nodes.txt"
	size=1000
	distance=1
	prodRate=10
fi

`rm "$filename"`

echo "0 -1" >> $filename
for i in $(seq 1 $(($size-1)));
do
	if [ $i -eq $(($size/2)) ]
	then
		echo ""$i" "$prodRate"" >> $filename
	else
		echo "$i" >> $filename
	fi
done
echo ""$size" -1" >> $filename
echo "#" >> $filename
echo "0 1 "$distance"" >> $filename
for i in $(seq 1 $(($size-1)));
do
	echo ""$i" "$(($i+1))" "$distance"" >> $filename
	echo ""$i" "$(($i-1))" "$distance"" >> $filename
done
echo ""$size" "$(($size-1))" "$distance"" >> $filename
