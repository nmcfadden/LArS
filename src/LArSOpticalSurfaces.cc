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
      smoothness   = .5
    )
  );

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
      finish       = groundfrontpainted, // only lambertian spike reflection
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Tetratex")->GetMaterialPropertiesTable());

  // interface between Tetratex and LAr ====================================================================
  surf_name = "LArToTetratex";
  fOpticalSurfaces.emplace(surf_name,
    new G4OpticalSurface(
      name         = surf_name + "_Surface",
      model        = unified,
      finish       = groundfrontpainted, // only lambertian spike reflection
      surface_type = dielectric_dielectric
    )
  );
  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(
    G4Material::GetMaterial("Tetratex")->GetMaterialPropertiesTable());
  
  // "Black" surface, using Metal Velvet
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
    BlackReflectivity[i] = 0.007;//low but not zero
    BlackEfficiencyEnergy[i]   = 0.0;
  }

  auto BlackTable = new G4MaterialPropertiesTable();
  BlackTable->AddProperty("REFLECTIVITY", BlackPhotonEnergy, BlackReflectivity, num);
  BlackTable->AddProperty("EFFICIENCY",   BlackPhotonEnergy, BlackEfficiencyEnergy,   num);

  fOpticalSurfaces[surf_name]->SetMaterialPropertiesTable(BlackTable);

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
  G4double PMTWL[npointsPMT] =           {100.*nm,117.*nm,119.*nm,122.*nm,124.*nm,
                                          126.*nm,128.*nm,130.*nm,132.*nm,134.*nm,
                                          138.*nm,145.*nm,165.*nm,185.*nm,210.*nm,
                                          420.*nm,700.*nm};
  G4double PMTEfficiencyWavelength[npointsPMT] =
                                         {0.00   ,  0.158,  0.184,  0.215,  0.214,
                                          0.218  ,  0.228,  0.240,  0.250,  0.262,
                                          0.268  ,  0.259,  0.297,  0.378,  0.325,
                                          0.2738,0};
  //G4double PMTCEfficiencyWavelength[npointsPMT] =   {1.0,1.,1.,1.,1,1,1,1,1,1,1};
  G4double PMTEfficiencyEnergy[npointsPMT];
  G4double PMTReflectivity[npointsPMT];// = {0.0,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};
  G4double PMTPhotonEnergy[npointsPMT];
  for (G4int ji=0; ji < npointsPMT; ji++){
    PMTPhotonEnergy[ji] = LambdaE/(PMTWL[(npointsPMT-1)-ji]);
    PMTReflectivity[ji] = 0.0; 
    PMTEfficiencyEnergy[ji] = PMTEfficiencyWavelength[(npointsPMT-1)-ji]; // Quantum efficiency of the PMTC. 
  }
  auto PMTOptTable = new G4MaterialPropertiesTable();
  PMTOptTable->AddProperty("EFFICIENCY",PMTPhotonEnergy,PMTEfficiencyEnergy,npointsPMT);
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



