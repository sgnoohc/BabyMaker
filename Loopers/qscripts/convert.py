#!/bin/env python

import os
import sys

def help():
    print "Usage: python {} cutflow.csv".format(sys.argv[0])
    sys.exit()

try:
    f = open(sys.argv[1])
except:
    help()

lines = f.readlines()

newlines = []
for line in lines:
    items = []
    for index, item in enumerate(line.split(",")):
        mod = item.replace("\"", "")
        mod = mod.strip()
        if mod.find("+/-") != -1:
            ms = mod.split("+/-")
            items.append(ms[0].strip())
            items.append(u"\u00B1".encode("utf-8"))
            items.append(ms[1].strip())
        else:
            items.append(mod)
            if index != 0:
                items.append("")
                items.append("")
    newlines.append(",".join(items))

try:
    ofile = open(sys.argv[2], 'w')
except:
    ofile = open("cutflow.csv", 'w')

for newline in newlines:
    ofile.write(newline + "\n")
