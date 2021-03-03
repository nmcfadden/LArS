# LArS simulations
 Geant4 Monte Carlo for UZH Liquid Argon Research Setup (LARS): 
 Managed by Neil McFadden neil.mcfadden@physik.uzh.ch and co-edited by Gabriela R. Araujo 

## Instructions for git:
- Be responsible when pushing changes
- With great power comes great responsibility
##Adding enviromental variables to your path:

#LArS
export LARSDIR=/path/to/LArS/MC/
export LARSOPTICALDATA=$LARSDIR/opticalData
-> see full LArS_bashrc file

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

## Simple script for root visualization:
root -l roofile.root
root [0] .x plotpmthits.C

## scripts for multiple simulation runs varying optical parameters
 - change parameters for the simulation in sim_input
 - change options for the simulation in preinit macro (fast simulation option produces smaller root files, use TTX, PEN, etc)
 - run the simulation:
	 $ source LArS_bashrc && root -l runSim.C  (this may create multiple directories for the output)
 - to read the simulation output, use the script sim_read.C


