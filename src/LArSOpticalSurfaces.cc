//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                                                                           //
//                         MaGe Simulation                                   //
//                                                                           //
//      This code implementation is the intellectual property of the         //
//      MAJORANA and Gerda Collaborations. It is based on Geant4, an         //
//      intellectual property of the RD44 GEANT4 collaboration.              //
//                                                                           //
//                        *********************                              //
//                                                                           //
//    Neither the authors of this software system, nor their employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
//
// $Id: MGcodeTemplate.cc,v 1.1 2004-12-09 08:58:35 pandola Exp $
//
//
//---------------------------------------------------------------------------//
/**
 * SPECIAL NOTES:
 */
//
//---------------------------------------------------------------------------//
/**
 * AUTHOR: Neil McFadden
 * CONTACT: nmcfadde@unm.edu
 * FIRST SUBMISSION: 
 Luigi Perdorti
 *
 * REVISION:
 *
 */
//---------------------------------------------------------------------------//
//


#include "LArSOpticalSurfaces.hh"

// Geant4
#include "globals.hh"
#include "G4Material.hh"

using namespace CLHEP;
const G4double LArSOpticalSurfaces::LambdaE = twopi *1.973269602e-16 * m * GeV;

std::map<std::string, G4OpticalSurface*> LArSOpticalSurfaces::fOpticalSurfaces;

