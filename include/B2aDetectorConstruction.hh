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
//
// $Id: B2aDetectorConstruction.hh 73722 2013-09-09 10:23:05Z gcosmo $
//
/// \file B2aDetectorConstruction.hh
/// \brief Definition of the B2aDetectorConstruction class

#ifndef B2aDetectorConstruction_h
#define B2aDetectorConstruction_h 1
//#include "B2aField.hh"
#include "EMField.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"
#include "G4Region.hh"
#include "G4ChordFinder.hh"
#include "G4PropagatorInField.hh" 
#include "G4EqMagElectricField.hh"
//#include "G4ThreeVector.hh"
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
//class G4GlobalMagFieldMessenger;
class B2aDetectorMessenger;
/// Detector construction class to define materials, geometry
/// and global uniform magnetic field.

class B2aDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  B2aDetectorConstruction();
  virtual ~B2aDetectorConstruction();
  //B2aField* emField;
  G4Region* GetTargetRegion()  {return fRegion;}
public:
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();

    // Set methods
    //void SetTargetMaterial (G4String );
    void SetChamberMaterial(G4String );
    void SetPixelMaterial(G4String);
    void SetMaxStep (G4double );
    void SetCheckOverlaps(G4bool );
    G4ThreeVector eField;           ///< Electric field vector                                                                                            
    G4ThreeVector mField;           ///< Magnetic field vector                                                                                             
  // methods                                                                                                                                              
    void UpdateEMField();
    void SetEleField(G4ThreeVector eField);
    void SetMagField(G4ThreeVector mField);
  private:
  G4Region*          fRegion;
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();
  G4int fNbOfChambers;
  G4int frows;
  G4int fcolumns;
  G4int fpixelN;
  G4LogicalVolume**  fLogicChamber;    // pointer to the logical Chamber
  G4LogicalVolume**  fLogicPixel;
  G4Material*        fChamberMaterial; // pointer to the chamber material
  G4Material*        fPixelMaterial; // pointer to the chamber material
  G4UserLimits* fStepLimit;            // pointer to user step limits
  B2aDetectorMessenger*  fMessenger;   // messenger
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps 
  static G4ThreadLocal EMField * fField;
  G4FieldManager * fFieldMgr;
  G4MagIntegratorStepper * fStepper;
  G4EqMagElectricField * fEquation;
  G4MagInt_Driver * fIntgrDriver;
  G4ChordFinder * fChordFinder ;
  G4PropagatorInField * fPropInField; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
