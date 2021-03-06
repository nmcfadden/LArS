//
// CLASS IMPLEMENTATION:  LArSOpticalMaterialProperties.cc
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 Code taken from MaGe a LEGEND software package. N. McFadden wrote the LEGEND code
 and N. McFadden took the LEGEND code and performed the intail implamentation in 
 LArS Geant4 sims
 *
 *
 */
//
//---------------------------------------------------------------------------//
/*
 * AUTHOR: Neil McFadden
 * CONTACT: neil.mcfadden@physik.uzh.ch
 */
//---------------------------------------------------------------------------//
//


//---------------------------------------------------------------------------//
#include "LArSOpticalMaterialProperties.hh"


using namespace CLHEP;
const G4double LArSOpticalMaterialProperties::LambdaE = twopi *1.973269602e-16 * m * GeV;
const G4int    LArSOpticalMaterialProperties::NUMENTRIES = 69;
const G4int    LArSOpticalMaterialProperties::NUMENTRIES_1 = 5;
const G4int    LArSOpticalMaterialProperties::NUMENTRIES_2 = 500;
const G4int    LArSOpticalMaterialProperties::NUMENTRIES_3 = 29;


LArSOpticalMaterialProperties::LArSOpticalMaterialProperties()
  :fSuccessfulInitialization(false)
{
  
}

LArSOpticalMaterialProperties::~LArSOpticalMaterialProperties()
{}

void LArSOpticalMaterialProperties::ConstructionOpticalProperties()
{
  ph_energies = new G4double[NUMENTRIES_2];
  //Energy Array used for all materials from 115 nm to 650 nm with 500 points (1.07 nm/bin)
  for (int i = 0; i < NUMENTRIES_2; i++) {
    ph_energies[i] = LambdaE/(650*nm) + i*((LambdaE/(115*nm) - (LambdaE/(650*nm)))/(NUMENTRIES_2-1));
  }
  RegisterArgonOpticalProperties();
  //RegisterXeDopedArgonOpticalProperties();
  Register_TPB_Properties();
  Register_PEN_Properties();
  Register_Acrylic();
  Register_MgF2();

  //Register_Fiber_Properties();
  //Register_Fiber_Cladding_Properties();
  //Register_Nylon_Properties();
  //Register_Copper_Properties();
  //Register_Germanium_Properties();
  //Register_Silicon_Properties();
  //Register_Teflon_Properties();
  //Register_Silica_Properties();
  //Register_VM2000();
  //Register_StainlessSteel();

  G4cout <<"Constructed Optical Material Properties"<<G4endl;
}

/// Methods imported from the MPIKLarGe class
/// Optical properties of LAr in several places
void LArSOpticalMaterialProperties::RegisterArgonOpticalProperties()
{


	  static const G4int NUMENTRIES = 69;
	  const G4int num = 69;
	  static const G4double temp = 87*kelvin; //Temperature may be higher since we were overpressure - this may only slightly affect values such as the rayleigh scattering length
	  static const G4double LambdaE = twopi *1.973269602e-16 * m * GeV;

	  /**
	   * Nominal values for pure argon from Doke et al 2002. For other particles, see paper
	  */
	  G4double q_factor_electron=0.8; // (non relativistic)
	  G4double q_factor_alpha=0.72; // value for 5.5MeV alphas: flat LET response for several energies
	  G4double scint_yield = 19.5*eV; // mean energy necessary to produce a photon in LAr

	  // an extra factor to lower the light yield was introduced, so that the simulation PMThits matches the measured value
	  G4double extra_qFactor = *( (*std::unique_ptr<TGraph>(ReadSpectrumFromFile("qFactor_LAr.dat"))).GetY() );

	  G4double photon_yield_alpha= 1.0/(scint_yield/q_factor_alpha) * extra_qFactor;
	  G4double photon_yield_electron= 1.0/(scint_yield/q_factor_electron);

	  static const G4int energy_entries=10000;
	 G4double SCY_Energy_alpha[energy_entries]; G4double SCY_Energy_electron[energy_entries];
	 G4double SCY_alpha[energy_entries]; G4double SCY_electron[energy_entries];

	// defining light yield for alphas and electrons using constant values for now 
	  for (int i=0; i<energy_entries; i++) {
		double step = i*0.001;
		SCY_Energy_alpha[i]=(0.0001+step)*MeV;
		SCY_alpha[i]=SCY_Energy_alpha[i]*photon_yield_alpha;
		SCY_Energy_electron[i]=(0.0001+step)*MeV;
		SCY_electron[i]=SCY_Energy_electron[i]*photon_yield_electron;
	}

	//continue with for loop

	  G4double tau_s = 6.0*ns;
	  G4double tau_l = 1590.0*ns;

	  G4int ji;
	  G4double e;
	  G4double ee;

	  G4double PPCKOVHighE = LambdaE / (115*nanometer);
	  G4double PPCKOVLowE = LambdaE / (650*nanometer);
	  G4double de = ((PPCKOVHighE - PPCKOVLowE) / ((G4double)(NUMENTRIES-1)));

	  // liquid argon (LAr)
	  G4double LAr_PPCK[(NUMENTRIES)];
	  G4double LAr_RIND[(NUMENTRIES)];
	  G4double LAr_RAYL[(NUMENTRIES)];
	  G4double LAr_ABSL[(NUMENTRIES)];

	  G4double LAr_ABSL_xuv = 60*cm;
	  G4double LAr_ABSL_vis = 10*m;

	  //G4cout  << "Rayleigh scattering lenght [m]:" << G4endl;
    for (ji = 0; ji < NUMENTRIES; ji++){
      e = PPCKOVLowE + ((G4double)ji) * de;
      LAr_PPCK[ji] = e;
      LAr_RIND[ji] = LArRefIndex((LambdaE / e));
      LAr_RAYL[ji] = LArRayLength((LambdaE / e), temp);
      //Uncomment for debugging purposes
       /*  G4cout << (LambdaE/LAr_PPCK[ji])/nm <<", "<< LAr_RAYL[ji] << G4endl;
         G4cout << " WL: " << (LambdaE/LAr_PPCK[ji])/nm<< " nm Energy: " << LAr_PPCK[ji]/eV << " eV; Refr: " <<
         LAr_RIND[ji] << " ; Rayleigh l. " << LAr_RAYL[ji]/m << " m" << G4endl;*/
      

      if (((LambdaE / e)/nm) < 200.0) {
        LAr_ABSL[ji] =LAr_ABSL_xuv;
      } 
      else {
        LAr_ABSL[ji] = LAr_ABSL_vis;
      }
    }
    //G4cout << "XUV attenuation length: " << LAr_ABSL_xuv/cm << " cm" << G4endl;
    //G4cout << "VIS attenuation length: " << LAr_ABSL_vis/m << " m" << G4endl;

	  G4double PPSCHighE = LambdaE /(115*nanometer);
	  G4double PPSCLowE = LambdaE /(136*nanometer);
	  G4double dee = ((PPSCHighE - PPSCLowE) / ((G4double)(num-1)));
	  G4double LAr_SCIN[num];
	  G4double LAr_SCPP[num];
    for (ji = 0; ji < num; ji++){
      ee=PPSCLowE+ ((G4double)ji) * dee;
      LAr_SCPP[ji]=ee;
      LAr_SCIN[ji]=ArScintillationSpectrum((LambdaE/ee)/nanometer);
      /** Keep for debugging purposes
        G4cout << " WL: " << (LambdaE/LAr_SCPP[ji])/nanometer<< " nm Scint: " << LAr_SCPP[ji]/eV << " eV :: " << LAr_SCIN[ji] << G4endl;

        G4cout << " WL1: " << (LambdaE/ee)/nanometer << " WL: " << (LambdaE/LAr_PPCK[ji])/nm<< " En: " << LAr_PPCK[ji]/eV << " ;n: " <<
        LAr_RIND[ji] << " ; Rayleigh  " << LAr_RAYL[ji]/m << " m; Scint " << LAr_SCIN[ji] << G4endl;
        */
    }

	  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

	  myMPT1->AddConstProperty("SCINTILLATIONYIELD",photon_yield_alpha); //set now to photon yield alpha
	  myMPT1->AddProperty("ALPHASCINTILLATIONYIELD",SCY_Energy_alpha, SCY_alpha, energy_entries); 
	  myMPT1->AddProperty("ELECTRONSCINTILLATIONYIELD",SCY_Energy_electron, SCY_electron, energy_entries); 
	  //myMPT1->AddProperty("PROTONSCINTILLATIONYIELD",SCY_Energy_alpha, SCY_alpha, energy_entries); 

	  myMPT1->AddProperty("RINDEX",        LAr_PPCK, LAr_RIND, NUMENTRIES);
	  myMPT1->AddProperty("RAYLEIGH",      LAr_PPCK, LAr_RAYL, NUMENTRIES);
	  myMPT1->AddProperty("ABSLENGTH",     LAr_PPCK, LAr_ABSL, NUMENTRIES);

	  // Fast and slow components of the scintillation
	  // They should both be the same
	  if ( (LAr_SCPP[0] >= PPCKOVLowE) && (LAr_SCPP[(sizeof(LAr_SCPP)/sizeof(G4double) - 1)] <= PPCKOVHighE) ){
	      myMPT1->AddProperty("FASTCOMPONENT",LAr_SCPP,LAr_SCIN,num);
	      myMPT1->AddProperty("SLOWCOMPONENT",LAr_SCPP,LAr_SCIN,num);
	  }

	  myMPT1->AddConstProperty("FASTTIMECONSTANT", tau_s);
	  myMPT1->AddConstProperty("SLOWTIMECONSTANT",tau_l);

	  // This is the value for electrons and gammas
	  // For example, for nuclear recoils it should be 0.75
	  // nominal value for electrons and gamas: 0.23
	  // Value used was provided by F. Art
	  myMPT1->AddConstProperty("YIELDRATIO",1.); // it does not change anything for now


	  /**
	   * statistical yield fluctuation can be broadened or narrower
	   * (impurities, fano factor):
	   *
	   * LAr Fano factor = 0.11 ( Doke et al, NIM 134 (1976)353 )
	   *
	   */

	  G4double fano =0.11;// 0.11;// Doke et al, NIM 134 (1976)353
	  myMPT1->AddConstProperty("RESOLUTIONSCALE",fano); //not implemented? // Gabriela
    	  fArgonLiquid = G4Material::GetMaterial("Argon-Liq"); 

	 // uncomment for debugging purposes 
	 //myMPT1->DumpTable();//bool exists = myMPT1->ConstPropertyExists(""); // myMPT1->RemoveConstProperty("");
	  fArgonLiquid->SetMaterialPropertiesTable(myMPT1);

	  //fArgonLiquid->GetIonisation()->SetBirksConstant(5.1748e-4*cm/MeV); 

}

