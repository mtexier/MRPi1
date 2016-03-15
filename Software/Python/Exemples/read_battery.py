#!/usr/bin/python

# Mace Robotics (www.macerobotics.com)
# Author : Mace Robotics 
# Exemple : read battery
# Date : 30/12/2015
# Version : 0.1

from mrpi1_lib import *

#main program
print "Start program : read battery"

tension = battery()
print "Battery = %f Volt" %(tension)
