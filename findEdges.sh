#!/bin/bash
#Argument order: input file, output file
if [ $# > 2 ]
then
	input=$1
	output=$2
else
	input="test/nodes.node"
	output="test/full.txt"
fi

`rm "$output"`

`sed 1d $input > $output`
echo "#" >> "$output"
`awk '{print $1, $2, "\n"$2, $1}' $input > "$input".tmp`
`dct/dct < "$input".tmp > "$output".tmp`
`./dct-doubler.awk "$output".tmp >> "$output"`
`rm "$input".tmp`
`rm "$output".tmp`

