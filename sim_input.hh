#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream> 
#include <dirent.h>

 int const n_samples=4; 
 string s_samples[n_samples]={"absorber", "TTX", "PEN", "WLSR"}; 
 string mod_files[4]={"qFactor_LAr", "PMTQE","AlS_reflectivity","Reflectivity_Tetratex" };

 //####### these are the values that will value for each  iteration of the simulation #######

 int which_sample=1, init_ref=0; // note: apart from here the sample needs to be changed in the preinit file
 string sim_number="2"; 
 string sim_n="sim"+sim_number+"_"+s_samples[which_sample]; // new directories are created for this sim_n

 int const n_qLY=4, n_qQE=1, n_AlS_r=3, n_AlS_SS=3, n_AlS_BS=1, n_ref_TTX=3;
 double q_factor_LY[n_qLY]={0.64, 0.7, 0.76, 0.82};
 double q_factor_QE[n_qQE]={1};
 double AlS_r[n_AlS_r]={0.07, 0.13, 0.19};
 double AlS_SS[n_AlS_SS]={0.25, 0.4, 0.6};
 double AlS_BS[n_AlS_BS]={0.05};
 double AlS_SL=0.; //kept const


 double ref_TTX[n_ref_TTX]={0.007, 0.05, 0.1};
 string N_events="200";//number of events simulated in each iteration // Total: 4x1x3x3X1x4=144x200 = 28800 events

 //############################################################################################

 string output_dir[4]={"simdata", "simrootfiles", "log", sim_n};// These directories are created if they dont exist
 string runsimcmd_base="./bin/LArS -p macros/preinit.mac -f macros/run_alpha.mac -n "+N_events+" -o ";
 string LArSpath(getenv("LARSDIR"));

bool itExists(string dirName_in)
{
  int ans=0;
  DIR* dir = opendir(dirName_in.c_str()); //DIR type from #include <dirent.h>
  if (dir){ closedir(dir); ans=1; }
  return ans;
}
