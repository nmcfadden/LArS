

void example (void) {

/////////////////////////////////////////////////////////////////
///// Inititalize ROOT Input
/////////////////////////////////////////////////////////////////
	
	// Load Input file and Input Tree //
	TFile *inFile = new TFile("events.root");
	TTree *inTree = (TTree*) inFile->Get("events/events");


	// Defining entries in the Tree //
	Long64_t nentries = inTree -> GetEntriesFast();

	// Defining variables in the Tree //
        float xp_pri;
        float yp_pri;
        float zp_pri;

  	inTree->SetBranchAddress("xp_pri", &xp_pri);
	inTree->SetBranchAddress("yp_pri", &yp_pri);
	inTree->SetBranchAddress("zp_pri", &zp_pri);

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

        //cout<<"entrie  "<<jentry<<endl;

        inTree->GetEntry(jentry);

         x_position.push_back(xp_pri);
         y_position.push_back(yp_pri);
         z_position.push_back(zp_pri);

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
gr->Draw("AP");



}
