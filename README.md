# Demonstrator simulations
 Geant4 Monte Carlo for UZH Darwin Demonstrator Liquid Argon Research Setup (LARS): 
 Managed by Neil McFadden neil.mcfadden@physik.uzh.ch 23-09-2020




## Instructions for git:
- Be responsible when pushing changes
- With great power comes great responsibility

## Compilation & Running Macros:
mkdir build
cd build
cmake ..
make
- this makes an executable in your /bin directory
./bin/LArS -p macros/preinit.mac -f macros/run_geantino_all.mac -n 10000
--> output in root file ("event.root", unless specified differently). 

## Simple online root visualization: 
-  TFile *pFile = new TFile(inputfile+".root");
-  TDirectoryFile *pDir = (TDirectoryFile *) pFile->Get("events");
-  TTree *pTree = (TTree *) pDir->Get("events");
-  pTree->Draw("xp_pri:yp_pri:zp_pri");
# LArS
