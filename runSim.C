#include "TVectorD.h"
#include "TVectorT.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream> 
#include <TROOT.h>
#include <TFile.h>
#include <TMath.h>
#include "TTree.h" 
#include "TBranch.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TF1.h"
#include <vector>
#include "TLegend.h"
#include "TColor.h"
#include "TAxis.h"
#include "TH1D.h"
#include <dirent.h>

#include "sim_input.hh"


using namespace std;


// to run the program: 
//$ source LArS_bashrc && root -l runSim.C 
// or directly root -l runSim.C, in case you have already the necessary paths loaded

void runSim()
{

 int it=0;

 //LY loop
 for (int i=0; i<n_qLY; i++)
 {
  double qLY=q_factor_LY[i];
  stringstream sqLY; sqLY<<qLY*100; 

  //PMT QE loop
  for (int j=0; j<n_qQE; j++)
  {
   double qQE=q_factor_QE[j];
   stringstream sqQE; sqQE<<qQE*100;

   //reflectivity loop 
   for (int r=0; r<n_AlS_r; r++)
   {
    //if (r>1) break;
    double AlSr=AlS_r[r];
    stringstream sAlSr; sAlSr<<AlSr*100;

    for(int ss=0; ss<n_AlS_SS; ss++)
    {
     double AlSss=AlS_SS[ss];
     //if (ss>0) break;
     stringstream sAlSss; sAlSss<<AlSss*100;

     for (int bs=0; bs<n_AlS_BS; bs++)
     {
	//if (it>2) break; 
	//if (bs>0) break;
      double AlSbs=AlS_BS[bs];
      stringstream sAlSbs; sAlSbs<<AlSbs*100;

      for (int tr=0; tr<n_ref_TTX; tr++)
      {
        double TTXref=ref_TTX[tr];
        stringstream sTTX_r; sTTX_r<<TTXref*100;

	cout<<"\n\n####****#### Starting simulation iteration: "<<it<<" ####****####\n\n"<<endl;
	cout<<"  qLY: "<<sqLY.str()<<", qQE: "<<sqQE.str()<<", rTTX: "<<sTTX_r.str()<<", AlS_r: "<<sAlSr.str()<<", AlS_SS: "<<sAlSss.str()<<", AlS_BS: "<<sAlSbs.str()<<endl;

        if(!itExists(output_dir[0])) system(("mkdir "+output_dir[0]).c_str());

	string svaryttx; if (n_ref_TTX>1) {svaryttx="p_TTXr"+sTTX_r.str();} else {svaryttx="";}
	string svarydata="_LY"+sqLY.str()+"p_QE"+sqQE.str()+svaryttx+"p_AlSr"+sAlSr.str()+"p_SS"+sAlSss.str()+"p_BS"+sAlSbs.str()+"p";
        string std_optdata(getenv("LARSOPTICALDATA"));
	string new_optdata=LArSpath+"/"+output_dir[0]+"/opticalData"+svarydata;
	system(("cp -Tr "+std_optdata+" "+new_optdata).c_str());
	
	// ## **** modifying LY data
	string sinoutfile=new_optdata+"/"+mod_files[0]+".dat";

 	auto LYGraph   = new TGraph(sinoutfile.c_str());
 	double *LYX=LYGraph->GetX();
  	double *LYY=LYGraph->GetY();

	ofstream newoutfile(sinoutfile.c_str());
	for (int l=0; l<LYGraph->GetN(); l++)
	{
		newoutfile<<LYX[l]<<" "<<LYY[l]*qLY<<endl;
	}
	newoutfile.close();

	// ## **** modifying QE data
	sinoutfile=new_optdata+"/"+mod_files[1]+".dat";

 	auto PMTQEGraph   = new TGraph(sinoutfile.c_str());
 	double *PMTWL=PMTQEGraph->GetX();
  	double *PMTEfficiency=PMTQEGraph->GetY();

	newoutfile.open(sinoutfile.c_str());
	for (int l=0; l<PMTQEGraph->GetN(); l++)
	{
		newoutfile<<PMTWL[l]<<" "<<PMTEfficiency[l]*qQE<<endl;
	}
	newoutfile.close();


	// ## **** modifying AlS (al disk source) reflectivity data
	sinoutfile=new_optdata+"/"+mod_files[2]+".dat";

 	auto AlS_rGraph = new TGraph(sinoutfile.c_str(), "%lg %lg");
 	double *AlS_rWL=AlS_rGraph->GetX();

	newoutfile.open(sinoutfile.c_str());
	for (int l=0; l<AlS_rGraph->GetN(); l++)
	{
		newoutfile<<AlS_rWL[l]<<" "<<AlSr<<" "<<AlSss<<" "<<AlS_SL<<" "<<AlSbs<<endl;
	}
	newoutfile.close();

	// ## **** modifying reflectivity of Tetratex
	sinoutfile=new_optdata+"/"+mod_files[3]+".dat";

 	auto TTX_rGraph = new TGraph(sinoutfile.c_str());
 	double *TTX_rWL=TTX_rGraph->GetX();
 	double *TTX_r=TTX_rGraph->GetY();

	newoutfile.open(sinoutfile.c_str());
	for (int l=0; l<TTX_rGraph->GetN(); l++)
	{
		if (TTX_rWL[l]<160) {newoutfile<<TTX_rWL[l]<<" "<<ref_TTX[tr]<<endl;}
		else {newoutfile<<TTX_rWL[l]<<" "<<TTX_r[l]<<endl;}
	}
	newoutfile.close();
	
	//----- create directories and run the simulation -------
	string outdir=output_dir[1]+"/"+output_dir[3];
	string outdirlog=output_dir[2]+"/"+output_dir[3]; 
	if (it==0) // it only checks/creates directories in the first iteration
	{ 
		if(!itExists(output_dir[1])) system(("mkdir "+output_dir[1]).c_str());
		if(itExists(outdir)) 
		{
			cout<<"\n\n sim directory "+output_dir[3]+" already exists!!! Are you sure you want to overwrite it? if so, press any key, otherwise pres ctrl+c to stop "<<endl;
			char cont; cin>>cont;
			system((" rm -rf "+outdir+" "+outdirlog).c_str());
		}
		system(("mkdir "+outdir+" "+outdirlog).c_str());
		system(("cp sim_input.hh "+outdirlog+"/sim_input.hh").c_str());
	}

	string outfile=outdir+"/events_"+s_samples[which_sample]+"_"+N_events+svarydata+".root";
	string logfile=outdirlog+"/"+s_samples[which_sample]+"_"+N_events+svarydata+".log";

	string runsimcmd=runsimcmd_base+outfile+" > "+logfile;

	cout<<"\n  opened: "<<new_optdata<<"\n  run command: "<<runsimcmd<<"\n\n####*******####*******####*******####*******####*******####"<<endl;
	system(("export LARSOPTICALDATA="+new_optdata+" && "+runsimcmd).c_str());
	// to run multiple jobs in batch mode: system('sbatch --job-name=%s --time=%s --output=%s (as in https://github.com/Physik-Institut-UZH/Gator_2020/blob/master/simulations/gator_v2.0/GatorSims.py)
	
	//--------------------------------------------------------

	it++;
      }
     }
    }
   }
  }
 }
}









