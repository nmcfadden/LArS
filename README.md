# Demonstrator simulations
 Geant4 Monte Carlo for UZH Darwin Demonstrator Liquid Argon Research Setup (LARS): 
 Managed by Neil McFadden neil.mcfadden@physik.uzh.ch 23-09-2020




## Instructions for git:
- Be responsible when pushing changes
- With great power comes great responsibility
##Adding enviromental variables to your path:

#LArS
export LARSDIR=/path/to/LArS/MC/
export LARSOPTICALDATA=$LARSDIR/opticalData

## Compilation & Running Macros:
mkdir build bin
cd build
cmake ..
make
- this makes an executable in your /bin directory
./bin/LArS -p macros/preinit.mac -f macros/run_geantino_all.mac -n 10000
--> output in root file ("event.root", unless specified differently).

To run alphas on the bottom of the PMT cell do:
./bin/LArS -p macros/preinit.mac -f macros/run_alpha.mac -n 1

## Simple online root visualization: 
TFile *pFile = new TFile(inputfile+".root");
TDirectoryFile *pDir = (TDirectoryFile *) pFile->Get("events");

TDirectoryFile *pDir = (TDirectoryFile *) _file0->Get("events");
TTree *pTree = (TTree *) pDir->Get("events");
pTree->Draw("ntpmthits");
c1->SetLogy();



# LArS
