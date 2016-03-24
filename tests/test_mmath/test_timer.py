#*********************************************************************************
#* Copyright (C) 2015 Alexey V. Akimov
#*
#* This file is distributed under the terms of the GNU General Public License
#* as published by the Free Software Foundation, either version 2 of
#* the License, or (at your option) any later version.
#* See the file LICENSE in the root directory of this distribution
#* or <http://www.gnu.org/licenses/>.
#*
#*********************************************************************************/

import os
import sys
import math

# Fisrt, we add the location of the library to test to the PYTHON path
cwd = os.getcwd()
print "Current working directory", cwd
sys.path.insert(1,cwd+"/../../_build/src/mmath")


print "\nTest 1: Importing the library and its content"
print "from cygmmath import *"
from cygmmath import *


print "\nTest 2: Construct timer object"
t = Timer()

print "\nTest 3: Several cycles with same timer - return accumulated time"
for a in xrange(3):
    x = 0.0
    t.start()
    for i in range(0,1000000):
        x = x + math.sin(i*math.pi)
    t.stop()
    print "Time to compute = ", t.show(), " sec"


print "\nTest 4: Several cycles with the creation of a new Timer every time - return time for each cycle"
for a in xrange(3):
    t = Timer()
    t.start()
    x = 0.0
    for i in range(0,1000000):
        x = x + math.sin(i*math.pi)
    t.stop()
    print "Time to compute = ", t.show(), " sec"




