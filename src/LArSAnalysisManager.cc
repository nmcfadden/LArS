#include "LArSAnalysisManager.hh"


LArSAnalysisManager::LArSAnalysisManager(LArSPrimaryGeneratorAction *pPrimaryGeneratorAction){
  runTime = new G4Timer();
  
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
  gROOT->ProcessLine("#include <string>");

  //Event info
  m_pTree->Branch("etot", &m_pEventData->m_fTotalEnergyDeposited, "etot/F");
  m_pTree->Branch("nScintPhotons", &m_pEventData->m_nScintPhotons, "nScintPhotons/I");
  m_pTree->Branch("totalStepLength", &m_pEventData->m_pTotalStepLength,"TotalStepLength/F");
  m_pTree->Branch("eventid", &m_pEventData->m_iEventId, "eventid/I");

  //Step Info added by Neil
  m_pTree->Branch("vol","vector<string", &m_pEventData->m_pVol);
  m_pTree->Branch("xp", "vector<float>", &m_pEventData->m_pX);
  m_pTree->Branch("yp", "vector<float>", &m_pEventData->m_pY);
  m_pTree->Branch("zp", "vector<float>", &m_pEventData->m_pZ);
  m_pTree->Branch("ed", "vector<float>", &m_pEventData->m_pEnergyDeposited);
  m_pTree->Branch("time", "vector<float>", &m_pEventData->m_pTime);
  m_pTree->Branch("ekin", "vector<float>", &m_pEventData->m_pKineticEnergy);
  m_pTree->Branch("trackid", "vector<int>", &m_pEventData->m_pTrackId);
  m_pTree->Branch("parentid", "vector<int>", &m_pEventData->m_pParentId);
  m_pTree->Branch("edproc", "vector<string>", &m_pEventData->m_pDepositingProcess);
  m_pTree->Branch("type", "vector<int>", &m_pEventData->m_pParticleType);
  m_pTree->Branch("creaproc", "vector<string>", &m_pEventData->m_pCreatorProcess);
  m_pTree->Branch("stepLength", &m_pEventData->m_pStepLength);

  //Primary Information
  m_pTree->Branch("VolPrim","vector<string>",&m_pEventData->m_pVolPrim);
  m_pTree->Branch("xPrim", "vector<float>", &m_pEventData->m_pXPrim);
  m_pTree->Branch("yPrim", "vector<float>", &m_pEventData->m_pYPrim);
  m_pTree->Branch("zPrim", "vector<float>", &m_pEventData->m_pZPrim);
  m_pTree->Branch("KEPrim","vector<float>",&m_pEventData->m_pKEPrim);

  // PMT hits 
  m_pTree->Branch("pmthits", &m_pEventData->m_pPmtHits,"m_pPmtHits/I");

  m_pNbEventsToSimulateParameter = new TParameter<int>("nbevents", m_iNbEventsToSimulate);
  m_pNbEventsToSimulateParameter->Write();

  m_pTreeFile->cd();

  //Setting sensitive volumes
  G4PhysicalVolumeStore* volumeStore = G4PhysicalVolumeStore::GetInstance();
  G4int nVolumes = (G4int) volumeStore->size();
  G4String candidateList;
  G4cout<<"There are "<<nVolumes<<" defined, the following volumes will have stepping information stored in them if energy is deposited:"<<G4endl;
  for(G4int i=0;i<nVolumes;i++) {
    G4VPhysicalVolume* physicalVolume = (*volumeStore)[i];
    candidateList = (*volumeStore)[i]->GetName();
    int sensVolID = m_pDetCon->SetSensitiveVolumes(candidateList);
    m_pSensitiveIDOfPhysicalVol[physicalVolume] = sensVolID;
    if(sensVolID != 0) G4cout<<"\tVolume name "<<candidateList<<", sensitive volume ID: "<<sensVolID<<G4endl;
  }
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

}

//******************************************************************/
// EndOfEvent action - getting all event data
//******************************************************************/

void LArSAnalysisManager::EndOfEvent(const G4Event *){
  _events->cd();
  // save only energy depositing events
  if(writeEmptyEvents)
  {
    m_pTree->Fill(); // write all events to the tree
  }
  else
  {
    // if(fTotalEnergyDeposited > 0.) m_pTree->Fill();
    if(m_pEventData->m_fTotalEnergyDeposited > 0. || m_pEventData->m_pPmtHits > 0) m_pTree->Fill(); // only events with some activity are written to the tree
  }
  m_pEventData->Clear(); 
  m_pTreeFile->cd();
}

