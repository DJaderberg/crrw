#!/bin/bash

out_folder="/tmp/random-walk"
sinks_file="data/nodes/nodes_sinks_M10.txt"
sources_file="data/nodes/nodes_sources_M10.txt"

base_name="nodes"
metis="M10"
sinks_or_soruces="sources"
mu="1.0"
filetype=".txt"

steps=1000000
write=1000
time_step="0.1"
threads=10

#Initialize linear version
`cp versions/random-walk-linear.cpp src/random-walk.cpp`
`make clean`
`make random-walk`

#Parallel linear with METIS with many sinks
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`

#Parallel linear with METIS with many sources
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`


#
# Switch from linear to non-linear (mu = 1.1)!
#

`cp versions/random-walk-1.1.cpp src/random-walk.cpp`
`make clean`
`make random-walk`

mu="1.1"

#Parallel non-linear (mu=1.1) with METIS with many sources
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`

#Parallel non-linear (mu=1.1) with METIS with many sinks
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`

#
# Switch from linear to non-linear (mu = 1.4)!
#

`cp versions/random-walk-1.4.cpp src/random-walk.cpp`
`make clean`
`make random-walk`

mu="1.4"

#Parallel non-linear (mu=1.4) with METIS with many sources
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`

#Parallel non-linear (mu=1.4) with METIS with many sinks
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`


#
# Switch from linear to non-linear (mu = 1.8)!
#

`cp versions/random-walk-1.8.cpp src/random-walk.cpp`
`make clean`
`make random-walk`

mu="1.8"

#Parallel non-linear (mu=1.8) with METIS with many sources
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`

#Parallel non-linear (mu=1.8) with METIS with many sinks
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -p "$threads"`
