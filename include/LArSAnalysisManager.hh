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
#include "LArSPrimaryGeneratorAction.hh"
#include "LArSEventData.hh"

//Additional Header Files
#include <globals.hh>
#include <numeric>
#include <vector>
#include <cmath>


//G4 Header Files
#include <G4VUserDetectorConstruction.hh>
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4TrackStatus.hh"
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
class LArSDetectorConstruction;

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
  void OpticalBoundaryInformation(const G4Step *step);

  void inline SetDectorConstructor(LArSDetectorConstruction *detCon){m_pDetCon = detCon;};


private:
  G4int fPastTrackPrimaryID = -1;
  
  G4String m_hDataFilename;
  G4int m_iNbEventsToSimulate;

  TFile      *m_pTreeFile;
  TTree      *m_pTree;
  TDirectory *_events;

  TParameter<int> *m_pNbEventsToSimulateParameter;

  LArSPrimaryGeneratorAction *m_pPrimaryGeneratorAction;

  LArSEventData *m_pEventData;

  G4Timer *runTime;
  G4bool            writeEmptyEvents;

  LArSDetectorConstruction* m_pDetCon;
  // a map of physical volume pointers to sensitive ids:
  std::map<G4VPhysicalVolume*, int> m_pSensitiveIDOfPhysicalVol;

  G4OpBoundaryProcessStatus fExpectedNextStatus;

};

#endif // __LARSANALYSISMANAGER_H__
