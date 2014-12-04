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


# Groups:
# All groups are defined by 4 values:
# 1: Central longitude, 2: central latitude, 3: maximum distance, 4: Is source? 
class Group:
  def __init__(self, lon=0.0, lat=0.0, dist=0.0, source=True):
    self.lon = lon
    self.lat = lat
    self.dist = dist
    self.source = source
  def is_in(self, lon, lat):
      if ((self.lat - lat)**2 + (self.lon - lon)**2 < self.dist**2):
          return True
      else:
          return False

# Definitions of groups
#Sinks
centrum = Group(17.6389, 59.8586, 0.0100, False)
bolanderna = Group(17.6753 , 59.8504 , 0.0100, False)
polacks = Group(17.6476 , 59.8396 , 0.0100, False)

#sink_list = [centrum, bolanderna, polacks]
sink_list = [centrum]
#Sources
sunnersta = Group(17.6535, 59.7960, 0.0205, True)
gottsunda = Group(17.6260 , 59.8095 , 0.0100, True)
savja = Group(17.7034 , 59.8167 , 0.0200, True)
norby = Group(17.6219 , 59.8238 , 0.0172, True)
flogsta = Group(17.5898 , 59.8485 , 0.0297, True)
luthagen = Group(17.6128 , 59.8683 , 0.0100, True)
nyby = Group(17.6501 , 59.8791 , 0.0225, True)
sala_backe = Group(17.6746 , 59.8691 , 0.0100, True)

source_list = [sunnersta, gottsunda, savja, norby, flogsta, luthagen, nyby, sala_backe]

line = node_file.readline()


vals = re.findall(r'\b\d+\.?\d*\b', line)

sources = 0
sinks = 0

# Count sources and count sinks
while len(vals) >= 3:
    i = int(vals[0])
    lon = float(vals[1])
    lat = float(vals[2])
    # Sinks
    matched = False
    for group in sink_list:
        if matched == False and group.is_in(lon, lat):
            sinks = sinks + 1
            matched = True
    # Sources
    for group in source_list:
        if matched == False and group.is_in(lon, lat):
            sources = sources + 1
            matched = True
    line = node_file.readline()
    vals = re.findall(r'\b\d+\.?\d*\b', line)

node_file.close()

sink_rate = -int(math.ceil(total_rate/sinks))
source_rate = int(total_rate/sources)

node_file = open(filename, 'r')

line = node_file.readline()

vals = re.findall(r'\b\d+\.?\d*\b', line)

sources = 0
sinks = 0

while len(vals) >= 3:
    i = int(vals[0])
    lon = float(vals[1])
    lat = float(vals[2])
    matched = False
    # Sinks
    for group in sink_list:
        if matched == False and group.is_in(lon, lat):
            output.write("%d %f %f %d\n" % (i, lon, lat, sink_rate))
            matched = True
    # Sources
    for group in source_list:
        if matched == False and group.is_in(lon, lat):
            output.write("%d %f %f %d\n" % (i, lon, lat, source_rate))
            matched = True
    if matched == False:
        output.write("%d %f %f\n" % (i, lon, lat))
    line = node_file.readline()
    vals = re.findall(r'\b\d+\.?\d*\b', line)

while len(line) > 1:
    output.write(line);
    line = node_file.readline()
