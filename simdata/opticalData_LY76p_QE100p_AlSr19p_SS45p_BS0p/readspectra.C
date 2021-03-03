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

void readspectra()
{

 static const int samples=4; // here the samples are actually the diff types of measurements
 string samplesnames[samples]={"Reflectivity_Tetratex", "TPBAbsorption", "TPBEmission","TPBOnTetratexEmission"};
 TH1F *hsp[samples]; TCanvas *c[samples];

 for (int s=0; s<samples; s++)
 { 
	hsp[s]=new TH1F("","",800, 0, 800);
 	string sinFile=samplesnames[s]+".dat";
	ifstream inFile(sinFile.c_str());
	if (!inFile.is_open()) 	{cout<< "arquivo nao encontrado = "<< sinFile << endl;}
	double wl, inten; int n=0;
	while(inFile>>wl>>inten)
	{
		n++;//cout<<n<<" "<<wl<<" "<<inten<<endl;
		hsp[s]->Fill(wl, inten);
	}

	c[s]= new TCanvas(); hsp[s]->Draw("P*CHIST");

	
  }


}

  /*auto TPBTable = new G4MaterialPropertiesTable();
  TPBTable->AddProperty     ("RINDEX",               ph_energies, TPB_refraction, NUMENTRIES_2);
  TPBTable->AddProperty     ("WLSABSLENGTH",         ph_energies, TPB_absorption, NUMENTRIES_2);
  TPBTable->AddProperty     ("WLSCOMPONENT",         ph_energies, TPB_emission,   NUMENTRIES_2);
  TPBTable->AddConstProperty("WLSTIMECONSTANT",      TPB_TimeConstant);
  TPBTable->AddConstProperty("WLSMEANNUMBERPHOTONS", TPB_QuantumEff);
  G4Material::GetMaterial("TPB")->SetMaterialPropertiesTable(TPBTable);

  TetratexOpTable->AddProperty("REFLECTIVITY", ph_energies, refl_Tetratex, NUMENTRIES_2);



*/




