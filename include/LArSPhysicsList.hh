#ifndef __LARSPHYSICSLIST_H__
#define __LARSPHYSICSLIST_H__

#include "LArSPhysicsMessenger.hh"

//Additional Header Files
#include <globals.hh>
#include <iomanip>
#include <vector>

//Root Header Files
#include "TFile.h"
#include "TH1.h"
#include "TParameter.h"
#include "TNamed.h"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include <G4OpticalPhysics.hh>
#include <G4EmStandardPhysics.hh>
#include <G4EmPenelopePhysics.hh>
#include <G4EmExtraPhysics.hh>
#include <G4DecayPhysics.hh>
#include <G4StoppingPhysics.hh>
#include <G4NistManager.hh>
#include <G4HadronicProcessStore.hh>
#include <G4ios.hh>
#include <G4EmCalculator.hh>

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"

#include <vector>
using namespace std;

class LArSPhysicsList: public G4VModularPhysicsList 
{

public:
  LArSPhysicsList(G4String fName);
  virtual ~LArSPhysicsList();
  
public:
  void SetCuts();

  // functions for the messenger interface
  void SetCerenkov(G4bool useCerenkov) { m_bCerenkov = useCerenkov; }
  void SetEMlowEnergyModel(G4String theModel) { m_hEMlowEnergyModel = theModel; }
  void SetHadronicModel(G4String theModel)    { m_hHadronicModel = theModel; }
  void SetHistograms(G4bool makeHistos) { makePhysicsHistograms = makeHistos; }

  void MakePhysicsPlots();
  void WriteParameter(G4String parName);

private:

  G4VPhysicsConstructor *X1TG4OpticalPhysics;
  
  G4double defaultCutValue;
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  //G4double cutForProton;
  //G4double cutForAlpha;
  //G4double cutForGenericIon;
  
  G4int VerboseLevel;
	
  LArSPhysicsMessenger *m_pMessenger;
  G4String                 m_hEMlowEnergyModel;
  G4String                 m_hHadronicModel;
  G4bool                   m_bCerenkov;
  G4bool                   makePhysicsHistograms;
  
  G4String physRootFile;

};
#endif
