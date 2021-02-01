//XEBRA Header Files
#include "LArSPrimaryGeneratorAction.hh"
#include "LArSDetectorConstruction.hh"
#include "LArSAnalysisManager.hh"
#include "LArSStackingAction.hh"
#include "LArSSteppingAction.hh"
#include "LArSRunAction.hh"
#include "LArSEventAction.hh"
#include "LArSPhysicsList.hh"

//Additional Header Files
#include "fileMerger.hh"

//C++ Header Files
#include <string>
#include <sstream>
#include <unistd.h>
#include <chrono>
//G4Header Files
#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4GeneralParticleSource.hh>


using namespace std::chrono; 


void usage();

int
main(int argc, char **argv)
{    
  std::string git_tag = "0.0.1";
  auto start = high_resolution_clock::now(); 
  G4cout << G4endl << "Welcome to Liquid Argon Test Stand (LArS) MC Version " << git_tag.c_str() << G4endl;
    
  // switches
  int c = 0;
  
  std::stringstream hStream;
	
  bool bInteractive = false;
  bool bVisualize = false;
  bool bVrmlVisualize = false;
  bool bQtVisualize = false;
  bool bOpenGlVisualize = false;
  bool bHepRepVisualize = false;
  bool bPreInitFromFile = false;
	
  bool bRunMacro = false;
  std::string hRunMacroFilename, hDataFilename, hPreInitFilename, hSamplename;
  std::string hCommand;
  int iNbEventsToSimulate = 0;
  
  // parse switches
  while((c = getopt(argc,argv,"v:f:o:p:n:i:w")) != -1)
  {
    switch(c)	{

      case 'v': 
        bVisualize = true;
        hStream.str(optarg);
        if(hStream.str() == "vrml")
          bVrmlVisualize = true;
        else if(hStream.str() == "opengl")
          bOpenGlVisualize = true;
        else if(hStream.str() == "qt")
          bQtVisualize = true;
        else if(hStream.str() == "heprep")
          bHepRepVisualize = true;
        hStream.clear();
        break;
        
      case 'f':
        bRunMacro = true;
        hRunMacroFilename = optarg;
        break;
        
      case 'o':
        hDataFilename = optarg;
        break;
				
      case 'p':
        bPreInitFromFile = true;
        hPreInitFilename = optarg;
        break;
        
      case 'n':
        hStream.str(optarg);
        hStream.clear();
        hStream >> iNbEventsToSimulate;
        break;
        
      case 'i':
        bInteractive = true;
        break;

      case 's':
        hSamplename = optarg;
        break;
        
      default:
        usage();
    }
  }
  

  if(hDataFilename.empty()) hDataFilename = "events.root";
  
  // create the run manager
  G4RunManager *pRunManager = new G4RunManager;

  // Detector Construction
  G4String detectorRoot = hDataFilename+"_DET";
  LArSDetectorConstruction *detCon = new LArSDetectorConstruction(detectorRoot); 
  pRunManager->SetUserInitialization(detCon);

  G4String physicsRoot = hDataFilename+"_PHYS";
  
  // Physics List
  LArSPhysicsList *physList = new LArSPhysicsList(physicsRoot);
  pRunManager->SetUserInitialization(physList);
    
  // create the primary generator action
  G4String generatorRoot = hDataFilename+"_GEN";
  LArSPrimaryGeneratorAction *pPrimaryGeneratorAction = new LArSPrimaryGeneratorAction(generatorRoot);
    
  // create an analysis manager object
  LArSAnalysisManager *pAnalysisManager = new LArSAnalysisManager(pPrimaryGeneratorAction);
  pAnalysisManager->SetDataFilename(hDataFilename);
  pAnalysisManager->SetDectorConstructor(detCon);

  
  // Visualization Manager
  G4VisManager* pVisManager = new G4VisExecutive;
  pVisManager->SetVerboseLevel(0);
  pVisManager->Initialize();  
  
  if(iNbEventsToSimulate) pAnalysisManager->SetNbEventsToSimulate(iNbEventsToSimulate);

  // set user-defined action classes
  pRunManager->SetUserAction(pPrimaryGeneratorAction);
  pRunManager->SetUserAction(new LArSStackingAction(pAnalysisManager));
  pRunManager->SetUserAction(new LArSRunAction(pAnalysisManager));
  pRunManager->SetUserAction(new LArSSteppingAction(pAnalysisManager));
  pRunManager->SetUserAction(new LArSEventAction(pAnalysisManager));
  
  // geometry IO
  G4UImanager* pUImanager = G4UImanager::GetUIpointer();
  
  if(bPreInitFromFile)
  {
    hCommand = "/control/execute " + hPreInitFilename;
    pUImanager->ApplyCommand(hCommand);
    //pAnalysisManager->AddMacroFile(hPreInitFilename);
  }

  // initialize it all....
  pRunManager->Initialize();
  
  G4UIExecutive * pUI = 0;
  G4UIsession * pUIsession = 0;
  if (bQtVisualize) {
      if(bInteractive) pUI = new G4UIExecutive(argc, argv, "Qt");
  } else {
      if(bInteractive) pUIsession = new G4UIterminal(new G4UItcsh);
  }
    
  if(bVisualize)
  {
      pUImanager->ApplyCommand("/vis/scene/create");
    if(bVrmlVisualize)
      pUImanager->ApplyCommand("/vis/open VRML2FILE");
    if( (bOpenGlVisualize) || (bQtVisualize) )
      pUImanager->ApplyCommand("/vis/open OGL 600x600-0+0");
    if(bHepRepVisualize)
      pUImanager->ApplyCommand("/vis/open HepRepFile");

    pUImanager->ApplyCommand("/vis/drawVolume");
    pUImanager->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 90 0 deg");
    pUImanager->ApplyCommand("/vis/viewer/set/upVector 0 0 1");
    pUImanager->ApplyCommand("/vis/viewer/zoom 5.0");
    pUImanager->ApplyCommand("/vis/scene/add/trajectories");
    pUImanager->ApplyCommand("/vis/scene/add/hits");
    pUImanager->ApplyCommand("/tracking/storeTrajectory 1");
    pUImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
	
    pUImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
    pUImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true");
    pUImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 5");
    pUImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawAuxPts true");
    pUImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setAuxPtsSize 5");
  }
  
  if(bRunMacro)
  {
    hCommand = "/control/execute " + hRunMacroFilename;
    pUImanager->ApplyCommand(hCommand);
    //pAnalysisManager->AddMacroFile(hRunMacroFilename);
  }

  G4cout << "Loaded preinit macro: " << hPreInitFilename << G4endl;
  //G4cout << "Loaded preinit_B macro: " << hPreInitBeltFilename << G4endl;
  //G4cout << "Loaded preinit_EF macro: " << hPreInitEFFilename << G4endl;
  //G4cout << "Loaded optical setup: " << hSetupOpticalFromFile << G4endl;
  G4cout << "Loaded run macro: " << hRunMacroFilename << G4endl;
  
  if(iNbEventsToSimulate)
  {
    hStream.str("");
    hStream.clear();
    hStream << "/run/beamOn " << iNbEventsToSimulate;
    pUImanager->ApplyCommand(hStream.str());
    
    G4cout << "Total number of events requested: " << iNbEventsToSimulate << G4endl;
  }
  
  if(bInteractive)
  {
    if (bQtVisualize) {
        pUImanager->ApplyCommand("/control/execute macros/ui.mac"); 
        pUI->SessionStart();
        delete pUI;
    } else {
        pUIsession->SessionStart();
        delete pUIsession;
    }
  }  
  
  delete pAnalysisManager;
  if(bVisualize) delete pVisManager;
  delete pRunManager;
  
  // merge the output files to one .... events.root
  vector<std::string> auxfiles;
  auxfiles.push_back(detectorRoot);
  auxfiles.push_back(physicsRoot);
  auxfiles.push_back(generatorRoot);

  fileMerger myMerger(hDataFilename,auxfiles);
  myMerger.Merge();
  myMerger.CleanUp();

  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start); 
  cout << duration.count()/1000000 << endl; 

  return 0;



}

void
usage()
{
  exit(0);
}
