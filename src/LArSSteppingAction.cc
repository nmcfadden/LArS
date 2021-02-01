#include "LArSSteppingAction.hh"


LArSSteppingAction::LArSSteppingAction(LArSAnalysisManager *myAM):myAnalysisManager(myAM)
{}

void LArSSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // Using custom stepping action in the Analysis Manager
  myAnalysisManager->Step(aStep);
}
