#include "LArSDetectorConstruction.hh"

map<G4String, G4double> LArSDetectorConstruction::m_hGeometryParameters;

LArSDetectorConstruction::LArSDetectorConstruction(G4String fName){  
    m_pDetectorMessenger = new LArSDetectorMessenger(this);
    detRootFile = fName;
}

LArSDetectorConstruction::~LArSDetectorConstruction(){
    delete m_pDetectorMessenger;
}

G4double LArSDetectorConstruction::GetGeometryParameter(const char *szParameter){
    return m_hGeometryParameters[szParameter];
}


G4VPhysicalVolume* LArSDetectorConstruction::Construct(){
  //////////////// Define Materials //////////////////////
  LArSMaterials *Materials = new LArSMaterials();
  Materials->DefineMaterials(); 
  

  ///////////////// Place World Volume/////////////////////
  G4Box *World_volume_solid = new G4Box("World_volume", 20*m, 20*m, 20*m);
  G4LogicalVolume *World_volume_logical = new G4LogicalVolume(World_volume_solid, G4Material::GetMaterial("Vacuum"), "World_volume_logical", 0, 0, 0);
  World_volume_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), World_volume_logical, "World_volume", 0, false, 0);
  //Pass Mother volume along after each construction
  Mother_volume = World_volume_logical; 

  //////////////// Construct Laboratory ///////////////////
  LArSConstructLab *lab = new LArSConstructLab(this);
  Mother_volume = lab->Construct();
  //Place First mother Volume
  //G4cout << G4endl << "Laboratory constructed...Mother Volume name is "<<Mother_volume->GetName() << G4endl;
  
  //////////////// Construct Cryostat//////////////////
  LArSConstructCryostat *cryostat = new LArSConstructCryostat(this);
  Mother_volume = cryostat->Construct();
  //Steel_cryostat_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.*cm,0.*m), Steel_cryostat_logical, "Steel_cryostat_physical", Mother_volume, false, 0);
  
  //G4cout << G4endl << "Cryostat constructed...Mother Volume name is "<<Mother_volume->GetName() << G4endl;

  //////////////// Construct LAr//////////////////
  LArSActiveVolume * lar = new LArSActiveVolume(this);
  Mother_volume = lar->Construct();
  //G4cout << G4endl << "LAr constructed...Mother Volume name is "<<Mother_volume->GetName() << G4endl;
  
  //*****************************************Defining sensitivity*****************************************
  G4SDManager *SDManager = G4SDManager::GetSDMpointer(); 
  LArSLXeSensitiveDetector *LArSD = new LArSLXeSensitiveDetector("LArSD");
  SDManager->AddNewDetector(LArSD); 
  lar->GetMotherVolume()->SetSensitiveDetector(LArSD);

  ////////////////Construct PMT Cell////////////////////
  LArSPMTCell *pmtCell = new LArSPMTCell(this);
  Mother_volume = pmtCell->Construct();

  /////////////////Overlap Check////////////////////
  if(pCheckOverlap) SecondOverlapCheck();

  return World_volume_physical;
}

//Overlap check

void LArSDetectorConstruction::SecondOverlapCheck()
{


  G4PhysicalVolumeStore* thePVStore = G4PhysicalVolumeStore::GetInstance();
  G4cout << "\n" << "******************************" << G4endl;
  G4cout << "\n" << "CHECK FOR OVERLAPS" << G4endl;
  G4cout << "\n" << "******************************" << G4endl;
  G4cout <<"\n" << G4endl;

  G4cout << thePVStore->size() << " physical volumes are defined" << G4endl;

  G4bool overlapFlag = false;

  for (size_t i=0; i<thePVStore->size();i++){
      overlapFlag = (*thePVStore)[i]->CheckOverlaps(5000) | overlapFlag;
  }
    
  G4cout << "\n" << G4endl;

}


// SetLXeAbsorbtionLength

void LArSDetectorConstruction::SetLXeAbsorbtionLength(G4double dAbsorbtionLength) {
  G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));

  if(pLXeMaterial)
    {
      G4cout << "----> Setting LXe absorbtion length to " << dAbsorbtionLength/cm << " cm" << G4endl;

      G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();

      G4double LXe_PP[] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double LXe_ABSL[] = {dAbsorbtionLength, dAbsorbtionLength, dAbsorbtionLength};
      pLXePropertiesTable->RemoveProperty("ABSLENGTH");
      pLXePropertiesTable->AddProperty("ABSLENGTH", LXe_PP, LXe_ABSL, 3);
    }
  else
    {
      G4cout << "ls!> LXe materials not found!" << G4endl;
      exit(-1);
    }
}

// SetGXeAbsorbtionLength

