void plotpmthits()
{

TCanvas *c1 = new TCanvas("c1", "c1", 900, 600); c1->Divide(2, 1);
TDirectoryFile *pDir = (TDirectoryFile *) _file0->Get("events");
TTree *pTree = (TTree *) pDir->Get("events");
c1->cd(1)->SetLogy();
pTree->Draw("pmthits");
c1->cd(2)->SetLogy();
pTree->Draw("nScintPhotons");

}
/*
	// Defining entries in the Tree //
	Long64_t nentries = inTree -> GetEntriesFast();

	// Defining variables in the Tree //
        float xp;
        float yp;
        float zp;

  	inTree->SetBranchAddress("xp", &xp);
	inTree->SetBranchAddress("yp", &yp);
	inTree->SetBranchAddress("zp", &zp);

///////////////////////////////////////////////////////////////////
///// Definig Vectors for the parameters
/////////////////////////////////////////////////////////////////

vector<float> x_position;
vector<float> y_position;
vector<float> z_position;

///////////////////////////////////////////////////////////////////
///// Starting Main Loop over tree entries 
/////////////////////////////////////////////////////////////////

    for(Long64_t jentry = 0; jentry<nentries; jentry++){

        if (jentry<200) cout<<"entrie  "<<jentry<<" "<<xp<<" "<<yp<<endl;

        inTree->GetEntry(jentry);

         x_position.push_back(xp);
         y_position.push_back(yp);
         z_position.push_back(zp);

      }

///////////////////////////////////////////////////////////////////
///// Definig the Graph
/////////////////////////////////////////////////////////////////


TGraph *gr = new TGraph( z_position.size(), &(x_position[0]), &(y_position[0]) );

///////////////////////////////////////////////////////////////////
///// Plot
/////////////////////////////////////////////////////////////////

TCanvas *c = new TCanvas("c", "graph draw options",618,148,920,780);
gr->GetYaxis()->SetTitle(" y [mm]");
gr->GetXaxis()->SetTitle(" x [mm]");
gr->SetMarkerStyle(6);
gr->SetMarkerColor(4);
gr->Draw("AP");*/