LArSOpticalSurfaces::LArSOpticalSurfaces() {

  G4cout<< "Initializing optical surfaces" << G4endl;;


  /////////////////////////////////
  // Initialize optical surfaces //
  /////////////////////////////////

  G4String               name;
  G4OpticalSurfaceModel  model;
  G4OpticalSurfaceFinish finish;
  G4SurfaceType          surface_type;
  G4double               smoothness;
  G4double               roughness;

  std::string surf_name;

  // interface between TPB and LAr =======================================================================
  surf_name = "LArToTPB";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric,
      smoothness   = .1 // smoothness 0.5 seemed too high, lowered to 0.1
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
      G4Material::GetMaterial("TPB")->GetMaterialPropertiesTable());//added by Gabriela

  // interface between LAr and acrylic =======================================================================
  surf_name = "LArToAcrylic";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = polished, //changed to polished
      surface_type = dielectric_dielectric
      //smoothness   = .05 //removed smoothness 
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
      G4Material::GetMaterial("Acrylic")->GetMaterialPropertiesTable());

  // interface between TPB and Nylon =======================================================================
  surf_name = "TPBToNylon";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
      G4Material::GetMaterial("TPBOnNylon")->GetMaterialPropertiesTable());
  
  // interface between Teflon and LAr ====================================================================
  surf_name = "LArToTeflon";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Teflon")->GetMaterialPropertiesTable());
  
  // interface between Tetratex and TPB ====================================================================
  surf_name = "TPBToTetratex";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground, // changed to ground
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Tetratex")->GetMaterialPropertiesTable());

  // interface between TPBOnTetratex and LAr (added by Gabriela) ============================================
  // not in use now, since I am simulating them separately 
  /*  surf_name = "LArToTPBOnTetratex"; 
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = groundfrontpainted, 
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("TPBOnTetratex")->GetMaterialPropertiesTable());*/

  // interface between Tetratex and LAr ====================================================================
  surf_name = "LArToTetratex";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = groundfrontpainted, // changed to ground
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Tetratex")->GetMaterialPropertiesTable());
  
  // "Black" surface, using Metal Velvet =====================================================
  // https://www.acktar.com/wp-content/uploads/2017/12/MAXiBLACK_Super_Black_Polymer-2.pdf
  const G4int num = 4;
  G4double Wavelength[num] = {100, 200, 301, 650};
  surf_name = "MetalVelvet";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );

  G4double BlackPhotonEnergy [num];
  G4double BlackReflectivity [num];
  G4double BlackEfficiencyEnergy   [num];

  for (G4int i=0; i < num; i++) {
    BlackPhotonEnergy[i] = LambdaE/(Wavelength[(num-1)-i]*nm);
    BlackReflectivity[i] = 0.007;//low but not zero 0.007
    BlackEfficiencyEnergy[i]   = 1.0;
  }

  auto BlackTable = new G4MaterialPropertiesTable();
  BlackTable->AddProperty("REFLECTIVITY", BlackPhotonEnergy, BlackReflectivity, num);
  BlackTable->AddProperty("EFFICIENCY",   BlackPhotonEnergy, BlackEfficiencyEnergy,   num);

  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(BlackTable);

  // Surface of the disk where the source is deposited =========================================
  // edit: the material of the disk is actually stainless steel.
  surf_name = "AlSource";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified, //only applies to dielectric_dielectric?
      finish       = ground,
      surface_type = dielectric_metal
      //roughness    = 0.5 // setting roughness or smoothness here did not change anything...
    )
  );


  auto AlSrefGraph = std::unique_ptr<TGraph>(ReadData("AlS_reflectivity.dat", "%lg %lg"));
  G4double *AlSWL=AlSrefGraph->GetX();
  G4double *AlSReflectivity=AlSrefGraph->GetY();

  auto AlSrefGraph_SS = std::unique_ptr<TGraph>(ReadData("AlS_reflectivity.dat", "%lg %*lg %lg"));
  G4double *AlS_SS = AlSrefGraph_SS->GetY();

  auto AlSrefGraph_SL = std::unique_ptr<TGraph>(ReadData("AlS_reflectivity.dat", "%lg %*lg %*lg %lg"));
  G4double *AlS_SL = AlSrefGraph_SL->GetY();

  auto AlSrefGraph_BS = std::unique_ptr<TGraph>(ReadData("AlS_reflectivity.dat", "%lg %*lg %*lg %*lg %lg"));
  G4double *AlS_BS = AlSrefGraph_BS->GetY();

  const G4int num_ = 4;
  G4double AlSPhotonEnergy [num_];
  G4double AlSEfficiencyEnergy [num_];
  
  G4String s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/AlS_ref.dat"; std::ofstream outfile_AlS(s_outfile.c_str());

  for (G4int i=0; i < num_; i++) {
    AlSPhotonEnergy[i] = LambdaE/(AlSWL[i]*nm);
    AlSEfficiencyEnergy[i]   = 1.0;//changed by neil from 0 to 1.. If it is 0, no energy is deposited, 
                                   //if it is less than 1 and greater than 0, then G4 rolls a dice to see if energy is 
   outfile_AlS<<LambdaE/AlSPhotonEnergy[i]/nm<<" "<<AlSReflectivity[i]<<" "<<AlS_SS[i]<<" "<<AlS_SL[i]<<" "<<AlS_BS[i]<<G4endl;
  }

  auto AlSTable = new G4MaterialPropertiesTable();
  AlSTable->AddProperty("REFLECTIVITY", AlSPhotonEnergy, AlSReflectivity, num_); //default: T=0, A=1-R-T 
  AlSTable->AddProperty("EFFICIENCY",   AlSPhotonEnergy, AlSEfficiencyEnergy,   num_);
  AlSTable->AddProperty("SPECULARLOBECONSTANT", AlSPhotonEnergy, AlS_SL, num_);
  AlSTable->AddProperty("SPECULARSPIKECONSTANT",AlSPhotonEnergy, AlS_SS, num_);
  AlSTable->AddProperty("BACKSCATTERCONSTANT", AlSPhotonEnergy, AlS_BS, num_);

  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(AlSTable);
  //AlSTable->DumpTable();

  // interface between SiPM and fibers ====================================================================
  // SiPM "sensitive" surface.. this will be a border surface between the fibers and the upper shroud
  // Set sensitivity to 100% to collect all photons and correct for Q.E. off line 
  // -N. McFadden 
  surf_name = "FiberToSiPM";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );
   const G4int npoints_eff = 10;
  G4double SiPMWL[npoints_eff] = {100.*nm,280.*nm,310.*nm,350.*nm,400.*nm,435.*nm,505.*nm,525.*nm,595.*nm,670.*nm};
  G4double SiPMEfficiencyWavelength[npoints_eff] =   {0.0,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00};
  G4double SiPMEfficiencyEnergy[npoints_eff];
  G4double SiPMReflectivity[npoints_eff];// = {0.0,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};
  G4double SiPMPhotonEnergy[npoints_eff];
  for (G4int ji=0; ji < npoints_eff; ji++){
    // Zero reflectivity and 1.0 efficiency means that the
    // photons are all "absorbed and identified as hits"
    SiPMPhotonEnergy[ji] = LambdaE/(SiPMWL[(npoints_eff-1)-ji]);
    SiPMReflectivity[ji] = 0.0; // Set the reflectivity in the fibers to zero, otherwise 99.999 % is reflected due to index of refraction
    SiPMEfficiencyEnergy[ji] = SiPMEfficiencyWavelength[(npoints_eff-1)-ji]; // Quantum efficiency of the SiPM. 
  }
  auto sipmOptTable = new G4MaterialPropertiesTable();
  sipmOptTable->AddProperty("EFFICIENCY",SiPMPhotonEnergy,SiPMEfficiencyEnergy,npoints_eff);
  sipmOptTable->AddProperty("REFLECTIVITY",SiPMPhotonEnergy,SiPMReflectivity,npoints_eff);
  
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(sipmOptTable);

  // interface for SiPM Wallpaper ===============================================
	// MPPC S13370/S13371 series
  // Set sensitivity from https://www.hamamatsu.com/eu/en/product/optical-sensors/mppc/mppc_mppc-array/index.html#anchor01 
  // -N. McFadden 
  surf_name = "SiPMWallpaper";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );
   const G4int npointsMPPC = 11;
  G4double MPPCWL[npointsMPPC] =           {100.*nm,120*nm,128.*nm,175.*nm,350.*nm,400.*nm,435.*nm,505.*nm,525.*nm,595.*nm,670.*nm};
  G4double MPPCEfficiencyWavelength[npointsMPPC] =   {0.01   ,0.11,  0.15,   0.24,   0.24,   0.24,   0.24,   0.24,   0.24,   0.24,   0.24};
  //G4double MPPCEfficiencyWavelength[npointsMPPC] =   {1.0,1.,1.,1.,1,1,1,1,1,1,1};
  G4double MPPCEfficiencyEnergy[npointsMPPC];
  G4double MPPCReflectivity[npointsMPPC];// = {0.0,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};
  G4double MPPCPhotonEnergy[npointsMPPC];
  for (G4int ji=0; ji < npointsMPPC; ji++){
    MPPCPhotonEnergy[ji] = LambdaE/(MPPCWL[(npointsMPPC-1)-ji]);
    MPPCReflectivity[ji] = 0.0; // Set the reflectivity in the fibers to zero, otherwise 99.999 % is reflected due to index of refraction
    MPPCEfficiencyEnergy[ji] = MPPCEfficiencyWavelength[(npointsMPPC-1)-ji]; // Quantum efficiency of the MPPC. 
  }
  auto MPPCOptTable = new G4MaterialPropertiesTable();
  MPPCOptTable->AddProperty("EFFICIENCY",MPPCPhotonEnergy,MPPCEfficiencyEnergy,npointsMPPC);
  MPPCOptTable->AddProperty("REFLECTIVITY",MPPCPhotonEnergy,MPPCReflectivity,npointsMPPC);
  
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(MPPCOptTable);

  //VUV PMT for LArS
  surf_name = "MgF2-PMT";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal
    )
  );


  const G4int npointsPMT = 17;
  //Only have one QE value for Vis light, 27.38% at 420nm, assume 0 QE at 100 nm and 700 nm

  auto PMTQEGraph   = std::unique_ptr<TGraph>(ReadData("PMTQE.dat", "%lg %lg"));
  G4double *PMTWL=PMTQEGraph->GetX();
  G4double *PMTEfficiency=PMTQEGraph->GetY();
  G4double PMTReflectivity[npointsPMT];
  G4double PMTPhotonEnergy[npointsPMT];

  s_outfile = G4String(getenv("LARSDIR"))+"/output_spectra/PMTQE.dat"; std::ofstream outfile(s_outfile.c_str());

  for (G4int ji=0; ji < npointsPMT; ji++){
 
    PMTPhotonEnergy[ji] = LambdaE/((PMTWL[ji]*nm));
    PMTReflectivity[ji] = 0.0; 
    outfile<<LambdaE/PMTPhotonEnergy[ji]/nm<<" "<<PMTEfficiency[ji]<<G4endl;
  }
  auto PMTOptTable = new G4MaterialPropertiesTable();
  PMTOptTable->AddProperty("EFFICIENCY",PMTPhotonEnergy,PMTEfficiency,npointsPMT);
  PMTOptTable->AddProperty("REFLECTIVITY",PMTPhotonEnergy,PMTReflectivity,npointsPMT);
  
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(PMTOptTable);


  // Interface between LAr and Detectors =============================================================================
  surf_name = "LArToGe";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = groundfrontpainted,
      surface_type = dielectric_metal,
      smoothness   = 0.5
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Germanium-Enr")->GetMaterialPropertiesTable());

  // Interface between LAr and copper ================================================================================
  surf_name = "LArToCu";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal,
      smoothness   = 0.5
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Copper-EF")->GetMaterialPropertiesTable());

  // Interface between LAr and silicon ================================================================================
  surf_name = "LArToSi";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_metal,
      smoothness   = 0.7
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Silicon")->GetMaterialPropertiesTable());

  // Interface between LAr and PEN ====================================================================================
  surf_name = "LArToPEN";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = ground,
      surface_type = dielectric_dielectric,
      roughness    = 0.5 
   )
 );
 fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
   G4Material::GetMaterial("PEN")->GetMaterialPropertiesTable());



}