void LArSDetectorConstruction::SetGXeAbsorbtionLength(G4double dAbsorbtionLength) {
  G4Material *pGXeMaterial = G4Material::GetMaterial(G4String("GXe"));
  
  if(pGXeMaterial)
    {
      G4cout << "----> Setting GXe absorbtion length to " << dAbsorbtionLength/m << " m" << G4endl;
    
      G4MaterialPropertiesTable *pGXePropertiesTable = pGXeMaterial->GetMaterialPropertiesTable();
    
      const G4int iNbEntries = 3;
    
      G4double GXe_PP[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double GXe_ABSL[iNbEntries] = {dAbsorbtionLength, dAbsorbtionLength, dAbsorbtionLength};
      pGXePropertiesTable->RemoveProperty("ABSLENGTH");
      pGXePropertiesTable->AddProperty("ABSLENGTH", GXe_PP, GXe_ABSL, iNbEntries);
    }
  else
    {
      G4cout << "ls!> GXe materials not found!" << G4endl;
      exit(-1);
    }
}

// SetTeflonReflectivity

void LArSDetectorConstruction::SetTeflonReflectivity(G4double dReflectivity) {
  G4Material *pTeflonMaterial = G4Material::GetMaterial(G4String("Teflon"));

  if(pTeflonMaterial)
    {
      G4cout << "----> Setting Teflon reflectivity to " << dReflectivity << G4endl;

      G4MaterialPropertiesTable *pTeflonPropertiesTable = pTeflonMaterial->GetMaterialPropertiesTable();

      G4double teflon_PP[] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
      G4double teflon_REFL[] = {dReflectivity, dReflectivity, dReflectivity};
      pTeflonPropertiesTable->RemoveProperty("REFLECTIVITY");
      pTeflonPropertiesTable->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, 3);
    }
  else
    {
      G4cout << "ls!> Teflon material not found!" << G4endl;
      exit(-1);
    }
}

// SetGXeTeflonReflectivity

void LArSDetectorConstruction::SetGXeTeflonReflectivity(G4double dGXeReflectivity)
{
  G4Material *pGXeTeflonMaterial = G4Material::GetMaterial(G4String("GXeTeflon"));
  
  if(pGXeTeflonMaterial)
    {
      G4cout << "----> Setting GXe Teflon reflectivity to " << dGXeReflectivity << G4endl;
    
      G4MaterialPropertiesTable *pGXeTeflonPropertiesTable = pGXeTeflonMaterial->GetMaterialPropertiesTable();
    
      const G4int iNbEntries = 3;
    
      G4double teflon_PP[iNbEntries] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
      G4double teflon_REFL[iNbEntries] = {dGXeReflectivity, dGXeReflectivity, dGXeReflectivity};
      pGXeTeflonPropertiesTable->RemoveProperty("REFLECTIVITY");
      pGXeTeflonPropertiesTable->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, iNbEntries);
   }
  else
   {
     G4cout << "ls!> GXe Teflon material not found!" << G4endl;
     exit(-1);
   }
}

// SetLXeRayScatterLength

void LArSDetectorConstruction::SetLXeRayScatterLength(G4double dRayScatterLength) {
  G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));
  
  if(pLXeMaterial)
    {      
      G4cout << "----> Setting LXe scattering length to " << dRayScatterLength/cm << " cm" << G4endl;
      
      G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
              
      G4double LXe_PP[] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double LXe_SCAT[] = {dRayScatterLength, dRayScatterLength, dRayScatterLength};
      pLXePropertiesTable->RemoveProperty("RAYLEIGH");
      pLXePropertiesTable->AddProperty("RAYLEIGH", LXe_PP, LXe_SCAT, 3);
    }
  else
    {
      G4cout << "ls!> LXe materials not found!" << G4endl;
      exit(-1);
    }

}

// SetLXeRefractionIndex

void LArSDetectorConstruction::SetLXeRefractionIndex(G4double dRefractionIndex)
{
  G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));
  
  if(pLXeMaterial)
    {
      G4cout << "----> Setting LXe refraction index to " << dRefractionIndex << G4endl;
    
      G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
	
      const G4int iNbEntries = 3;
    
      G4double LXe_PP[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double LXe_RI[iNbEntries] = {dRefractionIndex, dRefractionIndex, dRefractionIndex};
      pLXePropertiesTable->RemoveProperty("RINDEX");
	  pLXePropertiesTable->AddProperty("RINDEX", LXe_PP, LXe_RI, iNbEntries);
    }
  else
    {
      G4cout << "ls!> LXe materials not found!" << G4endl;
      exit(-1);
    }
}

// SetLXeScintillation

