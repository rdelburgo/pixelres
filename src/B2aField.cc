#include "B2aField.hh"
#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"
#include "G4ChordFinder.hh"
#include "G4TransportationManager.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//////////////////////////////////////////////////////////////////
///  Default zero field constructor
B2aField::B2aField() {
  //DefineUnits();
  fieldComponents[0] = fieldComponents[1] = fieldComponents[2] = 0.;
  fieldComponents[3] = fieldComponents[4] = fieldComponents[5] = 0.;
  equation = new G4EqMagElectricField(this);
  stepper = new G4ClassicalRK4(equation);
  G4int nvar=8;
  fIntgrDriver = new G4MagInt_Driver(fMinStep, 
                                     stepper, 
                                     nvar );
  theChordFinder= new G4ChordFinder(fIntgrDriver);
  GetGlobalFieldManager()->SetChordFinder(theChordFinder);
  GetGlobalFieldManager()->SetDetectorField(this);
}


//////////////////////////////////////////////////////////////////
///  Constructor with initial values for the electric an magnetic fields

B2aField::B2aField(const G4ThreeVector magFieldVector,const G4ThreeVector elecFieldVector) {
  //DefineUnits();
  equation = new G4EqMagElectricField(this);
  stepper = new G4ClassicalRK4(equation);
  SetFieldValue(magFieldVector, elecFieldVector);
  G4int nvar=8;
  fIntgrDriver = new G4MagInt_Driver(fMinStep,
                                     stepper,
                                     nvar );

  theChordFinder= new G4ChordFinder(fIntgrDriver);
  GetGlobalFieldManager()->SetChordFinder(theChordFinder);
  GetGlobalFieldManager()->SetDetectorField(this);
}

//////////////////////////////////////////////////////////////////
///  Copy constructor

B2aField::B2aField(const  B2aField &p)
  : G4ElectroMagneticField(p) {
  //DefineUnits();
  for(G4int i=0;i<6;i++)
    fieldComponents[i] = p.fieldComponents[i];
  equation = new G4EqMagElectricField(this);
  stepper = new G4ClassicalRK4(equation);
    G4int nvar=8;
  fIntgrDriver = new G4MagInt_Driver(fMinStep,
                                     stepper,
                                     nvar );

  theChordFinder= new G4ChordFinder(fIntgrDriver);
  GetGlobalFieldManager()->SetChordFinder(theChordFinder);
  GetGlobalFieldManager()->SetDetectorField(this);
}

//////////////////////////////////////////////////////////////////
///  Operator =
B2aField B2aField::operator = (const B2aField &p) {
  if (&p == this) return *this;
  for (G4int i=0; i<6; i++)
    fieldComponents[i] = p.fieldComponents[i];
  return *this;
}

//////////////////////////////////////////////////////////////////
///  Destructor
B2aField::~B2aField() {
  GetGlobalFieldManager()->SetDetectorField(0);
}

//////////////////////////////////////////////////////////////////
/// Set the value of the Global Field to fieldVector along Y
void B2aField::SetFieldValue(const G4ThreeVector magFieldVector,
					   const G4ThreeVector elecFieldVector) {
  if(elecFieldVector!=G4ThreeVector(0.,0.,0.) ||
     magFieldVector!=G4ThreeVector(0.,0.,0.) ) {
    fieldComponents[0] = magFieldVector.x();
    fieldComponents[1] = magFieldVector.y();
    fieldComponents[2] = magFieldVector.z();
    fieldComponents[3] = elecFieldVector.x();
    fieldComponents[4] = elecFieldVector.y();
    fieldComponents[5] = elecFieldVector.z();
  }
  else {
    // If the new field's value is Zero, then it is best to
    //  insure that it is not used for propagation.
    GetGlobalFieldManager()->SetDetectorField(0);
  }
}

