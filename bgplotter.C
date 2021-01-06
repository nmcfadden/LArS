

void example (void) {

/////////////////////////////////////////////////////////////////
///// Inititalize ROOT Input
/////////////////////////////////////////////////////////////////
	
	// Load Input file and Input Tree //
	TFile *inFile = new TFile("/disk/data8/student/ryajur/demo/SS/ss_U238/proc/SS_U238_1e9_Proc.root");
	TTree *inTree = (TTree*) inFile->Get("events");


	// Defining entries in the Tree //
	Long64_t nentries = inTree -> GetEntriesFast();

	// Defining variables in the Tree //
        float xpri;
        float ypri;
        float zpri;


  	inTree->SetBranchAddress("xpri", &xpri);
	inTree->SetBranchAddress("ypri", &ypri);
	inTree->SetBranchAddress("zpri", &zpri);

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