void LArSAnalysisManager::Step(const G4Step *step){

  OpticalBoundaryInformation(step);

  G4Track* track = step->GetTrack();
  G4StepPoint* postStepPoint = step->GetPostStepPoint();
  G4StepPoint* preStepPoint = step->GetPreStepPoint();

  G4VPhysicalVolume* physicalVolume = postStepPoint->GetPhysicalVolume();
  int sensVolID = m_pSensitiveIDOfPhysicalVol[physicalVolume];
  
  double eDep = step->GetTotalEnergyDeposit();
  //add Primary Information using prestep
  //The first step of a primary is defined as:
  //---having no Parent (poor primary)
  //---current step number is 1
  if( track->GetParentID() == 0 && track->GetCurrentStepNumber() == 1){
    /*
    int pid = track->GetDefinition()->GetPDGEncoding();
    int trackID = track->GetTrackID();
    int t = preStepPoint->GetGlobalTime();
    */
    G4String physVolName = preStepPoint->GetPhysicalVolume()->GetName();
    double kineticE = preStepPoint->GetKineticEnergy();
    //Prestep point used for intial position of primary
    G4ThreeVector position = preStepPoint->GetPosition();
    G4ThreeVector localPosition = step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(position);
    G4ThreeVector momentum = preStepPoint->GetMomentumDirection();
    m_pEventData->m_pVolPrim->push_back(physVolName);
    m_pEventData->m_pXPrim->push_back(position.x());
    m_pEventData->m_pYPrim->push_back(position.y() );
    m_pEventData->m_pZPrim->push_back(position.z());
    m_pEventData->m_pKEPrim->push_back(kineticE);
    
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
  //double totalTrackLength = track->GetTrackLength();

  //If you use the pre point you never find photons tracks that stop in detectors,
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
  //count scintillation photons that were created
  if(creatorName == "Scintillation" && iStep == 1){
    m_pEventData->m_nScintPhotons++;
  }

  //Do not write all steps
  if(eDep == 0 || sensVolID == 0) return;

  m_pEventData->m_pVol->push_back(physVolName);
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
  m_pEventData->m_pCreatorProcess->push_back(creatorName);
  m_pEventData->m_pStepLength->push_back(stepLength);
  m_pEventData->m_pTotalStepLength += stepLength;
  if( G4ParticleTable::GetParticleTable()->FindParticle("opticalphoton") != track->GetDefinition() ) m_pEventData->m_fTotalEnergyDeposited += eDep;

  //PMT specific information
  if(physVolName.contains("pmt") || physVolName.contains("PMT")){
    m_pEventData->m_pPmtHits++;

  }
}

//Fill Step info with Optical Boundary Information
void LArSAnalysisManager::OpticalBoundaryInformation(const G4Step *step){
  G4OpBoundaryProcessStatus boundaryStatus           = Undefined;
  static G4ThreadLocal G4OpBoundaryProcess* boundary = nullptr;
  G4StepPoint* thePostPoint    = step->GetPostStepPoint();
  
  // find the boundary process only once
  if(!boundary) {
    G4ProcessManager* pm = step->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses     = pm->GetProcessListLength();
    G4ProcessVector* pv  = pm->GetProcessList();
    for(G4int i = 0; i < nprocesses; ++i){
      if((*pv)[i]->GetProcessName() == "OpBoundary"){
        boundary = (G4OpBoundaryProcess*) (*pv)[i];
        break;
      }
    }
  }
  if(thePostPoint->GetStepStatus() == fGeomBoundary) {
    // Check to see if the particle was actually at a boundary
    // Otherwise the boundary status may not be valid
    if(fExpectedNextStatus == StepTooSmall){
      if(boundaryStatus != StepTooSmall){
        G4ExceptionDescription ed;
        ed << "LArSAnalysisManager::Step(): "
          << "No reallocation step after reflection!" << G4endl;
        G4Exception("LArSAnalysisManager::Step()", "", FatalException, ed,"Something is wrong with the surface normal or geometry");
      }
    }
    fExpectedNextStatus = Undefined;
    switch(boundaryStatus){
      case Absorption:
      case FresnelReflection:
      case TotalInternalReflection:
      case LambertianReflection:
      case LobeReflection:
      case SpikeReflection:
      case BackScattering:
      default:
        break;
    }
  }
}