// Calculates the refractive index of LAr from the Sellmeier formula.
G4double LArSOpticalMaterialProperties::LArRefIndex(const G4double lambda)
{

	G4double a_0=0.334, a_uv=0.100, a_ir=0.008; //Sellmeier coefficients from ArXiv 2002.09346
	G4double lambda_uv=106.6*nanometer, lambda_ir=908.3*nanometer; // poles at lambda_uv and lambda_ir.

	G4double x_ri=a_0+a_uv*pow(lambda,2)/(pow(lambda,2)-pow(lambda_uv,2))+a_ir*pow(lambda,2)/(pow(lambda,2)-pow(lambda_ir,2));
	G4double n_index_LAr= sqrt(1+3*x_ri/(3-x_ri));
  
	return (n_index_LAr);
  //return ( sqrt(LArEpsilon(lambda)) ); // square root of dielectric constant
}


G4double LArSOpticalMaterialProperties::LArRayLength(const G4double lambda,const
				   G4double temp)
{
  G4double dyne = 1.0e-5*newton;
  static const G4double LArKT = 2.18e-10 * cm2/dyne; // LAr isothermal compressibility
  static const G4double k = 1.380658e-23 * joule/kelvin; // the Boltzmann constant
  G4double h;
  h = pow(LArRefIndex(lambda),2); //h = LArEpsilon(lambda); 
  if (h < 1.00000001) h = 1.00000001; // just a precaution
  h = (h - 1.0) * (h + 2.0); // the "dielectric constant" dependance
  h *= h; // take the square
  h *= LArKT * temp * k; // compressibility * temp * Boltzmann constant
  h /= lambda * lambda * lambda * lambda; // (lambda)^4
  h *= 9.18704494231105429; // (2 * Pi / 3)^3
  if ( h < (1.0 / (10.0 * km)) ) h = 1.0 / (10.0 * km); // just a precaution
  if ( h > (1.0 / (0.1 * nanometer)) ) h = 1.0 / (0.1 * nanometer); // just a precaution
  return ( 1.0 / h );}

G4double LArSOpticalMaterialProperties::ArScintillationSpectrum(const G4double kk)
{
  G4double waveL;
  waveL =exp(-0.5*((kk-128.0)/(2.929))*((kk-128.0)/(2.929)));
  return waveL;
}

