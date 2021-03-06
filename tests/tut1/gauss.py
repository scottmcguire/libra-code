#*********************************************************************************
#* Copyright (C) 2015-2016 Alexey V. Akimov
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
if sys.platform=="cygwin":
    from cyglibra_core import *
elif sys.platform=="linux" or sys.platform=="linux2":
    from liblibra_core import *
from libra_py import *


def compute_estimators(a,q):
  # a - weights
  # q - coordinates

  N = len(q)

  ave = 0.0
  suma = 0.0  
  for i in range(0,N):
      ave = ave + a[i]*q[i]
      suma = suma + a[i]
  ave = ave / suma

  sig2 = 0.0
  for i in range(0,N):
      sig2 = sig2 + a[i]*(q[i] - ave)**2
  sig2 = sig2/suma

  sig = math.sqrt(sig2)

  print "average = ", ave 
  print "sigma = ", sig
  print "sigma2 = ", sig2

  return [suma, ave, sig, sig2]

def gauss(x, ave, sig, sig2, fact):
    pref = math.sqrt(fact/(sig*math.sqrt(math.pi)))
    res = pref * math.exp(-((x-ave)**2)/(2.0*sig2))
    return res





X = []
dx = 0.1
for i in range(-100,100):
    X.append(i*dx)


r = Random()

q = []
a0 = []
for i in range(0,500):
    q.append( 1.0 + 0.25*r.normal() )
    a0.append(1.0)

    q.append( -1.0 + 0.5*r.normal() )
    a0.append(1.0)

dy1 = DATA(q)
dens = dy1.Calculate_Distribution(X)[0]


suma0, ave0, sig0, sig02 = compute_estimators(a0, q)
fact0 = suma0 / float(len(a0))

a1 = []
for i in range(0,len(q)):
    g = gauss(q[i],ave0,sig0, sig02,fact0)
    a1.append(a0[i] - g*g)

suma1, ave1, sig1, sig12 = compute_estimators(a1, q)
fact1 = suma1 / float(len(a1))








f = open("normal.txt","w")
i = 0
sz = len(X)
for i in range(0, sz):
    f.write("%8.5f  %8.5f  %8.5f \n" % (X[i], dens[i], gauss(X[i],ave0,sig0, sig02,fact0) + gauss(X[i],ave1,sig1, sig12,fact1) ) )
f.close()

