#!/usr/bin/python

# Mace Robotics (www.macerobotics.com)
# Author : Mace Robotics 
# Exemple : read ambiant light
# Date : 30/12/2015
# Version : 0.1

from mrpi1_lib import *

#main program
print "Exemple : Read ambiant light"

al1 = ambiantLight(1)
al2 = ambiantLight(2)
al3 = ambiantLight(3)
al4 = ambiantLight(4)
al5 = ambiantLight(5)
al6 = ambiantLight(6)

print "Ambiant light = %d %d %d %d %d %d" %(al1, al2, al3, al4, al5, al6)