void LArSOpticalMaterialProperties::Register_TPB_Properties()
{
  //taken from MGGerdaLocalMaterialTable.cc in the gerda-optical branch because they do it so much better than me (N. McFadden)
  //Also, I am guessing most of the comments are from Luigi Pertoldi
  //Adding TPB emission properties for different materials and generic TPB

  G4NistManager*   nist = G4NistManager::Instance();
  G4Element* elH = nist->FindOrBuildElement("H");
  G4Element* elC = nist->FindOrBuildElement("C");
  G4Element* elF = nist->FindOrBuildElement("F");
  
  // TPB
  G4Material* TPB = new G4Material("TPB", 1.08*g/cm3, 2, kStateSolid);
              TPB -> AddElement(elH, 22);
              TPB -> AddElement(elC, 28);

  // TPB on Nylon
  G4Material* TPBOnNylon = new G4Material("TPBOnNylon", 1.08*g/cm3, 2, kStateSolid);
              TPBOnNylon -> AddElement(elH, 22);
              TPBOnNylon -> AddElement(elC, 28);

  // TPB on VM2000
  G4Material* TPBOnVM2000 = new G4Material("TPBOnVM2000", 1.08*g/cm3, 2, kStateSolid);
              TPBOnVM2000 -> AddElement(elH, 22);
              TPBOnVM2000 -> AddElement(elC, 28);

  // TPB on Tetratex
  G4Material* TPBOnTetratex = new G4Material("TPBOnTetratex", 1.08*g/cm3, 2, kStateSolid);
              TPBOnTetratex -> AddElement(elH, 22);
              TPBOnTetratex -> AddElement(elC, 28);

  //////////////
  // Tetratex //
  //////////////

  /** Reflectivity taken from https://www.osti.gov/servlets/purl/1184400
   * "Reflectivity spectra for commonly used reflectors" by M. Janacek
   *
   * He measures the reflectivity of 2 and 4 superimposed layers of 160um thick
   * Tetratex. As our layer in GERDA is 254um thick I'm taking here his results
   * for the two superimposed foils (= 320um). So, in reality, the reflectivity
   * of our foil should be (negligibly) smaller.
   *
   * In addition to this, the TPB layer has some effect on the reflectivity,
   * just like VM2000 above.
   * -Luigi Pertoldi
   */

  // Tetratex (PTFE)
  // density from data sheet found in Zurich
  G4Material* Tetratex = new G4Material("Tetratex", 0.35*g/cm3, 2);
              Tetratex -> AddElement(elF, 0.76);
              Tetratex -> AddElement(elC, 0.24);

  auto TetratexReflGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_Tetratex.dat"));
  G4double refl_Tetratex[NUMENTRIES_2];
  G4double rindex_Tetratex[NUMENTRIES_2];
  G4double eff_Tetratex[NUMENTRIES_2];
  G4double pdTeflonSpecularLobe[NUMENTRIES_2]; 
  G4double pdTeflonSpecularSpike[NUMENTRIES_2];
  G4double pdTeflonBackscatter[NUMENTRIES_2];  
  //G4double absLength[NUMENTRIES_2];

 G4String s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/TTX_ref.dat";
 std::ofstream outfile_ttx(s_outfile.c_str());
  for (int i = 0; i < NUMENTRIES_2; i++) {
    auto r = TetratexReflGraph->Eval(LambdaE/(ph_energies[i])/nm);
    //refl_Tetratex[i] = r >= 0 ? r : 0;
    refl_Tetratex[i] = r >= 0 ? r : 0;
    outfile_ttx<<LambdaE/ph_energies[i]/nm<<" "<<refl_Tetratex[i]<<G4endl;

    rindex_Tetratex[i] = 1.51;// Molded Unpolished PTFE https://arxiv.org/pdf/0910.1056.pdf
    eff_Tetratex[i] = 1.;
    pdTeflonSpecularLobe[i] = 0.01; //changed to 0.01 since most of the reflection is lambertian
    pdTeflonSpecularSpike[i] = 0.01; 
    pdTeflonBackscatter[i] = 0.01;
    //if(LambdaE/(ph_energies[i])/nm < 150) absLength[i] = 1.0*nm;//don't want photons going through the material
    //else absLength[i] = 1.0*m;

  }

  G4MaterialPropertiesTable* TetratexOpTable = new G4MaterialPropertiesTable();
  TetratexOpTable->AddProperty("RINDEX",ph_energies, rindex_Tetratex, NUMENTRIES_2);
  TetratexOpTable->AddProperty("REFLECTIVITY", ph_energies, refl_Tetratex, NUMENTRIES_2);
  TetratexOpTable->AddProperty("SPECULARLOBECONSTANT", ph_energies, pdTeflonSpecularLobe, NUMENTRIES_2);
  TetratexOpTable->AddProperty("SPECULARSPIKECONSTANT",ph_energies, pdTeflonSpecularSpike, NUMENTRIES_2);
  TetratexOpTable->AddProperty("BACKSCATTERCONSTANT",  ph_energies, pdTeflonBackscatter , NUMENTRIES_2);
  TetratexOpTable->AddProperty("EFFICIENCY", ph_energies, eff_Tetratex, NUMENTRIES_2);
  //TetratexOpTable->AddProperty("ABSLENGTH",ph_energies,absLength,NUMENTRIES_2);
  G4Material::GetMaterial("Tetratex")->SetMaterialPropertiesTable(TetratexOpTable);

  /////////
  // TPB //
  /////////

  /** Not actually to be used, please prefer TPBOnSomething materials
   *
   * - Emission spectrum taken from arXiv:1104.3259 (128nm excitation wavelength)
   * - Absorption spectrum: very difficult to find good data. Values in TPBAbsorption.dat
   *                        correspond to measurements reported in arXiv:1709.05002 for TPB
   *                        evaporated on utraviolet-transmitting acrylic substrate
   * - Quantum efficiency: literature value of 1.2 suggested by M. Walter
   *                       recommendation of DARWIN/ArDM
   * - Time constant: arbitrary small, same used by WArP people
   * - Refractive index: // http://www.molbase.com/en/overview_1450-63-1-moldata-77892.html
   *
   * -Luigi Pertoldi
   */

  G4double TPB_QuantumEff   = 0.7;//Changed it to 1 from 1.2 N.M.;
  G4double TPB_TimeConstant = 0.01 *ns;
  G4double TPB_RefrIndex    = 1.635;

  G4double TPB_refraction[NUMENTRIES_2];
  G4double TPB_absorption[NUMENTRIES_2];
  G4double TPB_emission  [NUMENTRIES_2];

  // read emission spectrum from file
  auto TPBEmissionGraph   = std::unique_ptr<TGraph>(ReadSpectrumFromFile("TPBEmission.dat"));
  // read absorption from file (lengths in nanometers)
  auto TPBAbsorptionGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("TPBAbsorption.dat"));
  
 s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/tpb_em.dat"; std::ofstream outfile(s_outfile.c_str());
 s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/tpb_abs.dat"; std::ofstream outfile2(s_outfile.c_str());

 for (int i = 0; i < NUMENTRIES_2; i++) {
    TPB_refraction[i] = TPB_RefrIndex;

    // use emission spectrum from file
    auto e = TPBEmissionGraph->Eval(LambdaE/(ph_energies[i])/nm);
    TPB_emission[i] = e >= 0 ? e : 0; 
    G4double wl=LambdaE/ph_energies[i]/nm;
    if (wl<350. || wl >680.) TPB_emission[i] =0; // it is unphysical to extrapolate TPB's emission further down/up
    outfile<<wl<<" "<<TPB_emission[i]<<G4endl;

    // use absorption length from file
    auto a = TPBAbsorptionGraph->Eval(LambdaE/(ph_energies[i])/nm) *nm;
    TPB_absorption[i] = a >= 0 ? a : 0;
    //TODO: this extrapolation seems to be going too far, check whether necessary to restrict it
    outfile2<<wl<<" "<<TPB_absorption[i]<<G4endl;
  }

  auto TPBTable = new G4MaterialPropertiesTable();
  TPBTable->AddProperty     ("RINDEX",               ph_energies, TPB_refraction, NUMENTRIES_2);
  TPBTable->AddProperty     ("WLSABSLENGTH",         ph_energies, TPB_absorption, NUMENTRIES_2);
  TPBTable->AddProperty     ("WLSCOMPONENT",         ph_energies, TPB_emission,   NUMENTRIES_2);
  TPBTable->AddConstProperty("WLSTIMECONSTANT",      TPB_TimeConstant);
  TPBTable->AddConstProperty("WLSMEANNUMBERPHOTONS", TPB_QuantumEff);
  G4Material::GetMaterial("TPB")->SetMaterialPropertiesTable(TPBTable);

  /////////////////////
  // TPB on Tetratex //
  /////////////////////

  /** Emission spectrum
   *
   * Taken from (our) publication: arXiv:1503.05349
   * Seems that the TPB is dip-coated (0.9 mg/cm2 ~ 8 um thickness) on the Tetratex
   * so here I'm taking the red curve in Fig. 4 (without the peak), which actually is
   * measured for 0.17 mg/cm2. In principle the thickness affects the shape of the
   * emission spectrum, as the efficiency of the reabsorption effect increases with
   * the thickness of the layer. However, I didn't find other measurements around...
   *  -Luigi Pertoldi
   * See material TPB for the other properties
   */

  G4double TPBOnTetratex_emission[NUMENTRIES_2];

  // read emission spectrum from file
  auto TetratexSpecGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("TPBOnTetratexEmission.dat"));

 s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/tpb_ttx_em.dat"; std::ofstream outfile_tpbttx(s_outfile.c_str());

  for (int i = 0; i < NUMENTRIES_2; i++) {
    // use emission from file
    auto e = TetratexSpecGraph->Eval(LambdaE/(ph_energies[i])/nm);
    TPBOnTetratex_emission[i] = e >= 0 ? e : 0;
    G4double wl=LambdaE/ph_energies[i]/nm;
    if (wl<350. || wl >680.) TPB_emission[i] =0; // it is unphysical to extrapolate TPB's emission further down/up
    outfile_tpbttx<<wl<<" "<<TPB_emission[i]<<G4endl;

  }

  G4MaterialPropertiesTable *TPBOnTetratexTable = new G4MaterialPropertiesTable();
  TPBOnTetratexTable->AddProperty     ("RINDEX",               ph_energies, TPB_refraction,         NUMENTRIES_2);
  TPBOnTetratexTable->AddProperty     ("WLSABSLENGTH",         ph_energies, TPB_absorption,         NUMENTRIES_2);
  TPBOnTetratexTable->AddProperty     ("WLSCOMPONENT",         ph_energies, TPBOnTetratex_emission, NUMENTRIES_2);
  TPBOnTetratexTable->AddConstProperty("WLSTIMECONSTANT",      TPB_TimeConstant);
  TPBOnTetratexTable->AddConstProperty("WLSMEANNUMBERPHOTONS", TPB_QuantumEff);
  //TPBOnTetratexTable->AddProperty("REFLECTIVITY", ph_energies, refl_Tetratex, NUMENTRIES_2); 
  //TPBOnTetratexTable->AddConstProperty("SCINTILLATIONYIELD",   TPB_ScintYield);
  G4Material::GetMaterial("TPBOnTetratex")->SetMaterialPropertiesTable(TPBOnTetratexTable);

  //////////////////
  // TPB On Nylon //
  //////////////////

  /** Emission spectrum
   *
   * Taken from GSTR-15-504
   * The TPB should be embedded in a polystyrene matrix (30% TPB 70% PS) and diluited in
   * toluene (ratio 1:10), then brushed on nylon. The spectrum in TPBOnNylonEmission.dat
   * comes from Fig. 2b, brown curve. The spectrum is similar to the one in arXiv:1304.6117
   * Fig. 14, for TPB in PS matrix on glass, which makes me hope that the spectrum makes sense
   *
   * For 30% TPB 70% PS the WLS light yield is reduced by 30% [Alexey]
   *
   * See material TPB for the other properties
   *  -Luigi Pertoldi
   */

