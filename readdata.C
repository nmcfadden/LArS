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



using namespace std;

void readdata()
{
 
 int const n_samples=4; int which_sample=0, init_ref=0;
 string s_samples[n_samples]={"absorber", "TTX", "PEN", "WLSR"};
 string initbase_sfile[n_samples]={"events_3K_5MeV_photonyield_108p_185489_newgeo_R","events_TTX_1K_5MeV_photonyield_108p_185489_newgeo_R","", "events_WLSR_1K_5MeV_photonyield_108p_185489_newgeo_E"};
 string endbase_sfile[n_samples]={"p.root","p.root","","p_noref.root"};

 TCanvas *chist;
 TCanvas *c1= new TCanvas(); 
 TLegend *lg= new TLegend(0.7, 0.7, 0.85, 0.89);
 lg->SetTextSize(0.035); lg->SetBorderSize(0);lg->SetFillStyle(0); lg->SetHeader("  Reflectivity | Mean"); 

 int n_bins=800, step=3; double first_bin=0.5, last_bin=first_bin+n_bins*step;
 int init_fit_PE=400, end_fit_PE=3000; 
 
 int const n_ref=9;
 double ref[n_ref]={0.007,0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};//, 0.9}; // reflectivity values
 double PE_values[n_ref], PE_values_sigma[n_ref];


 double PE_measured[n_samples]={520, 595,1080,1200}; //double exp_ref[n_samples]={0.7, 11, 50, 60};
 TH1F *PE_hist[n_ref];

 for (int r=init_ref; r<n_ref; r++)
 {
	//if (r>3 && r<7) continue;
	int s=which_sample;
	int ref_int=ref[r]*100; stringstream ref_p; ref_p<<ref_int; ref_p<<setprecision(2);
	string inputfile=initbase_sfile[s]+ref_p.str()+endbase_sfile[s];
	cout<<inputfile<<endl;
	TFile *pFile = new TFile(inputfile.c_str());
	TDirectoryFile *pDir = (TDirectoryFile *)pFile->Get("events");

	string hist_name="PE_hist_R"+ref_p.str();
	PE_hist[r] = new TH1F(hist_name.c_str(),"",n_bins,first_bin, last_bin);
	TTree *pTree = (TTree *) pDir->Get("events");
	c1->cd(); pTree->Draw(("ntpmthits>>"+hist_name).c_str()); 
	//int init_int=100/step; spectrum_int=PE_hist[r]->Integral(init_int,last_bin);

	if (r==init_ref) {chist= new TCanvas("chist", "chist", 800, 500); PE_hist[r]->Draw();}
	else if (r%2==0) {chist->cd(); PE_hist[r]->Draw("same");} 
	chist->SetLogy();
	PE_hist[r]->SetLineColor(kMagenta+r); PE_hist[r]->SetLineWidth(2);
	PE_hist[r]->GetYaxis()->SetTitle("Counts");
	PE_hist[r]->GetXaxis()->SetTitle("PE");
	gStyle->SetOptStat(0);

	if (s==0) {if (ref[r]>0.5){ init_fit_PE=800; PE_hist[r]->SetLineStyle(2);} if (ref[r]>0.75) init_fit_PE=1650;}
	else if (s==3) {if (ref[r]>0.){ init_fit_PE=1000; PE_hist[r]->SetLineStyle(2);} if (ref[r]>0.75) init_fit_PE=1000;}

	TF1  *f1 = new TF1("f1","gaus", init_fit_PE, end_fit_PE);
	PE_hist[r]->Fit("f1", "R"); 
	int mean_gaus=f1->GetParameter(1); //cout <<" ##############" <<mean_gaus<<endl;
	double sigma=f1->GetParameter(2); //double FWHM=2.35482*sigma;
	PE_values[r]=f1->GetParameter(1); PE_values_sigma[r]=f1->GetParameter(2); 
	stringstream smean; smean<<mean_gaus; smean<<setprecision(0);

	if (ref[r]==0.007) ref_p<<.7;
	string lg_smean=ref_p.str()+"% | "+smean.str()+" PE";
	if (r%2==0 || s>0) lg->AddEntry(PE_hist[r],lg_smean.c_str(), "l");

	ref[r]*=100;


 }
 c1->Close();
 lg->Draw();

 TGraphErrors *g_ref= new TGraphErrors(n_ref, ref, PE_values, 0, PE_values_sigma);
 TCanvas *cref = new TCanvas("cref","cref", 700, 500); g_ref->Draw("APL"); 
 g_ref->GetYaxis()->SetTitle("Mean PE value");  g_ref->GetXaxis()->SetTitle("Reflectivity [%]"); 
 g_ref->SetTitle(""); 
 g_ref->SetMarkerStyle(20); g_ref->SetMarkerColor(45); g_ref->SetLineColor(48);
 TLegend *glg= new TLegend(0.13, 0.7, 0.33, 0.89);
 glg->SetTextSize(0.035); glg->SetBorderSize(0); glg->SetFillStyle(0);
 glg->AddEntry(g_ref, "Simulated", "lp");
 TText *t;

 for (int i=0; i<n_samples-3; i++)
 {
 	double x1=0, x2=87, y1=PE_measured[i],y2=y1;
	TLine *PElines= new TLine(x1, y1, x2, y2);
	PElines->Draw(); PElines->SetLineStyle(2); PElines->SetLineColor(30);
	t = new TText(80,y1+75,(s_samples[i]).c_str());
	if (i%2==0) t = new TText(80,y1-75,(s_samples[i]).c_str());
	t->SetTextAlign(22);  t->SetTextColor(30); t->SetTextFont(43); t->SetTextSize(18);
	t->Draw();
	

 }
 TLegendEntry* l1 =  glg->AddEntry(t, "Measured", "l");
 l1->SetLineColor(30);  l1->SetLineStyle(2);  l1->SetTextColor(30);
 glg->Draw();
 
 cref->SaveAs("Reflectivity_absorber_new.png");
 chist->SaveAs("PE_hist_sim_absorber_new.png");



}










