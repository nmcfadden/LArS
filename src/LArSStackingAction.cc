//XEBRA header files
#include "LArSStackingAction.hh"



LArSStackingAction::LArSStackingAction(LArSAnalysisManager *pAnalysisManager)
{
	m_pAnalysisManager = pAnalysisManager;
}

LArSStackingAction::~LArSStackingAction()
{
}

G4ClassificationOfNewTrack
LArSStackingAction::ClassifyNewTrack(const G4Track *pTrack)
{
	G4ClassificationOfNewTrack hTrackClassification = fUrgent;

	if(pTrack->GetDefinition()->GetParticleType() == "nucleus" && !pTrack->GetDefinition()->GetPDGStable())
	{
		if(pTrack->GetParentID() > 0 && pTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay" && pTrack->GetDefinition()->GetPDGLifeTime()/ns > 10.)
			hTrackClassification = fPostpone;
	}

	return hTrackClassification;
}

void
LArSStackingAction::NewStage()
{
}

void
LArSStackingAction::PrepareNewEvent()
{ 
}








