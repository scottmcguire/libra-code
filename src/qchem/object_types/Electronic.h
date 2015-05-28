/*********************************************************************************
* Copyright (C) 2014 Alexey V. Akimov
*
* This file is distributed under the terms of the GNU General Public License
* as published by the Free Software Foundation, either version 2 of
* the License, or (at your option) any later version.
* See the file LICENSE in the root directory of this distribution
* or <http://www.gnu.org/licenses/>.
*
*********************************************************************************/
/**
 \file Electronic.h
 \brief Declaration of the containers for electronic variables and methods for handling them

*/
/****************************************************************************
  This file contains declaration of the following functions and classes:

  class Electronic
  int init_numbers(vector<int>&,Electronic*,vector<AO>&, Model_Parameters&, Nuclear&);
  int init_electronic_subsystems(vector<vector<int> >&,vector<vector<int> >&, vector<vector<int> >&, vector<Electronic*>&,vector<AO>&,Model_Parameters&, Nuclear&);

****************************************************************************/

#ifndef ELECTRONIC_H
#define ELECTRONIC_H

#include "Mathematics.h"
#include "Model_Parameters.h"
#include "Nuclear.h"
#include "MOAO.h"

/// \brief This class implements the container for information about electronic variables
class Electronic{

  public:

  //-------------- Constructors --------------
  /// Default constructor
  Electronic(){
    Norb  = 0;
    Nocc_alp = Nocc_bet = 0;
    Nelec = 0.0;
    P_alp = NULL; P_bet = NULL; P = NULL; 
    C_alp = NULL; C_bet = NULL;
    Sao   = NULL; Hao = NULL;
    Fao_alp = NULL; Fao_bet = NULL;
    dFao_alp_dP_alp = NULL;  dFao_alp_dP_bet = NULL;
    dFao_bet_dP_alp = NULL;  dFao_bet_dP_bet = NULL;
    E_alp = NULL; E_bet = NULL;
  }
  /// Constructor with one argument
  Electronic(int n){
    Norb = n;
    Nocc_alp = Nocc_bet = 0;
    Nelec = 0.0;
    P_alp = new MATRIX(Norb,Norb);
    P_bet = new MATRIX(Norb,Norb);
    P     = new MATRIX(Norb,Norb);
    C_alp = new MATRIX(Norb,Norb);
    C_bet = new MATRIX(Norb,Norb);
    Sao   = new MATRIX(Norb,Norb);
    Hao   = new MATRIX(Norb,Norb);
    Fao_alp = new MATRIX(Norb,Norb);
    Fao_bet = new MATRIX(Norb,Norb);
    dFao_alp_dP_alp = new MATRIX(Norb,Norb); *dFao_alp_dP_alp = 0.0;
    dFao_alp_dP_bet = new MATRIX(Norb,Norb); *dFao_alp_dP_bet = 0.0;
    dFao_bet_dP_alp = new MATRIX(Norb,Norb); *dFao_bet_dP_alp = 0.0;
    dFao_bet_dP_bet = new MATRIX(Norb,Norb); *dFao_bet_dP_bet = 0.0;
    E_alp = new MATRIX(Norb,Norb);
    E_bet = new MATRIX(Norb,Norb);   
    Mull_orb_pop_net = vector<double>(Norb,0.0);
    Mull_orb_pop_gross = vector<double>(Norb,0.0);

  }

  Electronic(const Electronic&);   ///< Copy constructor;
  Electronic(Electronic*);         ///< Constructor from the address of the other existing object
  
