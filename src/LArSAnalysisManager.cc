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

  m_pTree->Branch("eventid", &m_pEventData->m_iEventId, "eventid/I");

  //Step Info added by Neil
  m_pTree->Branch("vol","vector<string", &m_pEventData->m_pVol);
  m_pTree->Branch("creator","vector<string", &m_pEventData->m_pCreator);
  m_pTree->Branch("xp", "vector<float>", &m_pEventData->m_pX);
  m_pTree->Branch("yp", "vector<float>", &m_pEventData->m_pY);
  m_pTree->Branch("zp", "vector<float>", &m_pEventData->m_pZ);
  m_pTree->Branch("ed", "vector<float>", &m_pEventData->m_pEnergyDeposited);
  m_pTree->Branch("time", "vector<float>", &m_pEventData->m_pTime);
  m_pTree->Branch("ekin", "vector<float>", &m_pEventData->m_pKineticEnergy);
  m_pTree->Branch("trackid", "vector<int>", &m_pEventData->m_pTrackId);
  m_pTree->Branch("parentid", "vector<int>", &m_pEventData->m_pParentId);
  m_pTree->Branch("edproc", "vector<string>", &m_pEventData->m_pDepositingProcess);
  m_pTree->Branch("parenttype", "vector<string>", &m_pEventData->m_pParentType);
  m_pTree->Branch("etot", &m_pEventData->m_fTotalEnergyDeposited, "etot/F");
  

  m_pTree->Branch("VolPrim","vector<string>",&m_pEventData->m_pVolPrim);
  m_pTree->Branch("xPrim", "vector<float>", &m_pEventData->m_pXPrim);
  m_pTree->Branch("yPrim", "vector<float>", &m_pEventData->m_pYPrim);
  m_pTree->Branch("zPrim", "vector<float>", &m_pEventData->m_pZPrim);
  m_pTree->Branch("KEPrim", "vector<float>", &m_pEventData->m_pKErim);

  m_pTree->Branch("pmthits", "vector<int>", &m_pEventData->m_pPmtHits);
  
  // PMT hits 
  m_pTree->Branch("ntpmthits", &m_pEventData->m_iNbTopPmtHits, "ntpmthits/I");
  m_pTree->Branch("nrpmthits", &m_pEventData->m_iNbRingPmtHits, "nrpmthits/I");
  m_pTree->Branch("nbpmthits", &m_pEventData->m_iNbBottomPmtHits, "nbpmthits/I");
  m_pTree->Branch("nLSpmthits", &m_pEventData->m_iNbLSPmtHits, "nLSpmthits/I");
  
  m_pTree->Branch("PmtNb", &m_pEventData->m_iPmtNumber, "PmtNb/I");



  m_pTree->Branch("nsteps", &m_pEventData->m_iNbSteps, "nsteps/I");
  m_pTree->Branch("type", "vector<int>", &m_pEventData->m_pParticleType);
  m_pTree->Branch("creaproc", "vector<string>", &m_pEventData->m_pCreatorProcess);
  /*
  m_pTree->Branch("xp", "vector<float>", &m_pEventData->m_pX);
  m_pTree->Branch("yp", "vector<float>", &m_pEventData->m_pY);
  m_pTree->Branch("zp", "vector<float>", &m_pEventData->m_pZ);
  m_pTree->Branch("ed", "vector<float>", &m_pEventData->m_pEnergyDeposited);
  m_pTree->Branch("time", "vector<float>", &m_pEventData->m_pTime);
  m_pTree->Branch("ekin", "vector<float>", &m_pEventData->m_pKineticEnergy);
  */

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

      if(pHit->GetParticleType() == "opticalphoton") continue;
      m_pEventData->m_pTrackId->push_back(pHit->GetTrackId());
      m_pEventData->m_pParentId->push_back(pHit->GetParentId());
//      m_pEventData->m_pParticleType->push_back(pHit->GetParticleType());
      m_pEventData->m_pParentType->push_back(pHit->GetParentType());
      m_pEventData->m_pCreatorProcess->push_back(pHit->GetCreatorProcess());
      m_pEventData->m_pDepositingProcess->push_back(pHit->GetDepositingProcess());
      m_pEventData->m_pX->push_back(pHit->GetPosition().x()/mm);
      m_pEventData->m_pY->push_back(pHit->GetPosition().y()/mm);
      m_pEventData->m_pZ->push_back(pHit->GetPosition().z()/mm);
      //fTotalEnergyDeposited += pHit->GetEnergyDeposited()/keV;
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
    if(m_pEventData->m_fTotalEnergyDeposited > 0. || iNbPmtHits > 0) m_pTree->Fill(); // only events with some activity are written to the tree
  }
  m_pEventData->Clear(); 
  m_pTreeFile->cd();
}