/*
  G4double TPBOnNylon_emission   [NUMENTRIES_2];
  //Need attenuation length and WLS-attenuation because both physical properties exist
  G4double TPBOnNylon_absorption [NUMENTRIES_2];


  // read emission spectrum from file
  auto TPBOnNylonSpecGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("TPBOnNylonEmission.dat"));

  // lengths are in m in the file
  auto NylonAbsGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("NylonAbsorption.dat"));

  for (int i = 0; i < NUMENTRIES_2; i++) {
    // use emission from file
    auto e = TPBOnNylonSpecGraph->Eval(LambdaE/(ph_energies[i])/nm);
    TPBOnNylon_emission[i] = e >= 0 ? e : 0;

    auto a = NylonAbsGraph->Eval(LambdaE/(ph_energies[i])/nm) *m;
    TPBOnNylon_absorption[i]= a >= 0 ? a : 0;
  }

  G4MaterialPropertiesTable *TPBOnNylonTable = new G4MaterialPropertiesTable();
  TPBOnNylonTable->AddProperty     ("RINDEX",               ph_energies, TPB_refraction,        NUMENTRIES_2);
  TPBOnNylonTable->AddProperty     ("WLSABSLENGTH",         ph_energies, TPB_absorption,        NUMENTRIES_2);
  TPBOnNylonTable->AddProperty     ("ABSLENGTH",            ph_energies, TPBOnNylon_absorption, NUMENTRIES_2);
  TPBOnNylonTable->AddProperty     ("WLSCOMPONENT",         ph_energies, TPBOnNylon_emission,   NUMENTRIES_2);
  TPBOnNylonTable->AddConstProperty("WLSTIMECONSTANT",      TPB_TimeConstant);
  TPBOnNylonTable->AddConstProperty("WLSMEANNUMBERPHOTONS", 0.84);
  //TPBOnNylonTable->AddConstProperty("SCINTILLATIONYIELD",   TPB_ScintYield);
  G4Material::GetMaterial("TPBOnNylon")->SetMaterialPropertiesTable(TPBOnNylonTable);
*/

  ///////////////////
  // TPB on VM2000 //
  ///////////////////
  
  //
  //VM2000 will NOT be used in LEGEND because Tetratex is more radio pure, it is added here just to have it...
  /** Emission spectrum
   *
   * Values taken from arXiv:1304.6117
   * They measure the emission spectrum of TPB (~160 um thick layer) on VM2000
   * at an excitation wavelength of 128nm and at 87K, so exactly in our experimental
   * conditions. The major differences brougth by the LAr temperature are the vibronic
   * structures that modify the shape of the spectrum.
   *
   * The old emission spectrum can be still found in TPBOnVM2000Emission.dat and at
   * https://www.mpi-hd.mpg.de/gerdawiki/img_auth.php/8/8a/MaGe_optical_properties_table.pdf
   * as was measured (under which conditions?) by M. Heisel and A. Wegmann in the past
   *  -Luigi Pertoldi
   * See material TPB for the other properties
   */

/*
  G4double TPBOnVM2000_emission  [NUMENTRIES_2];

  auto TPBOnVM2000SpecGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("TPBOnVM2000Emission-87K.dat"));

  for (int i = 0; i < NUMENTRIES_2; i++) {
    // use emission from file
    auto e = TPBOnVM2000SpecGraph->Eval(LambdaE/(ph_energies[i])/nm);
    TPBOnVM2000_emission[i] = e >= 0 ? e : 0;
  }

  G4MaterialPropertiesTable *TPBOnVM2000Table = new G4MaterialPropertiesTable();
  TPBOnVM2000Table->AddProperty     ("RINDEX",               ph_energies, TPB_refraction,       NUMENTRIES_2);
  TPBOnVM2000Table->AddProperty     ("WLSABSLENGTH",         ph_energies, TPB_absorption,       NUMENTRIES_2);
  TPBOnVM2000Table->AddProperty     ("WLSCOMPONENT",         ph_energies, TPBOnVM2000_emission, NUMENTRIES_2);
  TPBOnVM2000Table->AddConstProperty("WLSTIMECONSTANT",      TPB_TimeConstant);
  TPBOnVM2000Table->AddConstProperty("WLSMEANNUMBERPHOTONS", TPB_QuantumEff);
  //TPBOnVM2000Table->AddConstProperty("SCINTILLATIONYIELD",   TPB_ScintYield);
  G4Material::GetMaterial("TPBOnVM2000")->SetMaterialPropertiesTable(TPBOnVM2000Table);
*/

  ////////////
  // VM2000 //
  ////////////

  //VM2000 will NOT be used in LEGEND because Tetratex is more radio pure, it is added here just to have it...
  /** Reflectivity taken from https://www.osti.gov/servlets/purl/1184400
   * "Reflectivity spectra for commonly used reflectors" by M. Janacek
   *
   * Seems to be a well-done measurement, done using an integrating sphere and taking
   * into account the (even little) fluorescence. He uses a 65um thick foil without the
   * glue on the back. The results he shows are already normalized by the reflectivity
   * of the reference PTFE sample (-> absolute reflectivity!)
   *
   * EDIT: I found this paper: arXiv:1304.6117 in which people measure the reflectivity
   *       of VM2000 with TPB evaporated on it, and it's a bit different. The measurement
   *       seems to be done properly as they take into account the effect of TPB's emission
   *       spectrum. The measurement seems to be pretty independent on the TPB layer thickness
   *
   *       The old reflectivity values can be found in 'Reflectivity_VM2000.dat'
   *  -Luigi Pertoldi
   */

    //auto VM2000ReflGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_VM2000.dat"));
/*
  auto VM2000ReflGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_TPBCoatedVM2000.dat"));
  G4double refl_VM2000[NUMENTRIES_2];

  for (int i = 0; i < NUMENTRIES_2; i++) {
    auto r = VM2000ReflGraph->Eval(LambdaE/(ph_energies[i])/nm);
    refl_VM2000[i] = r >= 0 ? r : 0;
  }

  G4MaterialPropertiesTable* VM2000OpTable = new G4MaterialPropertiesTable();
  VM2000OpTable->AddProperty("REFLECTIVITY", ph_energies, refl_VM2000, NUMENTRIES_2);
  G4Material::GetMaterial("VM2000")->SetMaterialPropertiesTable(VM2000OpTable);
*/


}
  /////////////////////
  //      PEN        //
  /////////////////////
//copied everything from TPB material

