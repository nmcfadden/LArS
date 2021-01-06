
#include "LArSEventAction.hh"

LArSEventAction::LArSEventAction(LArSAnalysisManager *pAnalysisManager)
{
  m_pAnalysisManager = pAnalysisManager;
}

LArSEventAction::~LArSEventAction()
{
}

void
LArSEventAction::BeginOfEventAction(const G4Event *pEvent)
{
  if(pEvent->GetEventID() % 100 == 0)
    {
      G4cout << "------ Begin event " << pEvent->GetEventID()<< "------" << G4endl;
    }
  
  if(m_pAnalysisManager)
    m_pAnalysisManager->BeginOfEvent(pEvent);
}

void LArSEventAction::EndOfEventAction(const G4Event *pEvent)
{
  if(m_pAnalysisManager)
    m_pAnalysisManager->EndOfEvent(pEvent);
}