void LArSAnalysisManager::Step(const G4Step *step)
{
  G4Track* track = step->GetTrack();
  G4StepPoint* postStepPoint = step->GetPostStepPoint();
  G4StepPoint* preStepPoint = step->GetPreStepPoint();

  G4VPhysicalVolume* physicalVolume = postStepPoint->GetPhysicalVolume();

  double eDep = step->GetTotalEnergyDeposit();
  //add Primary Information using prestep
  //The first step of a primary is defined as:
  //---having no Parent (poor primary)
  //---current step number is 1
  if( track->GetParentID() == 0 && track->GetCurrentStepNumber() == 1){
    int pid = track->GetDefinition()->GetPDGEncoding();
    int trackID = track->GetTrackID();
    G4String physVolName = preStepPoint->GetPhysicalVolume()->GetName();
    int t = preStepPoint->GetGlobalTime();
    double kineticE = preStepPoint->GetKineticEnergy();
    //Prestep point used for intial position of primary
    G4ThreeVector position = preStepPoint->GetPosition();
    G4ThreeVector localPosition = step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(position);
    G4ThreeVector momentum = preStepPoint->GetMomentumDirection();
    m_pEventData->m_pVolPrim->push_back(physVolName);
    m_pEventData->m_pXPrim->push_back(position.x());
    m_pEventData->m_pYPrim->push_back(position.y() );
    m_pEventData->m_pZPrim->push_back(position.z());
    m_pEventData->m_pKErim->push_back(kineticE);
    
  }
  if(fPastTrackPrimaryID != track->GetTrackID()){
    fPastTrackPrimaryID = track->GetTrackID();
  }
  const G4VProcess* creator = track->GetCreatorProcess();
  G4String creatorName;
  if(creator) creatorName = creator->GetProcessName();

  int pid = track->GetDefinition()->GetPDGEncoding();
  int trackID = track->GetTrackID();
  int parentTrackID = track->GetParentID();
  double stepLength = step->GetStepLength();
  double totalTrackLength = track->GetTrackLength();
 
  //If you use the pre point you never find tracks that stop in the SiPM,
  G4String physVolName;
  if(postStepPoint->GetPhysicalVolume() != NULL)
    physVolName = postStepPoint->GetPhysicalVolume()->GetName();
  G4String prePhysVolName;
  if(preStepPoint->GetPhysicalVolume()  != NULL)
    prePhysVolName = preStepPoint->GetPhysicalVolume()->GetName();

  double t = postStepPoint->GetGlobalTime();
  double kineticE = postStepPoint->GetKineticEnergy();

  const G4VProcess* processDefinedStep = postStepPoint->GetProcessDefinedStep();
  string procName = (processDefinedStep) ?  processDefinedStep->GetProcessName() : "";
  G4ThreeVector position = postStepPoint->GetPosition();
  G4ThreeVector momentum = postStepPoint->GetMomentum();
  int iStep = track->GetCurrentStepNumber();
  
  // Kill (anti)neutrinos regardless
  if(pid == -12 || pid == 12) step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
  
  //Kill All long steps
  if(iStep >= 10000 ){
    step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
    G4cout<<"Killing track for max Nstep...iStep "<<iStep<<", maxSteps is "<<10000<<", last volume step was in is "<<physVolName<<G4endl;
  }

  G4ThreeVector localPosition = step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(position);

  //Do not write all steps
  if(eDep == 0) return;
  m_pEventData->m_pVol->push_back(physVolName);
  m_pEventData->m_pCreator->push_back(creatorName);
  m_pEventData->m_pX->push_back(position.x()/mm);
  m_pEventData->m_pY->push_back(position.y()/mm);
  m_pEventData->m_pZ->push_back(position.z()/mm);
  m_pEventData->m_pEnergyDeposited->push_back(eDep/MeV);
  m_pEventData->m_pTime->push_back(t);
  m_pEventData->m_pKineticEnergy->push_back(kineticE/MeV);
  m_pEventData->m_pTrackId->push_back(trackID);
  m_pEventData->m_pParentId->push_back(parentTrackID);
  m_pEventData->m_pDepositingProcess->push_back(procName);
  m_pEventData->m_pParticleType->push_back(pid);
  m_pEventData->m_fTotalEnergyDeposited += eDep;

  if(physVolName.contains("pmt") || physVolName.contains("PMT")) m_pEventData->m_pPmtHits++;




  //Fill data class with step info:
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