void LArSDetectorConstruction::SetLXeScintillation(G4bool bScintillation) {
  G4cout << "----> Setting LXe(GXe) scintillation to " << bScintillation << G4endl;

    G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));
    if(pLXeMaterial) {
        G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
        if(bScintillation){
        pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 1./(21.6*eV)); 
        }    
}
  else
  {
    G4cout << "ls!> LXe materials not found!" << G4endl;
    exit(-1);
  }

  G4Material *pGXeMaterial = G4Material::GetMaterial(G4String("GXe"));
  if(pGXeMaterial){
    G4MaterialPropertiesTable *pGXePropertiesTable = pGXeMaterial->GetMaterialPropertiesTable();
    if(bScintillation){
        pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 1./(21.6*eV)); //ToDo: keep in mind that this changes the default value
    }  
  }
  else
  {
    G4cout << "ls!> GXe materials not found!" << G4endl;
    exit(-1);
  }
}

// SetSS304LSteelReflectivity

void LArSDetectorConstruction::SetSS304LSteelReflectivity(G4double dSteelReflectivity) {
  G4Material *pSteelMaterial = G4Material::GetMaterial(G4String("SS304LSteel"));

  if(pSteelMaterial)
    {
      G4cout << "----> Setting SS304LSteel reflectivity to " << dSteelReflectivity << G4endl;

      G4MaterialPropertiesTable *pSteelPropertiesTable = pSteelMaterial->GetMaterialPropertiesTable();

      G4double Steel_PP[] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
      G4double Steel_REFL[] = {dSteelReflectivity, dSteelReflectivity, dSteelReflectivity};
      pSteelPropertiesTable->RemoveProperty("REFLECTIVITY");
      pSteelPropertiesTable->AddProperty("REFLECTIVITY", Steel_PP, Steel_REFL, 3);
    }
  else
    {
      G4cout << "ls!> SS304LSteel material not found!" << G4endl;
      exit(-1);
    }
}





// Set GXeMeshTransparency

void LArSDetectorConstruction::SetGXeMeshTransparency(G4double dTransparency)
{
  G4Material *pMeshMaterial = G4Material::GetMaterial(G4String("GridMeshSS316LSteelGXe"));
  
  if(pMeshMaterial)
    {
      G4cout << "----> Setting GXe grid transparency to " << dTransparency*100 << " %" << G4endl;
      G4double dAbsorptionLength =  ((G4double)GetGeometryParameter("GridMeshThickness"))/(-log(dTransparency)); 
      G4cout << "----> Setting GXe grid absorption length to " << dAbsorptionLength/mm << " mm" << G4endl;
      G4MaterialPropertiesTable *pGateMeshPropertiesTable = pMeshMaterial->GetMaterialPropertiesTable();
      const G4int iNbEntries = 3;
      G4double pdMeshPhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double pdMeshAbsorptionLength[iNbEntries] = {dAbsorptionLength, dAbsorptionLength, dAbsorptionLength};
      pGateMeshPropertiesTable->RemoveProperty("ABSLENGTH");
      pGateMeshPropertiesTable->AddProperty("ABSLENGTH", pdMeshPhotonMomentum, pdMeshAbsorptionLength, iNbEntries);
   }
  else
    {
      G4cout << "ls!> GridMeshSS316LSteelGXe not found!" << G4endl;
      exit(-1);
    }
}

// Set GXeMeshTransparency

void LArSDetectorConstruction::SetLXeMeshTransparency(G4double dTransparency)
{
  G4Material *pMeshMaterial = G4Material::GetMaterial(G4String("GridMeshSS316LSteelLXe"));
  
  if(pMeshMaterial)
    {
      G4cout << "----> Setting LXe grid transparency to " << dTransparency*100 << " %" << G4endl;
      G4double dAbsorptionLength =  ((G4double)GetGeometryParameter("GridMeshThickness"))/(-log(dTransparency)); 
      G4cout << "----> Setting LXe grid absorption length to " << dAbsorptionLength/mm << " mm" << G4endl;
      G4MaterialPropertiesTable *pGateMeshPropertiesTable = pMeshMaterial->GetMaterialPropertiesTable();
      const G4int iNbEntries = 3;
      G4double pdMeshPhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double pdMeshAbsorptionLength[iNbEntries] = {dAbsorptionLength, dAbsorptionLength, dAbsorptionLength};
      pGateMeshPropertiesTable->RemoveProperty("ABSLENGTH");
      pGateMeshPropertiesTable->AddProperty("ABSLENGTH", pdMeshPhotonMomentum, pdMeshAbsorptionLength, iNbEntries);
   }
  else
    {
      G4cout << "ls!> GridMeshSS316LSteelLXe not found!" << G4endl;
      exit(-1);
    }
}

