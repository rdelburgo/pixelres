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
// $Id: B2aDetectorMessenger.cc 69706 2013-05-13 09:12:40Z gcosmo $
// 
/// \file B2aDetectorMessenger.cc
/// \brief Implementation of the B2aDetectorMessenger class

#include "B2aDetectorMessenger.hh"
#include "B2aDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UnitsTable.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2aDetectorMessenger::B2aDetectorMessenger(B2aDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  fB2Directory = new G4UIdirectory("/B2/");
  fB2Directory->SetGuidance("UI commands specific to this example.");
  fDetDirectory = new G4UIdirectory("/B2/det/");
  fDetDirectory->SetGuidance("Detector construction control");
  /////////////////////////////   
  eleFieldCmd = new G4UIcmdWith3VectorAndUnit("/B2a/det/setEleField",this);
  eleFieldCmd->SetGuidance("Define electric field.");
  eleFieldCmd->SetGuidance("Usage: /B2a/det/setEleField  Ex  Ey  Ez  (in MV/mm)");
  eleFieldCmd->SetGuidance("Use the command  update  after setting a field.");
  eleFieldCmd->SetParameterName("Ex","Ey","Ez",false,false);
  eleFieldCmd->SetDefaultUnit("kV/cm");
  eleFieldCmd->SetUnitCategory("Electric field");
  eleFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  magFieldCmd = new G4UIcmdWith3VectorAndUnit("/B2a/det/setMagField",this);
  magFieldCmd->SetGuidance("Define magnetic field.");
  magFieldCmd->SetGuidance("Usage: /B2a/det/setMagField  Bx  By  Bz  unit");
  magFieldCmd->SetGuidance("Use the command  update  after setting a field.");
  magFieldCmd->SetParameterName("Bx","By","Bz",false,false);
  magFieldCmd->SetDefaultUnit("tesla");
  magFieldCmd->SetUnitCategory("Magnetic flux density");
  magFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  /////////////////////////////
  updateCmd = new G4UIcmdWithoutParameter("/B2a/det/update",this);
  updateCmd->SetGuidance("Update geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s).");
  updateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


//fTargMatCmd = new G4UIcmdWithAString("/B2/det/setTargetMaterial",this);
  //fTargMatCmd->SetGuidance("Select Material of the Target.");
  //fTargMatCmd->SetParameterName("choice",false);
  //fTargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //fChamMatCmd = new G4UIcmdWithAString("/B2/det/setChamberMaterial",this);
  //fChamMatCmd->SetGuidance("Select Material of the Chamber.");
  //fChamMatCmd->SetParameterName("choice",false);
  //fChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/B2/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("stepMax",false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->SetDefaultUnit("mm");
  fStepMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2aDetectorMessenger::~B2aDetectorMessenger()
{
  //delete fTargMatCmd;
  delete fChamMatCmd;
  delete fStepMaxCmd;
  delete fB2Directory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2aDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  //if( command == fTargMatCmd )
  //{ fDetectorConstruction->SetTargetMaterial(newValue);}

  //if( command == fChamMatCmd )
  //{ fDetectorConstruction->SetChamberMaterial(newValue);}

  if( command == fStepMaxCmd ) 
    fDetectorConstruction->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
  if( command == eleFieldCmd )
    fDetectorConstruction->SetEleField(eleFieldCmd->GetNew3VectorValue(newValue));
  if( command == magFieldCmd )
    fDetectorConstruction->SetMagField(magFieldCmd->GetNew3VectorValue(newValue));
  if( command == updateCmd ) 
    fDetectorConstruction->UpdateEMField();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
