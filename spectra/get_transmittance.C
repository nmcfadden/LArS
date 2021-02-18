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
#include "TAxis.h"
using namespace std;

void get_transmittance()
{ 

int nlines=33, n_head=0; 
double wavelength[nlines], transmittance[nlines];
double wl, abs;
string thicknes[4]={"acrylic","5", "6", "8"};
TCanvas *c1;
TLegend *lg= new TLegend(0.2, 0.65, 0.4, 0.88);//(0.68, 0.65, 0.88, 0.88);
//lg->SetHeader("thickness"); //, "C"); // option "C" allows to center the header
lg->SetTextSize(0.04);
lg->SetBorderSize(0);
lg->SetFillStyle(0);

for (int s=0; s<1; s++)
{

	stringstream s_number;
	s_number<<s+1;
	string slegend=thicknes[s];//+" mm";
	//string filename="Sample"+s_number.str()+".Sample.Raw.dat"; 
	string filename="TPBAbsorption.dat";
	string line;
	ifstream absfile(filename.c_str()); if(!absfile.is_open()) cout<<" file not found" <<endl; // no loop for diff files because there was only one file
	ofstream trfile("TPB_ref-trans.dat");  if(!trfile.is_open()) cout<<" file not found" <<endl; // ofstream creates a file to write in
	
	for (int j=0; j<n_head; j++)
	{
		getline(absfile, line);
	}
	for (int i=0; i<nlines; i++)
	{
	    absfile>>wl>>abs;    
	    wavelength[i]=wl;
	    transmittance[i]=1/pow(10,abs)*100;
	    cout<<wavelength[i]<<" "<<transmittance[i]<<endl;
	    trfile<<wavelength[i]<<" "<<transmittance[i]<<endl; // writes the data to the file. Not necessary in your case
	}

	TGraph *Tr= new TGraph(nlines, wavelength,transmittance);
	//TGraph *Abs= new TGraph(nlines, wavelength,transmittance);
	if (s==0) 
	{
		c1 = new TCanvas("c1","c1",800,800);
		Tr->Draw("APL"); //Tr->SetMarkerStyle(20); 
		//Tr->GetXaxis()->SetLimits(200., 890.);
		//Tr->SetMaximum(10);
		Tr->GetXaxis()->SetTitle("Wavelength [nm]"); Tr->GetXaxis()->SetTitleColor(kBlue+4);
		Tr->GetYaxis()->SetTitle("Transmittance [%]");Tr->GetYaxis()->SetTitleColor(kBlue+4);Tr->GetYaxis()->SetTitleSize(0.045);
		Tr->GetYaxis()->SetTitleOffset(1.1); Tr->GetXaxis()->SetTitleSize(0.045);
		Tr->SetTitle("");    
	} 
	else
	{
		Tr->Draw("PL");
	}
	Tr->SetLineColor(kBlue+s*2); Tr->SetMarkerColor(s+1); Tr->SetLineWidth(3);
	lg->AddEntry(Tr, slegend.c_str(),"l");
}
lg->Draw();
c1->SaveAs("TPB_ref-trans.png");
}








