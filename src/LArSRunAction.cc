//XEBRA header files

#include "LArSRunAction.hh"




LArSRunAction::LArSRunAction(LArSAnalysisManager *pAnalysisManager)
{
  m_hRanSeed         = 12345; // default value
  m_pMessenger       = new LArSRunActionMessenger(this);
  
  m_pAnalysisManager = pAnalysisManager;
  
}

LArSRunAction::~LArSRunAction()
{
  delete m_pMessenger;
}

void
LArSRunAction::BeginOfRunAction(const G4Run *pRun)
{
  if(m_pAnalysisManager) {
    //    m_pAnalysisManager->SetForcedTransport(m_hForcedTransport);
    m_pAnalysisManager->BeginOfRun(pRun);
  }
  
  // random seeding of the MC
  if(m_hRanSeed > 0){
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    G4cout << "LArSRunAction::BeginOfRunAction Initialize random numbers with seed = "<<m_hRanSeed<<G4endl;
    CLHEP::HepRandom::setTheSeed(m_hRanSeed);
  } else {
    // initialize with time.....
    struct timeval hTimeValue;
    gettimeofday(&hTimeValue, NULL);
    G4cout << "LArSRunAction::BeginOfRunAction Initialize random numbers with seed = "<<hTimeValue.tv_usec<<G4endl;
    CLHEP::HepRandom::setTheSeed(hTimeValue.tv_usec);
  }
}

void
LArSRunAction::EndOfRunAction(const G4Run *pRun)
{
  if(m_pAnalysisManager)
    m_pAnalysisManager->EndOfRun(pRun);
}