LArSOpticalSurfaces::~LArSOpticalSurfaces() {
  // delete all instances stored in the arrays
  for (auto _s : fOpticalSurfaces) delete _s.second;
}

G4OpticalSurface* LArSOpticalSurfaces::GetOpticalSurface(std::string name) {
  auto search = fOpticalSurfaces.find(name);
  if (search == fOpticalSurfaces.end()) {
    G4cout << "Optical surface " << name << " not found! Returning nullptr." << G4endl;;
    return nullptr;
  }

  return search->second;
}

std::vector<std::string> LArSOpticalSurfaces::GetListOfSurfaces() {
  std::vector<std::string> v;
  for (auto& _s : fOpticalSurfaces) v.push_back(_s.first);
  return v;
}

TGraph* ReadData(G4String filename, G4String soption) {

  //G4cout << "Looking for " << filename << " file" << G4endl;
  G4String pathFile;
  if (!getenv("LARSOPTICALDATA")) {
    G4cout << "LARSOPTICALDATA environment variable not set! Setting it to '.'" << G4endl;
    pathFile = ".";
  }
  else pathFile = G4String(getenv("LARSOPTICALDATA"));
  pathFile += "/" + filename;
  if(!std::ifstream(pathFile).is_open()) {
    G4cout << "Could not find " << pathFile << ". please set the LARSOPTICALDATA variable." << G4endl;
  }

  auto _g = new TGraph(pathFile.data(), soption.c_str());

  if (!_g->IsZombie() and _g->GetN() > 0 ) {
    G4cout << "Spectrum/data (" << _g->GetN()
                   << " points) successfully loaded from " << filename << G4endl;
  } else {
    G4cout << "could not read data from from " << pathFile.data() << G4endl;
  }

  return _g;
}
