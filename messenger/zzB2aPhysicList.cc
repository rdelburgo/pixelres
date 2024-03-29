
#include "B2aPhysicList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"

//#include "PhysListEmStandard.hh"
//#include "PhysListEmStandardWVI.hh"
//#include "PhysListEmStandardSS.hh"
//#include "PhysListEmStandardGS.hh"
//#include "HadrontherapyIonStandard.hh"

//#include "B2aStepLimiterBuilder.hh"

#include "G4UnitsTable.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4EmConfigurator.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4BraggIonGasModel.hh"
#include "G4BetheBlochIonGasModel.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4IonPhysics.hh"

//////////////////////////////////////////////////////////////////
/// Constructor. Initializing values
B2aPhysicList::B2aPhysicList():  G4VModularPhysicsList(){

  emBuilderIsRegisted = false;
  stepLimiterIsRegisted = false;
  helIsRegisted = false;
  bicIsRegisted = false;
  ionIsRegisted = false;
  gnucIsRegisted = false;
  gasIsRegisted = false;
  stopIsRegisted = false;
  verbose = 0;
  G4LossTableManager::Instance()->SetVerbose(verbose);
  //G4LossTableManager::Instance();
  defaultCutValue = 1.*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

  //  pMessenger = new B2aPhysicListMessenger(this);

  // EM physics
  //emPhysicsList = new PhysListEmStandard("local");
  //emPhysicsList = new G4EmStandardPhysics(1);

  // Add Physics builders
  RegisterPhysics(new G4DecayPhysics());
  //steplimiter = new B2aStepLimiterBuilder();
}

//////////////////////////////////////////////////////////////////
/// Destructor. Nothing to do
B2aPhysicList::~B2aPhysicList() {
  delete emPhysicsList;
  //delete pMessenger;
}

//////////////////////////////////////////////////////////////////
/// Registering the physics processes
void B2aPhysicList::AddPhysicsList(const G4String& name){
  if(verbose > 0) {
    G4cout << "Add Physics <" << name
           << "> emBuilderIsRegisted= " << emBuilderIsRegisted
           << G4endl;
  }
  if ((name == "emstandard") && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics(1));
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } /**else if (name == "local" && !emBuilderIsRegisted) {
    emPhysicsList = new PhysListEmStandard(name);
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
    } **/else if (name == "emstandard_opt1" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option1());
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "emstandard_opt2" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option2());
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "emstandard_opt3" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option3());
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "emstandard_opt4" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option4());
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "emlivermore" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmLivermorePhysics());
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "empenelope" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmPenelopePhysics());
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  }/** else if (name == "standardSS" && !emBuilderIsRegisted) {
    emPhysicsList = new PhysListEmStandardSS(name);
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "standardWVI" && !emBuilderIsRegisted) {
    emPhysicsList = new PhysListEmStandardWVI(name);
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "standardGS" && !emBuilderIsRegisted) {
    emPhysicsList = new PhysListEmStandardGS(name);
    emBuilderIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
    }**/

  // Register Low Energy  processes for protons and ions
  // Stopping power parameterisation: ICRU49 (default model)
  // Register Standard processes for protons and ions
  /**
  else if (name == "ion-standard") {
    if (ionIsRegisted)
      G4cout << "B2aPhysicList::AddPhysicsList: " << name
	     << " cannot be registered ---- ion List already existing"
	     << G4endl;
    else {
      RegisterPhysics( new HadrontherapyIonStandard(name) );
      ionIsRegisted = true;
      G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
    }
  } else if (name == "ionGasModels" && !gasIsRegisted && emBuilderIsRegisted) {
    //AddPhysicsList("emstandard");
    AddIonGasModels();
    gasIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
    } **/
  //else if (name == "elastic" && helIsRegistered && emBuilderIsRegisted) {
  else if (name == "elastic"&& emBuilderIsRegisted) {   
  RegisterPhysics(new G4HadronElasticPhysics());
    helIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "binary" && !bicIsRegisted && emBuilderIsRegisted) {
    RegisterPhysics(new G4HadronInelasticQBBC());
    bicIsRegisted = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } /**else if (name == "binary_ion" && !ionIsRegisted && d = true;
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">" << G4endl;
  } else if(!emBuilderIsRegisted) {
    G4cout << "PhysicsList::AddPhysicsList <" << name << ">"
           << " fail - EM physics should be registered first " << G4endl;
  } else {
    G4cout << "B2aPhysicList::AddPhysicsList <" << name << ">"
           << " fail - module is already regitered or is unknown " << G4endl;
	   }**/
}

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

// Hadrons
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

//////////////////////////////////////////////////////////////////
/// Construct Particles

void B2aPhysicList::ConstructParticle() {
  if(verbose > 0)
    G4cout << "Construct Particles" << G4endl;

  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  //  G4NeutrinoE::NeutrinoEDefimPhysicsList::ConstructProcess() {

  if(verbose > 0)
    G4cout << "Construct Processes" << G4endl;

  if(!emBuilderIsRegisted) { AddPhysicsList("standard"); }
  if(!emPhysicsList) { G4VModularPhysicsList::ConstructProcess(); }
  else{
    AddTransportation();
    emPhysicsList->ConstructProcess();
  }
  // Define energy interval for loss processes
  G4EmProcessOptions emOptions;
  emOptions.SetMinEnergy(0.1*keV);
  emOptions.SetMaxEnergy(100.*GeV);
  //emOptions.Sbose>0) DumpCutValuesTable();
}

//////////////////////////////////////////////////////////////////
/// Selecting verbosity
void B2aPhysicList::SetVerbose(G4int val){
  verbose = val;
}

//////////////////////////////////////////////////////////////////
/// Setting cut value for the gammas
void B2aPhysicList::SetCutForGamma(G4double cut){
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//////////////////l
void B2aPhysicList::AddIonGasModels() {
  G4EmConfigurator* em_config = G4LossTableManager::Instance()->EmConfigurator();

  G4ParticleTable::G4PTblDicIterator* aaParticleIterator = G4ParticleTable::GetParticleTable()->GetIterator();
  aaParticleIterator->reset();
  while ((*aaParticleIterator)()) {
G4ParticleDefinition* particle = aaParticleIterator->value();
    G4String partname = particle->GetParticleName();
    if(partname == "alpha" || partname == "He3" || partname == "GenericIon") {
      G4BraggIonGasModel* mod1 = new G4BraggIonGasModel();
      G4BetheBlochIonGasModel* mod2 = new G4BetheBlochIonGasModel();
      G4double eth = 2.*MeV*particle->GetPDGMass()/proton_mass_c2;
      em_config->SetExtraEmModel(partname,"ionIoni",mod1,"",0.0,eth,
                                 new G4IonFluctuations());
      em_config->SetExtraEmModel(partname,"ionIoni",mod2,"",eth,100*TeV,
                                 new G4UniversalFluctuation());
    }
  }
}
