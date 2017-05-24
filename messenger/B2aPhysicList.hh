#ifndef B2aPhysicList_h
#define B2aPhysicList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

//class B2aPhysicListMessenger;
//class B2aStepLimiterBuilder;
class G4VPhysicsConstructor;
class B2aPhysicList: public G4VModularPhysicsList {

public:
  B2aPhysicList();
  ~B2aPhysicList();

  // SetCuts()                                                                                                                                              
public:
  void ConstructParticle();
  void ConstructProcess();
  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void AddPhysicsList(const G4String&);
  void SetVerbose(G4int val);

private:
  void AddIonGasModels();
  G4double cutForGamma;            ///< Cut energy parameter for gammas
  G4double cutForElectron;         ///< Cut energy parameter for gammas
  G4double cutForPositron;         ///< Cut energy parameter for gammas
  G4int    verbose;                ///< Verbose control
  G4bool   emBuilderIsRegisted;    ///< Register control parameter for library
  G4bool   stepLimiterIsRegisted;  ///< Register control parameter for library
  G4bool   helIsRegisted;          ///< Register control parameter for library
  G4bool   bicIsRegisted;          ///< Register control parameter for library
  G4bool   ionIsRegisted;          ///< Register control parameter for library
  G4bool   gnucIsRegisted;         ///< Register control parameter for library
  G4bool   gasIsRegisted;          ///< Register control parameter for library
  G4bool   stopIsRegisted;         ///< Register control parameter for library

  //B2aPhysicListMessenger* pMessenger;  ///< Pointer to messenger
  //B2aStepLimiterBuilder* steplimiter;   ///< Pointer to step limiter

  G4VPhysicsConstructor*  emPhysicsList;     ///< Pointer to Physics list

};
#endif