//Refractive Index, Photon Yield, Absorption length and Emission spectra borrowed from Connor Hayward (hayward@mpp.mpg.de) Germany
//
//Quantum Efficiency value was suggested by Mike Febraro since no measurement was available
void LArSOpticalMaterialProperties::Register_PEN_Properties()
{
  G4NistManager*   nist = G4NistManager::Instance();
  G4Element* elH = nist->FindOrBuildElement("H");
  G4Element* elC = nist->FindOrBuildElement("C");
  G4Element* elO = nist->FindOrBuildElement("O");

  G4Material* PEN;
  if(G4Material::GetMaterial("PEN") == NULL ){
    PEN = new G4Material("PEN", 1.3*g/cm3, 3, kStateSolid);
    PEN -> AddElement(elH, 10);
    PEN -> AddElement(elC, 14);
    PEN -> AddElement(elO, 4);
  }
  G4double PEN_QuantumEff   = 0.36;
  G4double PEN_TimeConstant = 10.0 *ns; //
  G4double PEN_RefrIndex    = 1.638;
  //G4double PEN_photon_yield = 3000; 

  G4double PEN_refraction[NUMENTRIES_2];
  G4double PEN_absorption[NUMENTRIES_2];
  G4double PEN_emission  [NUMENTRIES_2];

  // read emission spectrum from file
  auto PENEmissionGraph   = std::unique_ptr<TGraph>(ReadSpectrumFromFile("PENEmission.dat"));
  // read absorption from file (lengths in nanometers)
  auto PENAbsorptionGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("PENAbsorption.dat"));

 G4String s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/pen_em.dat"; std::ofstream outfile_pen_em(s_outfile.c_str());
 s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/pen_abs.dat"; std::ofstream outfile_pen_abs(s_outfile.c_str());

  for (int i = 0; i < NUMENTRIES_2; i++) {
    PEN_refraction[i] = PEN_RefrIndex;

    // use emission spectrum from file
    auto e = PENEmissionGraph->Eval(LambdaE/(ph_energies[i])/nm);
    PEN_emission[i] = e >= 0 ? e : 0;
    G4double wl=LambdaE/ph_energies[i]/nm;
    //if (wl<330. || wl >680.) PEN_emission[i] =0; // it is unphysical to extrapolate PEN's emission further down/up
    outfile_pen_em<<wl<<" "<<PEN_emission[i]<<G4endl;

    // use absorption length from file
    auto a = PENAbsorptionGraph->Eval(LambdaE/(ph_energies[i])/nm) *nm;
    PEN_absorption[i] = a >= 0 ? a : 0;
    outfile_pen_abs<<wl<<" "<<PEN_absorption[i]<<G4endl;

  }

  auto PENTable = new G4MaterialPropertiesTable();
  PENTable->AddProperty     ("RINDEX",               ph_energies, PEN_refraction, NUMENTRIES_2);
  PENTable->AddProperty     ("WLSABSLENGTH",         ph_energies, PEN_absorption, NUMENTRIES_2);
  PENTable->AddProperty     ("WLSCOMPONENT",         ph_energies, PEN_emission,   NUMENTRIES_2);
  PENTable->AddConstProperty("WLSTIMECONSTANT",      PEN_TimeConstant);
  PENTable->AddConstProperty("WLSMEANNUMBERPHOTONS", PEN_QuantumEff);
  //PENTable->AddConstProperty("SCINTILLATIONYIELD",PEN_photon_yield);
  G4Material::GetMaterial("PEN")->SetMaterialPropertiesTable(PENTable);
}

void LArSOpticalMaterialProperties::Register_MgF2(){
  auto IndexGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("MgF2Index.dat"));
  G4String s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/MgF2Index.dat"; std::ofstream outfile(s_outfile.c_str());
  G4double index[NUMENTRIES_2];
  for (int i = 0; i < NUMENTRIES_2; i++) {
    auto ind = IndexGraph->Eval(LambdaE/(ph_energies[i])/nm);
    index[i] = ind;
    outfile<<LambdaE/(ph_energies[i])/nm<<" "<<index[i]<<G4endl;
  }

  auto MgF2Table = new G4MaterialPropertiesTable();
  MgF2Table->AddProperty("RINDEX"   , ph_energies, index, NUMENTRIES_2);
  G4Material::GetMaterial("MgF2")->SetMaterialPropertiesTable(MgF2Table);
}

void LArSOpticalMaterialProperties::Register_Acrylic()
{
  G4NistManager*   nist = G4NistManager::Instance();
  G4Element* elH = nist->FindOrBuildElement("H");
  G4Element* elC = nist->FindOrBuildElement("C");
  G4Element* elO = nist->FindOrBuildElement("O");

  G4Material* Acrylic;
  if(G4Material::GetMaterial("Acrylic") != NULL){
    Acrylic = G4Material::GetMaterial("Acrylic");
  }
  else{
    Acrylic  = new G4Material("Acrylic",1.18*g/cm3,3,kStateSolid);
    Acrylic->AddElement(elH,8);
    Acrylic->AddElement(elC,5);
    Acrylic->AddElement(elO,2);
  }
  //Data is in wavelength (nm) and absorption length (mm)
  //Taken from https://wiki.bnl.gov/dayabay/upload/Acrylic_Transmittance_Sep14.pdf
  auto acrylicAbsorptionGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("AcrylicAbsorption.dat"));
  auto acrylicIndexGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("AcrylicIndex.dat"));

  G4String s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/Acryl_abs.dat"; std::ofstream outfile(s_outfile.c_str());
  s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/Acryl_index.dat"; std::ofstream outfile2(s_outfile.c_str());


  G4double acrylic_absorption[NUMENTRIES_2];
  G4double acrylic_index[NUMENTRIES_2];
  for (int i = 0; i < NUMENTRIES_2; i++) {
    auto r = acrylicAbsorptionGraph->Eval(LambdaE/(ph_energies[i])/nm)*mm;
    if(LambdaE/(ph_energies[i])/nm < 200) r = 10*nm;
    acrylic_absorption[i] = r >= 0 ? r : 0;
    auto index = acrylicIndexGraph->Eval(LambdaE/(ph_energies[i])/nm);
    acrylic_index[i] = index;

    outfile<<LambdaE/(ph_energies[i])/nm<<" "<<acrylic_absorption[i]<<G4endl;
    outfile2<<LambdaE/(ph_energies[i])/nm<<" "<<acrylic_index[i]<<G4endl;
  }

  auto acrylicTable = new G4MaterialPropertiesTable();
  acrylicTable->AddProperty("RINDEX"   , ph_energies, acrylic_index, NUMENTRIES_2);
  acrylicTable->AddProperty("ABSLENGTH", ph_energies, acrylic_absorption, NUMENTRIES_2);
  G4Material::GetMaterial("Acrylic")->SetMaterialPropertiesTable(acrylicTable);
  
}

//copied from GEGSLArGeOptical.cc
/*
G4double LArSOpticalMaterialProperties::TPBEmissionSpectrum(G4double energy)
{
  if (fSuccessfulInitialization)
  {
    //Here the data are loaded
    G4double targetf = LambdaE/energy;

    G4double eff =fTPBspec->Eval(targetf/nm);
    if (eff < 0.2) eff = 0.2;
    //G4cout << "Eval ("<< targetf/nm<< ")yielded a value of " << eff << G4endl;
    return eff;
  }
  else
  {
    return 0.2;
  }
}

//(For PEN)Copied from G4double LArSOpticalMaterialProperties::TPBEmissionSpectrum(G4double energy)
G4double LArSOpticalMaterialProperties::PENEmissionSpectrum(G4double energy)
{
  if (fSuccessfulInitialization)
  {
    //Here the data are loaded
    G4double targetf = LambdaE/energy;

    G4double eff =fPENspec->Eval(targetf/nm);
    if (eff < 0.2) eff = 0.2;
    //G4cout << "Eval ("<< targetf/nm<< ")yielded a value of " << eff << G4endl;
    return eff;
  }
  else
  {
    return 0.2;
  }
}
*/

