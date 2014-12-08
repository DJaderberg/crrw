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

#Parallel linear with METIS with many sinks
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`

#Parallel linear with METIS with many sources
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`


#
# Switch from linear to non-linear (mu = 1.1)!
#

mu="1.1"

#Parallel non-linear (mu=1.1) with METIS with many sources
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`

#Parallel non-linear (mu=1.1) with METIS with many sinks
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`

#
# Switch from linear to non-linear (mu = 1.4)!
#

mu="1.4"

#Parallel non-linear (mu=1.4) with METIS with many sources
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`

#Parallel non-linear (mu=1.4) with METIS with many sinks
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`


#
# Switch from linear to non-linear (mu = 1.8)!
#

mu="1.8"

#Parallel non-linear (mu=1.8) with METIS with many sources
sinks_or_sources="sources"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sources_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`

#Parallel non-linear (mu=1.8) with METIS with many sinks
sinks_or_sources="sinks"
filename="$base_name"_"$metis"_"$sinks_or_sources"_"$mu""$filetype"
`./random-walk -i data/"$sinks_file" -o "$out_folder"/"$filename" -n "$steps" -w "$write" -t "$time_step" -u "$mu" -p "$threads"`
