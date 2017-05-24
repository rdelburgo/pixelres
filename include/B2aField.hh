#ifndef B2aFieldy_H
#define B2aField_H 1
#include "G4ElectroMagneticField.hh"
#include "G4ThreeVector.hh"
#include "G4MagIntegratorDriver.hh"
class G4ChordFinder;
class G4MagIntegratorStepper;
class G4EqMagElectricField;
class G4FieldManager;

class B2aField: public G4ElectroMagneticField {
private:
  G4double fieldComponents[6];      ///< The EM field: follows the G4ElectroMagneticField convention
  B2aField *emfield;
  G4ThreeVector eField;           ///< Electric field vector
  G4ThreeVector mField;    
  G4ChordFinder* theChordFinder;    ///< Chord parameter
  G4MagIntegratorStepper* stepper;  ///< Integrator stepper
  G4EqMagElectricField* equation;   ///< Equation
  G4double fMinStep;              ///minstep for the mag field driver
  G4MagInt_Driver  *fIntgrDriver; ///driver, u need this so u can set the driver to 8 dof, bc u have 2 fields, -_-
public:
  B2aField();
  B2aField(const G4ThreeVector magFieldVector,
			 const G4ThreeVector elecFieldVector);
  B2aField(const  B2aField &p);
  ~B2aField();

  B2aField operator = (const B2aField &p);

  void SetFieldValue(const G4ThreeVector magFieldVector,
		     const G4ThreeVector elecFieldVector);

  //Set the field as pure electric or magnetic    NOT YET USED...
  void SetPureElectricFieldValue(G4ThreeVector fieldVector);
  void SetPureMagneticFieldValue(G4ThreeVector fieldVector);

  ///This is a virtual function in G4ElectroMagneticField to be instanciated here
  ///Return as Bfield[0], [1], [2] the magnetic field x, y & z components
  /// and   as Bfield[3], [4], [5] the electric field x, y & z components
  void GetFieldValue(const G4double thePoint[4], G4double* theField) const;

  G4ThreeVector GetMagneticFieldValue();
  G4ThreeVector GetElectricFieldValue();

  G4bool DoesFieldChangeEnergy()const{return false;}
  //does not work in other way???

  void DefineUnits();
  //protected:
  /// Find the global Field Manager
  G4FieldManager* GetGlobalFieldManager();   // static
};
#endif