/*
void LArSOpticalMaterialProperties::Register_Fiber_Properties()
{
  //Stolen from gerdageometry/src/GEGeometryLArInstHybrid.cc
  //N. McFadden
  //updated with: https://www.crystals.saint-gobain.com/sites/imdf.crystals.com/files/documents/fiber-product-sheet.pdf
  ///
  /// -- Material definition --
  ///

  G4double density;
  std::vector<G4int> natoms;
  std::vector<G4double> fractionMass;
  std::vector<G4String> elements;

  G4NistManager *nistMan = G4NistManager::Instance();

  //--------------------------------------------------
  // Fiber and WLS: Polystyrene
  //--------------------------------------------------

  elements.push_back("C");     natoms.push_back(8);
  elements.push_back("H");     natoms.push_back(8);

  density = 1.050*g/cm3;

  // -- Rough approximation of BCF-91A             
  fFiber_material = nistMan->ConstructNewMaterial("PolystyreneFiber", elements, natoms, density);
  
  // Fibers Polystyrene //
  ////////////////////////

*/
  /** Absorption spectrum
   *
   * The data sheet from Saint Gobain at
   * https://www.crystals.saint-gobain.com/sites/imdf.crystals.com/files/documents/fiber-brochure.pdf
   * reports the absorption spectrum for BCF-91A. Knowing that the fibers are 1mm thick one can
   * extract the absorption length: starting from the trivial relation:
   *
   * 1 - P(E) = exp(-x/l(E))
   *
   * where P(E) is the probability (thus proportional to the absorption spectrum) for a photon
   * travelling a distance x to be absorbed in the material given the attenuation length l(E), one
   * can extract l(E) from P(E).  By integrating over the thickness of the material L one obtains:
   *
   * (1 - P(E)) * L = l(E) * (1 - exp(-L/l(E)))
   *
   * but the problem now is that l(E) cannot be extracted analytically (inhomogeneus expression).
   * I wrote a Mathematica script that solves it numerically, the result is saved in
   * FiberAbsorption.dat. Remeber that the units are arbitrary because the original absorption
   * spectrum has arbitrary units.
   *
   * Jozsef measured an absorption length of 0.7 mm at 400 nm, the spectrum has been rescaled by
   * that. Reference in Raphael Kneissl's bachelor thesis
   *
   * Emission spectrum: from the Saint-Gobain data sheets
   * WLS time constant: from the Saint-Gobain data sheets
   * -Luigi Pertoldi
   */
/*

  // read absorption spectrum from file
  auto FibersAbsorptionGr = std::unique_ptr<TGraph>(ReadSpectrumFromFile("FibersAbsorption.dat"));
  // read emission spectrum from file
  auto FibersEmissionGr = std::unique_ptr<TGraph>(ReadSpectrumFromFile("FibersEmission.dat"));

  G4double* FiberWLSAbsorption = new G4double[NUMENTRIES_2];
  G4double* FiberWLSEmission   = new G4double[NUMENTRIES_2];
  G4double* FiberRIndex        = new G4double[NUMENTRIES_2];
  G4double* FiberAbsorption    = new G4double[NUMENTRIES_2];

  // stuff that we have no variable information and therefore use a constant value

  // compute scale factor for absorption lengths
  G4double scaleAbs = 0.7*mm / (FibersAbsorptionGr->Eval(400)*m);

  //G4cout << "Making PolystyreneFiber optical properties" << G4endl;
  //G4cout << "energy[eV]\twavelength[nm]\tWLS-absl[mm]\tWLS-emi" << G4endl;

  for (int i = 0; i < NUMENTRIES_2; ++i) {
    FiberRIndex[i] = 1.6;
    FiberAbsorption[i] = 3.8*m;
    // use absorption from file
    auto a = FibersAbsorptionGr->Eval(LambdaE/(ph_energies[i])/nm) *m;
    FiberWLSAbsorption[i] = a >= 0 ? a : 0;
    FiberWLSAbsorption[i] *= scaleAbs;
    
    // use emission from file
    auto e = FibersEmissionGr->Eval(LambdaE/(ph_energies[i])/nm);
    FiberWLSEmission[i] = e >= 0 ? e : 0;
    //G4cout << ph_energies[i]/eV << "\t" << LambdaE/(ph_energies[i])/nm << "\t\t"
    //  << FiberWLSAbsorption[i] << "\t\t" << FiberWLSEmission[i] << "\t" << G4endl;
  }

  G4MaterialPropertiesTable* fiberTable = new G4MaterialPropertiesTable();
  fiberTable->AddProperty     ("RINDEX",          ph_energies, FiberRIndex,        NUMENTRIES_2);
  fiberTable->AddProperty     ("ABSLENGTH",       ph_energies, FiberAbsorption,    NUMENTRIES_2);
  fiberTable->AddProperty     ("WLSABSLENGTH",    ph_energies, FiberWLSAbsorption, NUMENTRIES_2);
  fiberTable->AddProperty     ("WLSCOMPONENT",    ph_energies, FiberWLSEmission,   NUMENTRIES_2);
  fiberTable->AddConstProperty("WLSTIMECONSTANT", 12 *ns);
  //fiberTable->AddConstProperty("WLSMEANNUMBERPHOTONS", ???);
  G4Material::GetMaterial("PolystyreneFiber")->SetMaterialPropertiesTable(fiberTable);

}
*/
//Copied from GEGeometryLArInstHybrid.cc

/*
void LArSOpticalMaterialProperties::Register_Fiber_Cladding_Properties()
{
  //--------------------------------------------------
  // Fiber cladding double wrapped: PMMA (inner) and Fluor-acrylic (outer)
  // It does not really matter the material, just the refractive index
  // https://www.crystals.saint-gobain.com/sites/imdf.crystals.com/files/documents/fiber-product-sheet.pdf
  //--------------------------------------------------
  G4double density;
  std::vector<G4int> natoms;
  std::vector<G4double> fractionMass;
  std::vector<G4String> elements;

  G4NistManager *nistMan = G4NistManager::Instance();

  elements.push_back("C");  natoms.push_back(5);
  elements.push_back("H");  natoms.push_back(8);
  elements.push_back("O");  natoms.push_back(2);
  density = 1.2*g/cm3;

  // -- Rough approximation of BCF-10
  fFiber_claddingInner_material = nistMan->ConstructNewMaterial("PMMA", elements, natoms, density);

  elements.clear();
  natoms.clear();

  // Attach optical properties to the cladding. Only the RIndex is important
  const G4int npoints_fixed = 2;
  G4double claddingFixEnergies[npoints_fixed] = {LambdaE/(650.0*nanometer),LambdaE/(115.0*nanometer)};
  G4double claddingRIndex[npoints_fixed] = {1.49,1.49};
  //Photons seem to get stuck between TPB and fiber cladding, maybe cladding needs absorption length
  //G4double claddingAbsorption[npoints_fixed] = {1*m,1*m};
  G4MaterialPropertiesTable *claddingTable = new G4MaterialPropertiesTable();

  claddingTable->AddProperty("RINDEX",claddingFixEnergies,claddingRIndex,npoints_fixed);
  //claddingTable->AddProperty("ABSLENGTH",claddingFixEnergies,claddingAbsorption,npoints_fixed);

  fFiber_claddingInner_material->SetMaterialPropertiesTable(claddingTable);

  elements.clear();natoms.clear();
  //could not find Fluor-acrylic properties, maybe trade marked?
  //Polyacrylonitrile is similar and used instead, index of refraction is the only real important value (taken from saint-gobain)
  density = 1.184*g/cm3;
  elements.push_back("C");  natoms.push_back(3);
  elements.push_back("H");  natoms.push_back(3);
  elements.push_back("N");  natoms.push_back(1);

  fFiber_claddingOuter_material = nistMan->ConstructNewMaterial("Fluor-acrylic",elements, natoms, density);
  
  G4double claddingOuterFixEnergies[npoints_fixed] = {LambdaE/(650.0*nanometer),LambdaE/(115.0*nanometer)};
  G4double claddingOuterRIndex[npoints_fixed] = {1.42,1.42};
  //Photons seem to get stuck between TPB and fiber cladding, maybe cladding needs absorption length
  //G4double claddingAbsorption[npoints_fixed] = {1*m,1*m};
  G4MaterialPropertiesTable *claddingOuterTable = new G4MaterialPropertiesTable();

  claddingOuterTable->AddProperty("RINDEX",claddingOuterFixEnergies,claddingOuterRIndex,npoints_fixed);
 // claddingTable->AddProperty("ABSLENGTH",claddingOuterFixEnergies,claddingOuterAbsorption,npoints_fixed);

  fFiber_claddingOuter_material->SetMaterialPropertiesTable(claddingOuterTable);
  //G4cout << " Constructed Fiber Cladding Properties"<< G4endl;
}
*/

