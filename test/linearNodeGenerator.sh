#!/bin/bash
# Argument order: filename, number of nodes, distance, production rate
if [ $# > 3 ]
then
	filename=$1
	size=$2
	prodRate=$3
else
	filename="test/nodes.txt"
	size=1000
	prodRate=10
fi

`rm "$filename"`

echo "0 0.0 0.0 -1" >> $filename
for i in $(seq 1 $(($size-1)));
do
	if [ $i -eq $(($size/2)) ]
	then
		echo ""$i" "$i".0 "$i".0" "$prodRate" >> $filename
	else
		echo ""$i" "$i".0 "$i".0" >> $filename
	fi
done
echo ""$size" "$size".0 "$size".0 -1" >> $filename
echo "#" >> $filename
echo "0 1" >> $filename
for i in $(seq 1 $(($size-1)));
do
	echo ""$i" "$(($i+1))"">> $filename
	echo ""$i" "$(($i-1))"" >> $filename
done
echo ""$size" "$(($size-1))"" >> $filename