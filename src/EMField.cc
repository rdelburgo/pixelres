//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software 
// shall cite the following Geant4-DNA collaboration publication:
// Med. Phys. 37 (2010) 4692-4708
// The Geant4-DNA web site is available at http://geant4-dna.org
// 
// If you use this example, please cite the following publication:
// Rad. Prot. Dos. 133 (2009) 2-11

#include "EMField.hh"
#include "G4SystemOfUnits.hh"

EMField::EMField() 
{    
}

EMField::~EMField ( ) 
{
}

void EMField::GetFieldValue(const double point[4], double *Bfield ) const
{ 
  G4double up= 300*volt;
  G4double down= 0.1*mm;
  G4double mag =3.8*tesla;
 
  // Magnetic field
  Bfield[0] = 0.;
  Bfield[1] = 0.;
  Bfield[2] = mag;
   
  // Electric field
  Bfield[3] = 0.;
  Bfield[4] = 0.;
  Bfield[5] = up/down;
  
  //    /**
  G4cout << point[0] << " " << point[1]/micrometer << " " << point[2]/micrometer << " " << point[3]/micrometer << " "
	 << "EMfield" << " " << Bfield[0]/tesla<< " "<< Bfield[1]/tesla<< " "<< Bfield[2]/tesla<< " E (V/mm) "
	 << Bfield[3]*mm/volt<< " "<< Bfield[4]*mm/volt<< " "<< Bfield[5]*mm/volt<< G4endl;
  //  **/
}
