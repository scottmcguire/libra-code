#*********************************************************************************
#* Copyright (C) 2016 Alexey V. Akimov
#*
#* This file is distributed under the terms of the GNU General Public License
#* as published by the Free Software Foundation, either version 2 of
#* the License, or (at your option) any later version.
#* See the file LICENSE in the root directory of this distribution
#* or <http://www.gnu.org/licenses/>.
#*
#*********************************************************************************/
###################################################################
# Tutorial: This file demonstrates the functionality of the 
# "LoadTRIPOS" module of the "libra_py"
###################################################################

import sys

if sys.platform=="cygwin":
    from cyglibra_core import *
elif sys.platform=="linux" or sys.platform=="linux2":
    from liblibra_core import *

from libra_py import *



tripos = ForceField()

LoadTRIPOS.Load_TRIPOS(tripos,"tripos.dat","tripos_bonds.dat","tripos_angles.dat","tripos_dihedrals.dat")

tripos.show_info()
