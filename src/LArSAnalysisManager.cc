#include "LArSAnalysisManager.hh"


LArSAnalysisManager::LArSAnalysisManager(LArSPrimaryGeneratorAction *pPrimaryGeneratorAction){
  runTime = new G4Timer();
  
  // initialization of the HitsCollectionID variables 
  m_iLXeHitsCollectionID = -1;
  m_iPmtHitsCollectionID = -1;
  m_iLScintHitsCollectionID = -1;  
  
  // default output file name (which should be redifined in the main class)
  m_hDataFilename = "events.root";
  
  // reference to the initialized PrimaryGeneratorAction
  m_pPrimaryGeneratorAction = pPrimaryGeneratorAction;
  
  // declaration of the EventData class
  m_pEventData = new LArSEventData();
  //plotPhysics      = kTRUE;
  writeEmptyEvents = kFALSE;
}

LArSAnalysisManager::~LArSAnalysisManager(){
}

void LArSAnalysisManager::BeginOfRun(const G4Run *)
{
  // start a timer for this run....
  runTime->Start();
  // do we write empty events or not?
  writeEmptyEvents = m_pPrimaryGeneratorAction->GetWriteEmpty();
  
  // create output file
  m_pTreeFile = new TFile(m_hDataFilename.c_str(), "RECREATE");//, "File containing event data for LArS");
  // make tree structure
  TNamed *G4version = new TNamed("G4VERSION_TAG",G4VERSION_TAG);
  G4version->Write();
    
  _events = m_pTreeFile->mkdir("events");
  _events->cd();

  // create ROOT Tree for the simulation data
  G4cout <<"LArSAnalysisManager:: Init data tree ..."<<G4endl;

  m_pTree = new TTree("events", "Tree containing event data for LArS");

  // include missing ROOT classes
  gROOT->ProcessLine("#include <vector>");

  gROOT->ProcessLine("#include <vector>");
  
  m_pTree->Branch("eventid", &m_pEventData->m_iEventId, "eventid/I");
  // PMT hits 
  m_pTree->Branch("ntpmthits", &m_pEventData->m_iNbTopPmtHits, "ntpmthits/I");
  m_pTree->Branch("nrpmthits", &m_pEventData->m_iNbRingPmtHits, "nrpmthits/I");
  m_pTree->Branch("nbpmthits", &m_pEventData->m_iNbBottomPmtHits, "nbpmthits/I");
  m_pTree->Branch("nLSpmthits", &m_pEventData->m_iNbLSPmtHits, "nLSpmthits/I");
  
  m_pTree->Branch("PmtNb", &m_pEventData->m_iPmtNumber, "PmtNb/I");


  m_pTree->Branch("pmthits", "vector<int>", &m_pEventData->m_pPmtHits);

  m_pTree->Branch("etot", &m_pEventData->m_fTotalEnergyDeposited, "etot/F");
  m_pTree->Branch("nsteps", &m_pEventData->m_iNbSteps, "nsteps/I");
  m_pTree->Branch("trackid", "vector<int>", &m_pEventData->m_pTrackId);
  m_pTree->Branch("type", "vector<string>", &m_pEventData->m_pParticleType);
  m_pTree->Branch("parentid", "vector<int>", &m_pEventData->m_pParentId);
  m_pTree->Branch("parenttype", "vector<string>", &m_pEventData->m_pParentType);
  m_pTree->Branch("creaproc", "vector<string>", &m_pEventData->m_pCreatorProcess);
  m_pTree->Branch("edproc", "vector<string>", &m_pEventData->m_pDepositingProcess);
  m_pTree->Branch("xp", "vector<float>", &m_pEventData->m_pX);
  m_pTree->Branch("yp", "vector<float>", &m_pEventData->m_pY);
  m_pTree->Branch("zp", "vector<float>", &m_pEventData->m_pZ);
  m_pTree->Branch("ed", "vector<float>", &m_pEventData->m_pEnergyDeposited);
  m_pTree->Branch("time", "vector<float>", &m_pEventData->m_pTime);
  m_pTree->Branch("ekin", "vector<float>", &m_pEventData->m_pKineticEnergy);

  m_pTree->Branch("pre_MomDirX", "vector<float>", &m_pEventData->m_pPreMomDirX);
  m_pTree->Branch("pre_MomDirY", "vector<float>", &m_pEventData->m_pPreMomDirY);
  m_pTree->Branch("pre_MomDirZ", "vector<float>", &m_pEventData->m_pPreMomDirZ);
  m_pTree->Branch("post_MomDirX", "vector<float>", &m_pEventData->m_pPostMomDirX);
  m_pTree->Branch("post_MomDirY", "vector<float>", &m_pEventData->m_pPostMomDirY);
  m_pTree->Branch("post_MomDirZ", "vector<float>", &m_pEventData->m_pPostMomDirZ);
  m_pTree->Branch("pre_ekin", "vector<float>", &m_pEventData->m_pPreKineticEnergy);
  m_pTree->Branch("post_ekin", "vector<float>", &m_pEventData->m_pPostKineticEnergy);
    
  m_pTree->Branch("LScint_etot", &m_pEventData->m_fLScintTotalEnergyDeposited, "LScint_etot/F");
  m_pTree->Branch("LScint_nsteps", &m_pEventData->m_iLScintNbSteps, "LScint_nsteps/I");
  m_pTree->Branch("LScint_trackid", "vector<int>", &m_pEventData->m_pLScintTrackId);
  m_pTree->Branch("LScint_type", "vector<string>", &m_pEventData->m_pLScintParticleType);
  m_pTree->Branch("LScint_parentid", "vector<int>", &m_pEventData->m_pLScintParentId);
  m_pTree->Branch("LScint_parenttype", "vector<string>", &m_pEventData->m_pLScintParentType);
  m_pTree->Branch("LScint_creaproc", "vector<string>", &m_pEventData->m_pLScintCreatorProcess);
  m_pTree->Branch("LScint_edproc", "vector<string>", &m_pEventData->m_pLScintDepositingProcess);
  m_pTree->Branch("LScint_xp", "vector<float>", &m_pEventData->m_pLScintX);
  m_pTree->Branch("LScint_yp", "vector<float>", &m_pEventData->m_pLScintY);
  m_pTree->Branch("LScint_zp", "vector<float>", &m_pEventData->m_pLScintZ);
  m_pTree->Branch("LScint_ed", "vector<float>", &m_pEventData->m_pLScintEnergyDeposited);
  m_pTree->Branch("LScint_ed_bCorr", "vector<float>", &m_pEventData->m_pLScintEnergyDepositedBirksCorrected);
  m_pTree->Branch("LScint_time", "vector<float>", &m_pEventData->m_pLScintTime);
  m_pTree->Branch("LScint_ekin", "vector<float>", &m_pEventData->m_pLScintKineticEnergy);
  
  m_pTree->Branch("type_pri", "vector<string>", &m_pEventData->m_pPrimaryParticleType);
  m_pTree->Branch("xp_pri", &m_pEventData->m_fPrimaryX, "xp_pri/F");
  m_pTree->Branch("yp_pri", &m_pEventData->m_fPrimaryY, "yp_pri/F");
  m_pTree->Branch("zp_pri", &m_pEventData->m_fPrimaryZ, "zp_pri/F");
  m_pTree->Branch("xp_fcd", &m_pEventData->m_fForcedPrimaryX, "xp_fcd/F");
  m_pTree->Branch("yp_fcd", &m_pEventData->m_fForcedPrimaryY, "yp_fcd/F");
  m_pTree->Branch("zp_fcd", &m_pEventData->m_fForcedPrimaryZ, "zp_fcd/F");
  m_pTree->Branch("e_pri",  &m_pEventData->m_fPrimaryE, "e_pri/F");
  m_pTree->Branch("w_pri",  &m_pEventData->m_fPrimaryW, "w_pri/F");

  m_pTree->Branch("NSave", &m_pEventData->m_iNSave, "NSave/I");
  m_pTree->Branch("Save_flag", "vector<int>", &m_pEventData->m_pSave_flag);
  m_pTree->Branch("Save_type", "vector<int>", &m_pEventData->m_pSave_type);
  m_pTree->Branch("Save_x", "vector<float>", &m_pEventData->m_pSave_x);
  m_pTree->Branch("Save_y", "vector<float>", &m_pEventData->m_pSave_y);
  m_pTree->Branch("Save_z", "vector<float>", &m_pEventData->m_pSave_z);
  m_pTree->Branch("Save_cx", "vector<float>", &m_pEventData->m_pSave_cx);
  m_pTree->Branch("Save_cy", "vector<float>", &m_pEventData->m_pSave_cy);
  m_pTree->Branch("Save_cz", "vector<float>", &m_pEventData->m_pSave_cz);
  m_pTree->Branch("Save_e", "vector<float>", &m_pEventData->m_pSave_e);
  m_pTree->Branch("Save_t", "vector<float>", &m_pEventData->m_pSave_t);
  m_pTree->Branch("Save_trkid", "vector<int>", &m_pEventData->m_pSave_trkid);
  
  m_pNbEventsToSimulateParameter = new TParameter<int>("nbevents", m_iNbEventsToSimulate);
  m_pNbEventsToSimulateParameter->Write();

  m_pTreeFile->cd();
}


