#!/bin/bash
#Argument order: input file, output file
if [ $# > 2 ]
then
	input=$1
	output=$2
else
	input="test/nodes2d.node"
	output="test/full.txt"
fi

`sed 1d $input > $output`
`head -n 1 "$input" > "$input.tmp"`
`awk '{print $2, $3}' $output >> "$input".tmp`
echo "#" >> "$output"
`dct/dct < "$input".tmp > "$output".tmp`
`./dct-doubler.awk "$output".tmp >> "$output"`
`rm "$input".tmp`
`rm "$output".tmp`

