#ifndef __LARSANALYSISMANAGER_H__
#define __LARSANALYSISMANAGER_H__

//Root Header Files
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TParameter.h>
#include <TDirectory.h>
#include <TH1.h>

//LARS header files
#include "LArSDetectorConstruction.hh"
#include "LArSPmtSensitiveDetector.hh"
#include "LArSLXeHit.hh"
#include "LArSPmtHit.hh"
//#include "LArSLScintHit.hh"
#include "LArSPrimaryGeneratorAction.hh"
#include "LArSEventData.hh"

//Additional Header Files
#include <globals.hh>
#include <numeric>
#include <vector>
#include <cmath>


//G4 Header Files
#include <G4SDManager.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4EmCalculator.hh>
#include <G4Material.hh>
#include <G4HadronicProcessStore.hh>
#include <G4ParticleTable.hh>
#include <G4NistManager.hh>
#include <G4ElementTable.hh>
#include <G4Version.hh>
#include <G4SystemOfUnits.hh>
#include <G4Timer.hh>
#include <G4ThreeVector.hh>



class G4Run;
class G4Event;
class G4Step;

class TFile;
class TTree;

class LArSEventData;
class LArSPrimaryGeneratorAction;

class LArSAnalysisManager
{
public:
  LArSAnalysisManager(LArSPrimaryGeneratorAction *pPrimaryGeneratorAction);
  virtual ~LArSAnalysisManager();

public:
  virtual void BeginOfRun(const G4Run *pRun); 
  virtual void EndOfRun(const G4Run *pRun); 
  virtual void BeginOfEvent(const G4Event *pEvent); 
  virtual void EndOfEvent(const G4Event *pEvent); 
  virtual void Step(const G4Step *pStep);	
  
  void SetDataFilename(const G4String &hFilename) { m_hDataFilename = hFilename; }
  void SetNbEventsToSimulate(G4int iNbEventsToSimulate) { m_iNbEventsToSimulate = iNbEventsToSimulate;}

  void FillParticleInSave(G4int flag, G4int partPDGcode, G4ThreeVector pos, G4ThreeVector dir, G4float nrg, G4float time, G4int trackID);

private:
  G4bool FilterEvent(LArSEventData *pEventData);

private:
  G4int m_iLXeHitsCollectionID;
  G4int m_iPmtHitsCollectionID;
  G4int m_iLScintHitsCollectionID;
  
  G4String m_hDataFilename;
  G4int m_iNbEventsToSimulate;

  TFile      *m_pTreeFile;
  TTree      *m_pTree;
  TDirectory *_events;

  TParameter<int> *m_pNbEventsToSimulateParameter;
  // TParameter<double> *nRejectParameter;
  // TParameter<double> *nAcceptParameter;

  LArSPrimaryGeneratorAction *m_pPrimaryGeneratorAction;

  LArSEventData *m_pEventData;
  G4bool            plotPhysics;

  G4Timer *runTime;
  G4bool            writeEmptyEvents;
};

#endif // __LARSANALYSISMANAGER_H__
