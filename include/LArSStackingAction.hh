#ifndef __LARSSTACKINGACTION_H__
#define __LARSSTACKINGACTION_H__

#include "LArSAnalysisManager.hh"

//Additional Header FIles
#include <globals.hh>

//G4 Header Files
#include <G4UserStackingAction.hh>
#include <G4ios.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTypes.hh>
#include <G4Track.hh>
#include <G4Event.hh>
#include <G4VProcess.hh>
#include <G4StackManager.hh>
#include <G4TransportationManager.hh>
#include <G4EventManager.hh>
#include <G4SystemOfUnits.hh>



class LArSAnalysisManager;

class LArSStackingAction: public G4UserStackingAction
{
public:
	LArSStackingAction(LArSAnalysisManager *pAnalysisManager=0);
	~LArSStackingAction();
  
	virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
	virtual void NewStage();
	virtual void PrepareNewEvent();

private:
	LArSAnalysisManager *m_pAnalysisManager;
};

#endif