//******************************************************************/
// EndOfRun action/end of the simulation
//******************************************************************/
void LArSAnalysisManager::EndOfRun(const G4Run *){
 
  runTime->Stop();
  G4double dt = runTime->GetRealElapsed();
  // make tree structure
  TParameter<G4double> *dtPar = new TParameter<G4double>("G4RUNTIME",dt);
  dtPar->Write();

  m_pTreeFile->cd();

  m_pTreeFile->Write();
  m_pTreeFile->Close();
}

//******************************************************************/
//	BeginOfEvent action - for each beamed particle
//******************************************************************/
void LArSAnalysisManager::BeginOfEvent(const G4Event *){

  if(m_iLXeHitsCollectionID == -1)
  {
    G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
    m_iLXeHitsCollectionID = pSDManager->GetCollectionID("LArHitsCollection");
  } 
 
}

//******************************************************************/
// EndOfEvent action - getting all event data
//******************************************************************/

void LArSAnalysisManager::EndOfEvent(const G4Event *pEvent){
  _events->cd();

  G4HCofThisEvent* pHCofThisEvent = pEvent->GetHCofThisEvent();
  LArSLXeHitsCollection* pLXeHitsCollection = 0;
  LArSPmtHitsCollection* pPmtHitsCollection = 0;
 
  
  G4int iNbLXeHits = 0, iNbPmtHits = 0, iNbLScintHits = 0;
	
  if(pHCofThisEvent)
  {
      if(m_iLXeHitsCollectionID != -1)
      {
        pLXeHitsCollection = (LArSLXeHitsCollection *)(pHCofThisEvent->GetHC(m_iLXeHitsCollectionID));
        iNbLXeHits = (pLXeHitsCollection)?(pLXeHitsCollection->entries()):(0);
      }
//***2*** calling the pmt hit collection function and storing the event data
      if(m_iPmtHitsCollectionID != -1)
	  {
        pPmtHitsCollection = (LArSPmtHitsCollection *)(pHCofThisEvent->GetHC(m_iPmtHitsCollectionID));
        iNbPmtHits = (pPmtHitsCollection)?(pPmtHitsCollection->entries()):(0);
	  }
      
  }

  // get the event ID and primary particle information
  m_pEventData->m_iEventId = pEvent->GetEventID();
  m_pEventData->m_pPrimaryParticleType->push_back(m_pPrimaryGeneratorAction->GetParticleTypeOfPrimary());
  
  m_pEventData->m_fPrimaryX = m_pPrimaryGeneratorAction->GetPositionOfPrimary().x();
  m_pEventData->m_fPrimaryY = m_pPrimaryGeneratorAction->GetPositionOfPrimary().y();
  m_pEventData->m_fPrimaryZ = m_pPrimaryGeneratorAction->GetPositionOfPrimary().z();

  m_pEventData->m_fForcedPrimaryX = m_pPrimaryGeneratorAction->GetForcedPositionOfPrimary().x();
  m_pEventData->m_fForcedPrimaryY = m_pPrimaryGeneratorAction->GetForcedPositionOfPrimary().y();
  m_pEventData->m_fForcedPrimaryZ = m_pPrimaryGeneratorAction->GetForcedPositionOfPrimary().z();

  m_pEventData->m_fPrimaryE = m_pPrimaryGeneratorAction->GetEnergyOfPrimary() / keV;
  m_pEventData->m_fPrimaryW = pEvent->GetPrimaryVertex()->GetWeight();
 
  
  G4int iNbSteps = 0;
  G4int iLScintNbSteps = 0;
  G4float fTotalEnergyDeposited = 0.;
  G4float fLScintTotalEnergyDeposited = 0.;
 

	
  if(iNbLXeHits || iNbPmtHits || iNbLScintHits) // If there are any non zero hits 
  {
		// LXe hits
    for(G4int i=0; i<iNbLXeHits; i++)
    {
	  LArSLXeHit *pHit = (*pLXeHitsCollection)[i];

	  if(pHit->GetParticleType() != "opticalphoton")
      {
        m_pEventData->m_pTrackId->push_back(pHit->GetTrackId());
        m_pEventData->m_pParentId->push_back(pHit->GetParentId());
        m_pEventData->m_pParticleType->push_back(pHit->GetParticleType());
        m_pEventData->m_pParentType->push_back(pHit->GetParentType());
        m_pEventData->m_pCreatorProcess->push_back(pHit->GetCreatorProcess());
        m_pEventData->m_pDepositingProcess->push_back(pHit->GetDepositingProcess());
        m_pEventData->m_pX->push_back(pHit->GetPosition().x()/mm);
        m_pEventData->m_pY->push_back(pHit->GetPosition().y()/mm);
        m_pEventData->m_pZ->push_back(pHit->GetPosition().z()/mm);
        fTotalEnergyDeposited += pHit->GetEnergyDeposited()/keV;
        m_pEventData->m_pEnergyDeposited->push_back(pHit->GetEnergyDeposited()/keV);
        m_pEventData->m_pKineticEnergy->push_back(pHit->GetKineticEnergy()/keV);
        m_pEventData->m_pTime->push_back(pHit->GetTime()/ns);       
        m_pEventData->m_pPreMomDirX->push_back(pHit->GetPreMomentumDir().x());
        m_pEventData->m_pPreMomDirY->push_back(pHit->GetPreMomentumDir().y());
        m_pEventData->m_pPreMomDirZ->push_back(pHit->GetPreMomentumDir().z());
        m_pEventData->m_pPostMomDirX->push_back(pHit->GetPostMomentumDir().x());
        m_pEventData->m_pPostMomDirY->push_back(pHit->GetPostMomentumDir().y());
        m_pEventData->m_pPostMomDirZ->push_back(pHit->GetPostMomentumDir().z());
        m_pEventData->m_pPreKineticEnergy->push_back(pHit->GetPreKineticEnergy()/keV);
        m_pEventData->m_pPostKineticEnergy->push_back(pHit->GetPostKineticEnergy()/keV);
            
        iNbSteps++;
      }
      
    }


  }

//***3 defining the number of pmts

		G4int iNbTopPmts = 0;
		G4int iNbBottomPmts = 0;
		G4int iNbRingPmts = 0;
//***4 resizing m_pPmtHits array
		m_pEventData->m_pPmtHits->resize(iNbTopPmts+iNbBottomPmts, 0);



    for(G4int i=0; i<iNbPmtHits; i++)
    {
        (*(m_pEventData->m_pPmtHits))[(*pPmtHitsCollection)[i]->GetPmtNb()]++; //? 
        G4cout << "PMTID " << (*pPmtHitsCollection)[i]->GetPmtNb() << G4endl;  
		m_pEventData->m_iPmtNumber = (*pPmtHitsCollection)[i]->GetPmtNb();
    }   

  
    m_pEventData->m_iNbBottomPmtHits = accumulate(m_pEventData->m_pPmtHits->begin(), m_pEventData->m_pPmtHits->begin()+iNbBottomPmts, 0);
    m_pEventData->m_iNbTopPmtHits = accumulate(m_pEventData->m_pPmtHits->begin()+iNbBottomPmts, m_pEventData->m_pPmtHits->begin()+iNbBottomPmts+iNbTopPmts, 0);
    m_pEventData->m_iNbRingPmtHits = accumulate(m_pEventData->m_pPmtHits->begin()+iNbBottomPmts+iNbTopPmts, m_pEventData->m_pPmtHits->begin()+iNbBottomPmts+iNbTopPmts+iNbRingPmts, 0);
 //  // also write the header information + primary vertex of the empty events....
 m_pEventData->m_iNbSteps = iNbSteps;
 m_pEventData->m_iLScintNbSteps = iLScintNbSteps;
 m_pEventData->m_fTotalEnergyDeposited = fTotalEnergyDeposited;
 m_pEventData->m_fLScintTotalEnergyDeposited = fLScintTotalEnergyDeposited;
  

  // save only energy depositing events
  if(writeEmptyEvents)
  {
    m_pTree->Fill(); // write all events to the tree
  }
  else
  {
  // if(fTotalEnergyDeposited > 0.) m_pTree->Fill();
  if(fTotalEnergyDeposited > 0. || iNbPmtHits > 0) m_pTree->Fill(); // only events with some activity are written to the tree
  }
  m_pEventData->Clear(); 
  m_pTreeFile->cd();
}

void LArSAnalysisManager::Step(const G4Step *)
{
}

void LArSAnalysisManager::FillParticleInSave(G4int flag, G4int partPDGcode, G4ThreeVector pos, G4ThreeVector dir,  G4float nrg, G4float time, G4int trackID)
{
    m_pEventData->m_pSave_flag->push_back(flag);
    m_pEventData->m_pSave_type->push_back(partPDGcode);
    m_pEventData->m_pSave_x->push_back(pos.x()/mm);
    m_pEventData->m_pSave_y->push_back(pos.y()/mm);
    m_pEventData->m_pSave_z->push_back(pos.z()/mm);
    m_pEventData->m_pSave_cx->push_back(dir.x());
    m_pEventData->m_pSave_cy->push_back(dir.y());
    m_pEventData->m_pSave_cz->push_back(dir.z());
    m_pEventData->m_pSave_e->push_back(nrg/keV);
    m_pEventData->m_pSave_t->push_back(time/ns);
    m_pEventData->m_pSave_trkid->push_back(trackID);
    m_pEventData->m_iNSave++;
}