/*
//copied from GEGeometryLArInstrumentation.cc
void LArSOpticalMaterialProperties::Register_Nylon_Properties()
{



  ///////////
  // Nylon //
  ///////////

  
   // Absorption length from arXiv:1704.02291
   

  // lengths are in m in the file
  auto NylonAbsGraph = std::unique_ptr<TGraph>(ReadSpectrumFromFile("NylonAbsorption.dat"));

  G4double Nylon_absorption[NUMENTRIES_2];
  G4double Nylon_refraction[NUMENTRIES_2];

  for (int i = 0; i < NUMENTRIES_2; i++) {
    Nylon_refraction[i] = 1.54;

    // use absorption length from file
    auto a = NylonAbsGraph->Eval(LambdaE/(ph_energies[i])/nm) *m;
    Nylon_absorption[i] = a >= 0 ? a : 0;
  }

  auto NylonTable = new G4MaterialPropertiesTable();
  NylonTable->AddProperty("RINDEX",       ph_energies, Nylon_refraction, NUMENTRIES_2);
  //GERDA code had this as WLSABSLEGNTH, should be ABSLENGTH
  NylonTable->AddProperty("ABSLENGTH", ph_energies, Nylon_absorption, NUMENTRIES_2);
  G4Material::GetMaterial("Nylon")->SetMaterialPropertiesTable(NylonTable);
}
*/

/*
//stolen from gerdageometry/src/GEGeometryLArInstrumentation.cc for MetalCopper
//TODO Not sure optical proper electroformed copper but for now assuming the same as metal coppper
void LArSOpticalMaterialProperties::Register_Copper_Properties()
{

  ////////////
  // Copper //
  ////////////

  // Measurements from Anne Wegmann's thesis:
  // https://www.mpi-hd.mpg.de/gerda/public/2017/phd2017-anneWegmann.pdf
  

  auto CuReflGr = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_Cu.dat"));

  const G4int n_points_cu = CuReflGr->GetN();
  G4double* ReflectivityCu   = new G4double[n_points_cu];
  G4double* AbsorptionCu   = new G4double[n_points_cu];
  G4double* PhotonEnergyCu   = new G4double[n_points_cu];
  G4double * EfficiencyCu = new G4double[n_points_cu];

  // put energies in ascending order
  for (int i = 0; i < n_points_cu; ++i) {
    PhotonEnergyCu[i] = LambdaE/(CuReflGr->GetX()[n_points_cu-1-i]*nm);
    ReflectivityCu[i] = CuReflGr->GetY()[n_points_cu-1-i];
    AbsorptionCu[i] = 1.0*nm;
    EfficiencyCu[i] = 1;;
    //G4cout<<"Copper reflectivity "<<ReflectivityCu[i]<<" "<<PhotonEnergyCu[i]<<G4endl;
  }

  auto CuOptTable = new G4MaterialPropertiesTable();
  CuOptTable->AddProperty("ABSLENGTH",PhotonEnergyCu, AbsorptionCu, n_points_cu);
  CuOptTable->AddProperty("REFLECTIVITY", PhotonEnergyCu, ReflectivityCu, n_points_cu);
  CuOptTable->AddProperty("EFFICIENCY",PhotonEnergyCu, EfficiencyCu, n_points_cu);

  G4Material::GetMaterial("Copper-EF")->SetMaterialPropertiesTable(CuOptTable);

}
*/

/*
void LArSOpticalMaterialProperties::Register_Germanium_Properties()
{
  ///////////////
  // Germanium //
  ///////////////

*/
  /*** Optical properties of Germanium
   * Needs to be attached to all deadlayer logical surfaces.
   *
   * Measurements from Anne Wegmann's thesis:
   * https://www.mpi-hd.mpg.de/gerda/public/2017/phd2017-anneWegmann.pdf
   * The Ge measured there is our dead-layer Li-doped germanium, at room temperature
   *
   * Found a reference for reflectivity to VUV light in Germanium:
   * http://prola.aps.org/abstract/PR/v160/i3/p602_1
   * It quotes a reflectivity quite high for UV light (~60-70%), but strongly
   * dependent on the incident angle and surface roughness
  */
/*

  auto GeReflGr = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_Ge.dat"));

  const G4int n_points_ge = GeReflGr->GetN();
  G4double* ReflectivityGe = new G4double[n_points_ge];
  G4double* AbsorptionGe = new G4double[n_points_ge];
  G4double* RIndexGe = new G4double[n_points_ge];
  G4double* PhotonEnergyGe = new G4double[n_points_ge];
  G4double* EfficiencyGe = new G4double[n_points_ge];

  // put energies in ascending order
  for (int i = 0; i < n_points_ge; ++i) {
    PhotonEnergyGe[i] = LambdaE/(GeReflGr->GetX()[n_points_ge-1-i]*nm);
    ReflectivityGe[i] = GeReflGr->GetY()[n_points_ge-1-i];
    AbsorptionGe[i] = 1*nm;
    RIndexGe[i] = 1.25;
    EfficiencyGe[i] = 1.0;
  }

  G4MaterialPropertiesTable *geOptTable = new G4MaterialPropertiesTable();
  //Need to add absorption length else photons will propagate through the germanium with infinite attenuation length
  geOptTable->AddProperty("ABSLENGTH", PhotonEnergyGe, AbsorptionGe, n_points_ge);
  geOptTable->AddProperty("REFLECTIVITY", PhotonEnergyGe, ReflectivityGe, n_points_ge);
  geOptTable->AddProperty("EFFICIENCY", PhotonEnergyGe, EfficiencyGe, n_points_ge);
  //geOptTable->AddProperty("RINDEX", PhotonEnergyGe, RIndexGe, n_points_ge);
  
  //LGND naming scheme
  G4Material *germanium = G4Material::GetMaterial("Germanium-Enr");
  germanium->SetMaterialPropertiesTable(geOptTable);
  germanium = G4Material::GetMaterial("Germanium-Nat");
  germanium->SetMaterialPropertiesTable(geOptTable);
}
*/

/*
void LArSOpticalMaterialProperties::Register_Silicon_Properties()
{
  /////////////
  // Silicon //
  /////////////

  // Measurements from Anne Wegmann's thesis:
  // https://www.mpi-hd.mpg.de/gerda/public/2017/phd2017-anneWegmann.pdf
   

  auto SiReflGr = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_Si.dat"));

  const G4int n_points_si = SiReflGr->GetN();
  G4double* ReflectivitySi   = new G4double[n_points_si];
  G4double* AbsorptionSi   = new G4double[n_points_si];
  G4double* PhotonEnergySi   = new G4double[n_points_si];

  // put energies in ascending order
  for (int i = 0; i < n_points_si; ++i) {
    PhotonEnergySi[i] = LambdaE/(SiReflGr->GetX()[n_points_si-1-i]*nm);
    ReflectivitySi[i] = SiReflGr->GetY()[n_points_si-1-i];
    AbsorptionSi[i] = 1.0*nm;
  }

  auto siOptTable = new G4MaterialPropertiesTable();
  siOptTable->AddProperty("ABSLENGTH", PhotonEnergySi, AbsorptionSi, n_points_si);
  siOptTable->AddProperty("REFLECTIVITY", PhotonEnergySi, ReflectivitySi, n_points_si);

}
*/