//////////////////////////////////////////////////////////////////
/// Set the value of the Electric Field to fieldVector
void B2aField::SetPureElectricFieldValue(G4ThreeVector fieldVector) {
  if(fieldVector!=G4ThreeVector(0.,0.,0.) ) {
    //    fieldComponents[0] = 0.;
    //    fieldComponents[1] = 0.;
    //    fieldComponents[2] = 0.;
    fieldComponents[3] = fieldVector.x();
    fieldComponents[4] = fieldVector.y();
    fieldComponents[5] = fieldVector.z();
  }
  else {
    // If the new field's value is Zero, then it is best to
    //  insure that it is not used for propagation.
    GetGlobalFieldManager()->SetDetectorField(0);
  }
}

//////////////////////////////////////////////////////////////////
/// Set the value of the Magnetic Field to fieldVector
void B2aField::SetPureMagneticFieldValue(G4ThreeVector fieldVector) {
  if(fieldVector!=G4ThreeVector(0.,0.,0.) ) {
    fieldComponents[0] = fieldVector.x();
    fieldComponents[1] = fieldVector.y();
    fieldComponents[2] = fieldVector.z();
    //    fieldComponents[3] = 0.;
    //    fieldComponents[4] = 0.;
    //    fieldComponents[5] = 0.;
  }
  else {
    // If the new field's value is Zero, then it is best to
    //  insure that it is not used for propagation.
    GetGlobalFieldManager()->SetDetectorField(0);
  }
}

//////////////////////////////////////////////////////////////////
/// This is a virtual function in G4ElectroMagneticField to be instanciated here:
///   Return as Bfield[0], [1], [2] the magnetic field x, y & z components
///   and   as Bfield[3], [4], [5] G4the electric field x, y & z components
void B2aField::GetFieldValue(const G4double thePoint[4],
					   G4double* theField) const {
  if(thePoint) {;} //avoid the warning message
  theField[0] = fieldComponents[0];
  theField[1] = fieldComponents[1];
  theField[2] = fieldComponents[2];
  theField[3] = fieldComponents[3];
  theField[4] = fieldComponents[4];
  theField[5] = fieldComponents[5];
  
  G4cout  << " GGGGGGGGG  "
	  << thePoint[0] << " " << thePoint[1] << " " << thePoint[2] << " " << thePoint[3] << " "
	  << theField[0] << " " << theField[1] << " " << theField[2] << " " << theField[3] << " "
	  << theField[4] << " " << theField[5] << G4endl;
  
}

//////////////////////////////////////////////////////////////////
/// Returns the uniform magnetic field value
G4ThreeVector B2aField::GetMagneticFieldValue() {
  return G4ThreeVector(fieldComponents[0], 
		       fieldComponents[1], 
		       fieldComponents[2]);
}

//////////////////////////////////////////////////////////////////
/// Returns the uniform electric field value
G4ThreeVector B2aField::GetElectricFieldValue() {
  return G4ThreeVector(fieldComponents[3],
		       fieldComponents[4],
		       fieldComponents[5]);
}

//////////////////////////////////////////////////////////////////
/// Getting a local pointer to the global field manager
G4FieldManager*  B2aField::GetGlobalFieldManager() {
  return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}


//#include "G4UnitsTable.hh"
/**void B2aField::DefineUnits() {
  
   //G4UnitDefinition(const G4String& name, const G4String& symbol,
   //                 const G4String& category, G4double value);
   //G4UnitDefinition("volt/meter","V/m","Electric Field",volt/meter);
  //   G4UnitDefinition("kilovolt/meter","kV/m","Electric Field",kilovolt/meter);
   G4UnitDefinition("kilovolt/centimeter","kV/cm","Electric Field",kilovolt/centimeter);
   //   G4UnitDefinition("kilovolt/millimeter","kV/mm","Electric Field",kilovolt/millimeter);
   //   G4UnitDefinition("tesla", "tesla", "Magnetic field", tesla);
   }**/