  /// Destructor
  ~Electronic(){
    delete P_alp;   delete P_bet;    delete P;        
    delete C_alp;   delete C_bet;
    delete Sao;     delete Hao;
    delete Fao_alp; delete Fao_bet;
    delete dFao_alp_dP_alp;  delete dFao_alp_dP_bet;
    delete dFao_bet_dP_alp;  delete dFao_bet_dP_bet;
    delete E_alp;   delete E_bet;

    Mull_orb_pop_net.clear();
    Mull_orb_pop_gross.clear();

    if(bands_alp.size()>0){ bands_alp.clear(); }
    if(bands_bet.size()>0){ bands_bet.clear(); }
    if(occ_alp.size()>0){ occ_alp.clear(); }
    if(occ_bet.size()>0){ occ_bet.clear(); }
   
    Norb  = 0;
    Nocc_alp = Nocc_bet = 0;
    Nelec = 0.0;
    P_alp = NULL; P_bet = NULL; P = NULL; 
    C_alp = NULL; C_bet = NULL;
    Sao   = NULL; Hao = NULL;
    Fao_alp = NULL; Fao_bet = NULL;
    dFao_alp_dP_alp = NULL;  dFao_alp_dP_bet = NULL;
    dFao_bet_dP_alp = NULL;  dFao_bet_dP_bet = NULL;
    E_alp = NULL; E_bet = NULL;

  }


 
  //-------------- Data members --------------
  int Norb;        ///< number of orbitals in this subsystem
  int Nocc_alp;    ///< number of occupied alpha orbitals in this subsystem
  int Nocc_bet;    ///< number of occupied beta orbitals in this subsystem
  double Nelec;    ///< number of electrons in this subsystem

  vector< pair<int,double> > bands_alp; ///< orbital index and orbital energy, alpha-channel
  vector< pair<int,double> > bands_bet; ///< orbital index and orbital energy, beta-channel
  vector< pair<int,double> > occ_alp;   ///< orbital index and orbital occupation number, alpha-channel
  vector< pair<int,double> > occ_bet;   ///< orbital index and orbital occupation number, beta-channel
  

  // Density matrices
  MATRIX* P_alp;                        ///< Density matrix, alpha-channel
  MATRIX* P_bet;                        ///< Density matrix, beta-channel
  MATRIX* P;                            ///< Density matrix, total

  // Wfc coefficients
  MATRIX* C_alp;                        ///< \brief MO coefficients, alpha-channel
                                        ///< C_alp[k][i] - is the i-th MO (column) k-th AO (row)
  MATRIX* C_bet;                        ///< \brief MO coefficients, beta-channel                     
                                        ///< C_bet[k][i] - is the i-th MO (column) k-th AO (row)
  // Overlaps
  MATRIX* Sao;                          ///< Overlap in AO basis

  // Core Hamiltonian
  MATRIX* Hao;                          ///< Core Hamiltonian in AO basis

  // Fock matrices
  MATRIX* Fao_alp;                      ///< Fock matrix in AO basis, alpha-channel
  MATRIX* Fao_bet;                      ///< Fock matrix in AO basis, beta-channel

  // Corrections:
  MATRIX* dFao_alp_dP_alp;              ///< derivative of the Fock matrix (alpha component) w.r.t. alpha component of density matrix
  MATRIX* dFao_alp_dP_bet;              ///< derivative of the Fock matrix (alpha component) w.r.t. beta component of density matrix
  MATRIX* dFao_bet_dP_alp;              ///< derivative of the Fock matrix (beta component) w.r.t. alpha component of density matrix
  MATRIX* dFao_bet_dP_bet;              ///< derivative of the Fock matrix (beta component) w.r.t. beta component of density matrix

  // Eigenvalues
  MATRIX* E_alp;                        ///< MO energies, alpha-channel
  MATRIX* E_bet;                        ///< MO energies, beta-channel

  vector<double> Mull_orb_pop_net;      ///< Net Mulliken populations for all (molecular) orbitals
  vector<double> Mull_orb_pop_gross;    ///< Gross Mulliken populations for all (molecular) orbitals

};

// Electronic.cpp
int init_numbers(vector<int>&,Electronic*,vector<AO>&, Model_Parameters&, Nuclear&,double);
int init_electronic_subsystems(vector<vector<int> >&,vector<vector<int> >&, vector<vector<int> >&, vector<Electronic*>&,
                               vector<AO>&,Model_Parameters&, Nuclear&,vector<double>&);


// NAC.cpp
void compute_overlap_nac(Electronic*, Electronic*, int, int, vector<int>&,
                         Electronic*, Electronic*, int, int, vector<int>&,
                         vector<AO>&,vector<AO>&,
                         double, vector<double*>&, int,MATRIX*, MATRIX*, MATRIX*, int);

void collect_matrices(int, vector<MATRIX*>&, vector<int>&, vector<int>&,
                      MATRIX*, vector<int>&,vector<int>&);




#endif // ELECTRONIC_H