/*
void LArSOpticalMaterialProperties::Register_Teflon_Properties()
{

    /////////////
  // Teflon //
  /////////////

   // Measurements from Anne Wegmann's thesis:
   // https://www.mpi-hd.mpg.de/gerda/public/2017/phd2017-anneWegmann.pdf
   

  auto TeflonReflGr = std::unique_ptr<TGraph>(ReadSpectrumFromFile("Reflectivity_Teflon.dat"));

  const G4int n_points_tef = TeflonReflGr->GetN();
  G4double* ReflectivityTeflon   = new G4double[n_points_tef];
  G4double* AbsorptionTeflon   = new G4double[n_points_tef];
  G4double* PhotonEnergyTeflon   = new G4double[n_points_tef];
  // put energies in ascending order
  for (int i = 0; i < n_points_tef; ++i) {
    PhotonEnergyTeflon[i] = LambdaE/(TeflonReflGr->GetX()[n_points_tef-1-i]*nm);
    ReflectivityTeflon[i] = TeflonReflGr->GetY()[n_points_tef-1-i];
    AbsorptionTeflon[i]   = 1.0 *nm;
  }

  auto TeflonOptTable = new G4MaterialPropertiesTable();
  TeflonOptTable->AddProperty("ABSLENGTH", PhotonEnergyTeflon, AbsorptionTeflon, n_points_tef);
  TeflonOptTable->AddProperty("REFLECTIVITY", PhotonEnergyTeflon, ReflectivityTeflon, n_points_tef);

  G4Material::GetMaterial("Teflon")->SetMaterialPropertiesTable(TeflonOptTable);
}
*/

/*
void LArSOpticalMaterialProperties::Register_Silica_Properties()
{
  G4MaterialPropertiesTable *silicaOptTable = new G4MaterialPropertiesTable;

  //from https://refractiveindex.info/?shelf=main&book=SiO2&page=Malitson
  //..........and............
  //Optical constants of silica glass from extreme ultraviolet to far infrared at near room temperature 
  //Rei Kitamura,1 Laurent Pilon,1,* and Miroslaw Jonasz2
  const G4int npoints= 7;
  G4double wavelength[npoints]  = {100.,120.,210.,300.,350.,500.,650.0};
  G4double index[npoints]       = {1.32,2.35,1.54,1.49,1.48,1.46,1.456};
  G4double absorbptionlength[npoints]       = {0.8*m,10*m,10*m,10*m,10*m,10*m,10*m};
  G4double energy[npoints] ;
  for(int i = 0; i < npoints;i++){
    energy[npoints - i - 1] = LambdaE/(wavelength[npoints-1-i]*nm);
    
  }

  silicaOptTable->AddProperty("RINDEX",energy,index,npoints);
  silicaOptTable->AddProperty("ABSLENGTH",energy,absorbptionlength,npoints);
  G4Material::GetMaterial("Silica")->SetMaterialPropertiesTable(silicaOptTable);
}
*/

/*
void LArSOpticalMaterialProperties::Register_VM2000()
{
  G4MaterialPropertiesTable *vm2000OptTable = new G4MaterialPropertiesTable;
  G4int ji = 0;
  G4double ee=0;
  // Build table with photon energies
  const G4int spot = 500;

  G4double PPSCHighE = LambdaE /(115*nanometer);
  G4double PPSCLowE = LambdaE /(650*nanometer); //598
  G4double dee = ((PPSCHighE - PPSCLowE) / ((G4double)(spot-1)));
  G4double LAr_SCPP[spot];
  for (ji = 0; ji < spot; ji++)
  {
    ee=PPSCLowE+ ((G4double)ji) * dee;
    LAr_SCPP[ji]=ee;
  }
  ///Reflector (VM2000)
  //From Dario's thesis, reflectivity of VM2000 is ~98% above 370 nm
  //and ~15% below it (almost a step-function)

  G4double Reflectivity[spot];
  G4double Efficiency[spot];

  for (ji=0;ji < spot; ji++)
  {
    if (LAr_SCPP[ji] < (LambdaE/(370*nanometer)))
      Reflectivity[ji] = 0.98; //visible
    else
      Reflectivity[ji] = 0.15; //UV
    Efficiency[ji] = 0.0;
  }
  vm2000OptTable->AddProperty("REFLECTIVITY",LAr_SCPP,Reflectivity,spot);
  vm2000OptTable->AddProperty("EFFICIENCY",LAr_SCPP,Efficiency,spot);

  G4Material::GetMaterial("VM2000")->SetMaterialPropertiesTable(vm2000OptTable);
}
*/

/*
void LArSOpticalMaterialProperties::Register_StainlessSteel()
{
    // Attach properties to the other materials
   // -- germanium
   //
  char* path = getenv("LARSOPTICALDATA");
  if (!path)
  {
    G4cout<< "LARSOPTICALDATA environment variable not set! Assuming local input (./)."
                  << "You find the files in $LArS/opticalData. Set LARSOPTICALDATA to point there." << G4endl;
    path = (char*) ".";
  }
  G4String pathString(path);

  G4MaterialPropertiesTable *ssOptTable = new G4MaterialPropertiesTable();
  G4String pathFile = pathString + "/RIndexReal_SS.dat";

  TGraph *ssRIndexReal = new TGraph(pathFile.data(),"%lg,%lg,%*lg");  
  G4double *waveIndexRealSi = new G4double[ssRIndexReal->GetN()];
  G4double *nrgIndexRealSi = new G4double[ssRIndexReal->GetN()];

  pathFile = pathString + "/RIndexImag_SS.dat";
  TGraph *ssRIndexImag = new TGraph(pathFile.data(),"%lg,%lg,%*lg");
  G4double *waveIndexImagSi = new G4double[ssRIndexImag->GetN()];
  G4double *nrgIndexImagSi = new G4double[ssRIndexReal->GetN()];

  G4int NpointsReal =  ssRIndexReal->GetN(); 
  G4int NpointsImag =  ssRIndexImag->GetN(); 
  if(NpointsReal != NpointsImag){
    G4cout<<"RIndexReal_Si.dat has different number of points than RIndexImag_Si.dat"<<G4endl;
  }
  G4double *RIndexSi = new G4double[NpointsReal];
  G4double *absLengthSi = new G4double[NpointsReal];
  for(int i = 0; i < ssRIndexReal->GetN();i++){

    waveIndexRealSi[i] = (ssRIndexReal->GetX())[i];
    waveIndexImagSi[i] = (ssRIndexImag->GetX())[i];

    nrgIndexRealSi[NpointsReal-i-1] = LambdaE/(waveIndexRealSi[i]*nm);
    nrgIndexImagSi[NpointsImag-i-1] = LambdaE/(waveIndexImagSi[i]*nm);

    RIndexSi[i] = sqrt( (ssRIndexReal->GetY())[i]*(ssRIndexReal->GetY())[i] +(ssRIndexImag->GetY())[i]*(ssRIndexImag->GetY())[i] );
    absLengthSi[i] = waveIndexRealSi[i]/(4*pi*(ssRIndexImag->GetY())[i]);//skin depth ~100 nm
  }


  ssOptTable->AddProperty("RINDEX",nrgIndexRealSi,RIndexSi,NpointsReal);
  ssOptTable->AddProperty("ABSLENGTH",nrgIndexRealSi,absLengthSi,NpointsReal);

  G4Material *ssteel = G4Material::GetMaterial("Steel");
  ssteel->SetMaterialPropertiesTable(ssOptTable);
}
*/

TGraph* LArSOpticalMaterialProperties::ReadSpectrumFromFile(G4String filename) {

  //G4cout << "Looking for " << filename << " file" << G4endl;
  G4String pathFile;
  if (!getenv("LARSOPTICALDATA")) {
    G4cout << "LARSOPTICALDATA environment variable not set! Setting it to '.'" << G4endl;
    pathFile = ".";
  }
  else pathFile = G4String(getenv("LARSOPTICALDATA"));
  pathFile += "/" + filename;
  if(!std::ifstream(pathFile).is_open()) {
    G4cout << "Could not find " << pathFile << ". pleas set the LARSOPTICALDATA variable." << G4endl;
  }

  auto _g = new TGraph(pathFile.data());

  if (!_g->IsZombie() and _g->GetN() > 0 ) {
    G4cout << "Spectrum (" << _g->GetN()
                   << " points) successfully loaded from " << filename << G4endl;
  } else {
    G4cout << "could not read data from from " << pathFile.data() << G4endl;
  }

  return _g;
}
