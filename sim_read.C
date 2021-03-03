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

#include "readinput_sim.hh"
using namespace std;

// !!!!!!!!!!!! TO RUN THIS CODE, FIRST EXPORT THE NAME OF THE SIMULATION FOLDER YOU WANT TO READ:
// $ export readsim_env="sim1_absorber" && source LArS_bashrc 
// THEN RUN: $ readsim # which is an alias set in LArS_bashrc

void sim_read()
{

 string sim_n(getenv("readsim_env")); //simulation name to be read from / where the png data will be saved

// ########### The values below may be a bit sample dependent
 bool saveas=false;//true; // does not save png files
 
 double min=320, max=1200; 
 int const n_q=4; // here is constant, since n_qLY and n_qQE can vary
 int add_width_ref=40;

 int init_fit_PE[n_q]={250, 300, 380, 420}; 
 int end_fit_PE[n_q]={620,750, 900,1150}; // int end_fit_PE[n_qLY]={600,800, 1000,1200};
 int n_bins[n_q]={300, 320, 360, 460}; int step=3; double first_bin=0.5;
 int corr_ly[n_q]={0, 50, 100, 175};
 int corr_ly_TTX=0;

// ########### change values here to zoom the plots and when necessary to adjust histograms and fits

 if (sim_n=="sim2_absorber" || sim_n=="sim3_absorber" || sim_n=="sim2_TTX") {min=450; max=750;}
 if (sim_n=="sim1_TTX") {min=450; max=1000; corr_ly_TTX=145;}
//if (s_samples[which_sample]=="TTX")

// ##############################

 int it=0;

 TCanvas *cref = new TCanvas("cref","cref", 1200, 950);
 cref->Divide(2,2);
 TCanvas *chist;
 TCanvas *c1= new TCanvas(); 
 TLegend *lg, *glg;
 TGraphErrors *g_ref;

 double PE_values[n_AlS_r], PE_values_sigma[n_AlS_r];

 // double PE_measured[n_samples]={520.63, 596.94, 1052.33, 1273};// data for 1350V  for "absorber", "TTX", "PEN", "WLSR"
 double PE_measured[n_samples]={592.52, 640.78, 1080.31, 1184};// data for 1500V //double exp_ref[n_samples]={0.7, 11, 50, 60};

 TH1F *PE_hist[n_AlS_r];

 //LY loop
 for (int i=0; i<n_qLY; i++)
 {
  //if (i>1) break;
  double qLY=q_factor_LY[i];
  stringstream sqLY; sqLY<<qLY*100; 

  //PMT QE loop
  for (int j=0; j<n_qQE; j++)
  {
   //if (j>1) continue;
   double qQE=q_factor_QE[j];
   stringstream sqQE; sqQE<<qQE*100;

   string svaryLYQE="_LY"+sqLY.str()+"p_QE"+sqQE.str();
   glg= new TLegend(0.1, 0.65, 0.9, 0.89); 
      
   for (int tr=0; tr<n_ref_TTX; tr++)
   {
    double TTXref=ref_TTX[tr];
    stringstream sTTX_r; sTTX_r<<TTXref*100;

   for(int ss=0; ss<n_AlS_SS; ss++)
   {
    double AlSss=AlS_SS[ss];
    if (ss==1 ) continue;//break;
    stringstream sAlSss; sAlSss<<AlSss*100;

    for (int bs=0; bs<n_AlS_BS; bs++)
    {
     //if (bs>0) break;
     double AlSbs=AlS_BS[bs];
     stringstream sAlSbs; sAlSbs<<AlSbs*100;
 
    //reflectivity loop 
    for (int r=0; r<n_AlS_r; r++)
    {
	//if (r>1) break;
	//if ((it>0 && it<432) || it>442) {it++; continue; }
	double AlSr=AlS_r[r];
	stringstream sAlSr; sAlSr<<AlSr*100;

	cout<<"\n\n####****#### Starting reading iteration: "<<it<<" ####****####\n\n"<<endl;
	cout<<"  qLY: "<<sqLY.str()<<", qQE: "<<sqQE.str()<<", rTTX: "<<sTTX_r.str()<<", AlS_r: "<<sAlSr.str()<<", AlS_SS: "<<sAlSss.str()<<", AlS_BS: "<<sAlSbs.str()<<endl;

        //if(!itExists(output_dir[0])) system(("mkdir "+output_dir[0]).c_str());// mkdir some figure file
	string svaryref="_AlSr"+sAlSr.str()+"p_SS"+sAlSss.str()+"p_BS"+sAlSbs.str()+"p";
	string svaryttx; if (n_ref_TTX>1) {svaryttx="p_TTXr"+sTTX_r.str();} else {svaryttx="";}
	string svarydata=svaryLYQE+svaryttx+"p"+svaryref;
	string new_optdata=LArSpath+"/"+output_dir[0]+"/opticalData"+svarydata;


	string inputfile=output_dir[1]+"/"+sim_n+"/events_"+s_samples[which_sample]+"_"+N_events+svarydata+".root";
	cout<<inputfile<<endl;
	TFile *pFile = new TFile(inputfile.c_str());
	TDirectoryFile *pDir = (TDirectoryFile *)pFile->Get("events");

	int ji; if (j>i) {ji=j;} else {ji=i;}
	string hist_name="PE_hist_R"+sAlSr.str();
	double last_bin=first_bin+n_bins[ji]*step;
	PE_hist[r] = new TH1F(hist_name.c_str(),"",n_bins[ji],first_bin, last_bin);
	TTree *pTree = (TTree *) pDir->Get("events");
	c1->cd(); pTree->Draw(("pmthits>>"+hist_name).c_str()); 
	//int init_int=100/step; spectrum_int=PE_hist[r]->Integral(init_int,last_bin);

	if (r==init_ref && bs==0 && ss==0) 
	{
		chist= new TCanvas("chist", "chist", 800, 500);
		PE_hist[r]->Draw();
		lg= new TLegend(0.7, 0.1, 0.85, 0.98);
	}
	else {chist->cd(); PE_hist[r]->Draw("same");} 
	chist->SetLogy();
	PE_hist[r]->SetLineColor(kMagenta-r+3*ss); PE_hist[r]->SetLineWidth(2);
	PE_hist[r]->GetYaxis()->SetTitle("Counts");
	PE_hist[r]->GetXaxis()->SetTitle("PE");
	gStyle->SetOptStat(0);


	int adj_initfit= init_fit_PE[j]+r*add_width_ref+corr_ly[i]+corr_ly_TTX;
	int adj_endfit= end_fit_PE[j]+r*add_width_ref+corr_ly[i]+corr_ly_TTX;
	string fname="f"+svaryref;
	TF1  *f1 = new TF1(fname.c_str(),"gaus", adj_initfit, adj_endfit);
	PE_hist[r]->Fit(fname.c_str(), "R"); 
	int mean_gaus=f1->GetParameter(1); //cout <<" ##############" <<mean_gaus<<endl;
	double sigma=f1->GetParameter(2); //double FWHM=2.35482*sigma;
	PE_values[r]=f1->GetParameter(1); PE_values_sigma[r]=f1->GetParameter(2); 
	stringstream smean; smean<<mean_gaus; smean<<setprecision(0);
	cout<<"  i, j, r: "<<i<<" "<<j<<" "<<r<<" "<<" initfit, endfit "<<adj_initfit<<" "<<adj_endfit<<endl;

	string lg_smean=sAlSr.str()+"% | "+smean.str()+" PE";
	// lg->AddEntry(PE_hist[r],lg_smean.c_str(), "l");

	//AlS_r[r]*=100;

	it++;
     }// end r loop
     g_ref= new TGraphErrors(n_AlS_r, AlS_r, PE_values, 0, 0);
     cref->cd(i+1); if (bs==0 && ss==0 && j==0 && tr==0)  {g_ref->Draw("APL");} else  {g_ref->Draw("PL");}
     g_ref->GetYaxis()->SetTitle("Mean PE value");  g_ref->GetYaxis()->SetTitleOffset(1.3);
     g_ref->GetXaxis()->SetTitle("Source Reflectivity"); 
     g_ref->SetTitle(("LY: "+sqLY.str()+"% NV").c_str()); 
     g_ref->SetMarkerStyle(20+ss); if (n_AlS_BS>1) g_ref->SetMarkerStyle(20+bs); if (n_ref_TTX>1) g_ref->SetMarkerStyle(20+tr); g_ref->SetMarkerSize(1+0.1*tr);
     int col=kMagenta+bs+3*ss; if (col==621) col=611;
     g_ref->SetMarkerColor(col); g_ref->SetLineColor(col); g_ref->SetLineStyle(3-ss); g_ref->SetLineWidth(tr+1);
     glg->SetTextSize(0.035); glg->SetBorderSize(0); glg->SetFillStyle(0);
     g_ref->SetMinimum(min); g_ref->SetMaximum(max);
     string slgTTX, slg; slg ="Sim: SS("+sAlSss.str()+"%), BS("+sAlSbs.str()+"%)";
     if (n_ref_TTX>1) {slgTTX="R_ttx("+sTTX_r.str()+"%)"; slg ="Sim: SS("+sAlSss.str()+"%), "+slgTTX;}
     glg->AddEntry(g_ref,slg.c_str() , "lp");

    }// end bs loop
   }// end ss loop
   //cref->SaveAs(("../png/Reflectivity_"+s_samples[which_sample]+"_"+N_events+svaryLYQE+"p.png").c_str());
   }
  if (saveas) chist->SaveAs(("../png/"+sim_n+"/PE_hist_sim_"+s_samples[which_sample]+"_"+N_events+svaryLYQE+".png").c_str());
  }//end j QE loop
 

 //chist->cd();
 //lg->SetTextSize(0.035); lg->SetBorderSize(0);lg->SetFillStyle(0); lg->SetHeader("  Reflectivity | Mean"); 
 //lg->Draw();

 cref->cd(i+1);
 TText *t;
 int meas_line_color=9, meas_line_style=9;
 for (int s=0; s<(which_sample+1); s++)
 {
 	double x1=g_ref->GetXaxis()->GetXmin(), x2=g_ref->GetXaxis()->GetXmax(), y1=PE_measured[s],y2=y1;
	TLine *PElines= new TLine(x1, y1, x2, y2);
	PElines->Draw(); PElines->SetLineStyle(meas_line_style); PElines->SetLineColor(meas_line_color);//30); 
	PElines->SetLineWidth(3);
	t = new TText(x1+(x2-x1)*0.15,y1+14,(s_samples[s]).c_str());
	//if (s%2==0) t = new TText(80,y1-75,(s_samples[i]).c_str());
	t->SetTextAlign(22);  t->SetTextColor(meas_line_color); t->SetTextFont(43); t->SetTextSize(18);
	t->Draw();

	TArrow *ar= new TArrow(0.282, min+100, 0.282,max-50,0.022,"|>");
	if (n_ref_TTX>1)  ar= new TArrow(0.21, min+20, 0.21,max-20,0.022,"|>");
	ar->Draw(); //ar->SetLineStyle(2); 
	ar->SetLineColor(30); ar->SetFillColor(30); ar->SetLineWidth(2);

	//string lytext="LY: 70, 85, 90, 115 % NV";
	TText *t_ar = new TText(0.275,750,"PMT QE: 70, 85, 100, 115 % NV");
	stringstream sTTX_r0, sTTX_rf; 
	if (n_ref_TTX>1) {sTTX_r0<<ref_TTX[0]*100; sTTX_rf<<ref_TTX[n_ref_TTX-1]*100;
	t_ar = new TText(0.215,min+(max-min)*0.32, ("Increasing reflectivity from "+sTTX_r0.str()+" to "+sTTX_rf.str()+"%").c_str());}
	t_ar->SetTextAngle(90); t_ar->SetTextAlign(22); 
	t_ar->SetTextColor(30); t_ar->SetTextFont(43); t_ar->SetTextSize(18);
	t_ar->SetTextColor(30); t_ar->SetTextFont(43); t_ar->SetTextSize(18);
	t_ar->Draw();
 }

 TLegendEntry* l1 =  glg->AddEntry(t, "Measured", "l");
 l1->SetLineColor(meas_line_color);  l1->SetLineStyle(meas_line_style);  l1->SetTextColor(meas_line_color);
 glg->SetNColumns(2); 
 if (i==0) glg->Draw();
 //cref->SaveAs(("../png/Reflectivity_"+s_samples[which_sample]+"_"+N_events+"_LY"+sqLY.str()+"p.png").c_str());
 }// end LY i loop
 if (saveas) cref->SaveAs(("../png/"+sim_n+"/Reflectivity_"+s_samples[which_sample]+"_"+N_events+".png").c_str());
}










