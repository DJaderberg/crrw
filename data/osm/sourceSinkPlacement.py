import re
import sys
import math

minlat=59.7847
maxlat=59.9157
minlon=17.5438
maxlon=17.8206

filename = '../uppsala.txt'
output = sys.stdout
source_dist = 0.08
source_dist_max = 0.11
sink_dist = 0.015

central_lat_source = (maxlat-minlat)/2 + minlat
central_lon_source = (maxlon-minlon)/2 + minlon - 0.01
central_lat_sink = (maxlat-minlat)/2 + minlat + 0.02
central_lon_sink = (maxlon-minlon)/2 + minlon - 0.03
total_rate = 80000
# One of req_sources and req_sinks must be a multiple of the other
# This ensures that equilibrium can be reached
req_sources = 800
req_sinks = 100
source_rate = total_rate/req_sources
sink_rate = -total_rate/req_sinks

node_file = open(filename, 'r')

line = node_file.readline()

vals = re.findall(r'\b\d+\.?\d*\b', line)

sources = 0
sinks = 0

while len(vals) >= 3:
    i = int(vals[0])
    lon = float(vals[1])
    lat = float(vals[2])
    dist_source = pow((lon-central_lon_source)**2 + (lat-central_lat_source)**2, 0.5)
    dist_sink = pow((lon-central_lon_sink)**2 + (lat-central_lat_sink)**2, 0.5)
    if dist_source > source_dist and dist_source < source_dist_max:
        sources = sources + 1
    elif dist_sink < sink_dist:
        sinks = sinks + 1
    line = node_file.readline()
    vals = re.findall(r'\b\d+\.?\d*\b', line)

assert(sources >= req_sources)
assert(sinks >= req_sinks)

node_file.close()
node_file = open(filename, 'r')

line = node_file.readline()

vals = re.findall(r'\b\d+\.?\d*\b', line)

sources = 0
sinks = 0

while len(vals) >= 3:
    i = int(vals[0])
    lon = float(vals[1])
    lat = float(vals[2])
    dist_source = pow((lon-central_lon_source)**2 + (lat-central_lat_source)**2, 0.5)
    dist_sink = pow((lon-central_lon_sink)**2 + (lat-central_lat_sink)**2, 0.5)
    if dist_source > source_dist and dist_source < source_dist_max and sources < req_sources:
        output.write("%d %f %f %d\n" % (i, lon, lat, source_rate))
        sources = sources + 1
    elif dist_sink < sink_dist and sinks < req_sinks:
        output.write("%d %f %f %d\n" % (i, lon, lat, sink_rate))
        sinks = sinks + 1
    else:
        output.write("%d %f %f\n" % (i, lon, lat))
    line = node_file.readline()
    vals = re.findall(r'\b\d+\.?\d*\b', line)

while len(line) > 1:
    output.write(line);
    line = node_file.readline()
