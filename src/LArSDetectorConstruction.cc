#include "LArSDetectorConstruction.hh"

std::map<G4String, G4double> LArSDetectorConstruction::m_hGeometryParameters;

LArSDetectorConstruction::LArSDetectorConstruction(G4String fName)
{  
    m_pDetectorMessenger = new LArSDetectorMessenger(this);
    detRootFile = fName;
}

LArSDetectorConstruction::~LArSDetectorConstruction(){
    delete m_pDetectorMessenger;
}

G4double LArSDetectorConstruction::GetGeometryParameter(const char *szParameter){
    return m_hGeometryParameters[szParameter];
}


G4VPhysicalVolume* LArSDetectorConstruction::Construct()//bool bAcrylicWindow)  -> attempt to pass the bool for the window
{

  //std::cout<<bAcrylicWindow<<std::endl;
  //////////////// Define Materials //////////////////////
  LArSMaterials *Materials = new LArSMaterials();
  Materials->BuildAll();
  //Intialize optical surfaces
  LArSOpticalSurfaces* opSurfaces = new LArSOpticalSurfaces();

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
  
  //G4cout << G4endl << "Cryostat constructed...Mother Volume name is "<<Mother_volume->GetName() << G4endl;

  //////////////// Construct LAr//////////////////
  LArSActiveVolume * lar = new LArSActiveVolume(this);
  Mother_volume = lar->Construct();
  //G4cout << G4endl << "LAr constructed...Mother Volume name is "<<Mother_volume->GetName() << G4endl;
  
  //*****************************************Defining sensitivity*****************************************
  ////////////////Construct PMT Cell////////////////////
  LArSPMTCell *pmtCell = new LArSPMTCell(this);
  Mother_volume = pmtCell->Construct();

  //get physical volumes by name for optical boundries
  //Some physical boundries are between the LAr
  //LAr boundaries defined here,
  G4PhysicalVolumeStore* volumeStore = G4PhysicalVolumeStore::GetInstance();
  G4int nVolumes = (G4int) volumeStore->size();
  G4String candidateList;
  for(G4int i=0;i<nVolumes;i++) {
    candidateList = (*volumeStore)[i]->GetName();
    G4VPhysicalVolume* phys_vol = (*volumeStore)[i];
    if(candidateList.contains("pmt") || candidateList.contains("PMT") ){
      //QE is only defined in one direction from LAr to window
      new G4LogicalBorderSurface("PMTQE"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("MgF2-PMT"));
    }
    if(candidateList.contains("wallCell")){
      if(UseTetratex()&& UsePEN()){
        new G4LogicalBorderSurface("wallCell"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("LArToTetratex"));
        new G4LogicalBorderSurface(to_string(i)+"wallCell",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("LArToTetratex"));
      }
      else if(UseTPB()){
        new G4LogicalBorderSurface("wallCell"+to_string(i),pmtCell->GetTPBVolume(),phys_vol,opSurfaces->GetOpticalSurface("TPBToTetratex"));
        new G4LogicalBorderSurface(to_string(i)+"wallCell",phys_vol,pmtCell->GetTPBVolume(),opSurfaces->GetOpticalSurface("TPBToTetratex"));
      }
      else{
        new G4LogicalBorderSurface("wallCell"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("MetalVelvet"));
        new G4LogicalBorderSurface(to_string(i)+"wallCell",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("MetalVelvet"));
      }
    }
    if(candidateList.contains("supportRod")){
      new G4LogicalBorderSurface("supportRod"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("MetalVelvet"));
      new G4LogicalBorderSurface(to_string(i)+"supportRod",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("MetalVelvet"));
    }
    if(candidateList.contains("topCell")){
      new G4LogicalBorderSurface("topCell"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("MetalVelvet"));
      new G4LogicalBorderSurface(to_string(i)+"topCell",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("MetalVelvet"));
    }
    if(candidateList.contains("bottomCell")){
      new G4LogicalBorderSurface("bottomCell"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("MetalVelvet"));
      new G4LogicalBorderSurface(to_string(i)+"bottomCell",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("MetalVelvet"));
    }
    if(candidateList.contains("alphaSource")){
      new G4LogicalBorderSurface("alphaSource"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("AlSource"));
      new G4LogicalBorderSurface(to_string(i)+"alpha",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("AlSource"));
    }
    if(UseAcrylicWindow() && (candidateList.contains("acrylic") || candidateList.contains("Acyrlic")) ){
      new G4LogicalBorderSurface("acrylic"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("LArToAcrylic"));
      new G4LogicalBorderSurface(to_string(i)+"acrylic",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("LArToAcrylic"));
    }
    if(UsePEN() && candidateList.contains("PEN")){
      new G4LogicalBorderSurface("PEN"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("LArToPEN"));
      new G4LogicalBorderSurface(to_string(i)+"PEN",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("LArToPEN"));
    }
    if(UseTPB() && candidateList.contains("TPB")){
      new G4LogicalBorderSurface("TPB"+to_string(i),lar->GetPhysicalVolume(),phys_vol,opSurfaces->GetOpticalSurface("LArToTPB"));
      new G4LogicalBorderSurface(to_string(i)+"TPB",phys_vol,lar->GetPhysicalVolume(),opSurfaces->GetOpticalSurface("LArToTPB"));
    }

  }

  /////////////////Overlap Check////////////////////
  if(pCheckOverlap) SecondOverlapCheck();

  return World_volume_physical;
}

//Set Sensitive Volumes
int LArSDetectorConstruction::SetSensitiveVolumes(G4String volName){

  //how to add a single volume to the sensitive volume list
  //if(volName == "LAr_physical")    return 100;

  //How to add all the volumes to the sensitive volume list
  G4PhysicalVolumeStore* volumeStore = G4PhysicalVolumeStore::GetInstance();
  G4int nVolumes = (G4int) volumeStore->size();
  G4String candidateList;
  for(G4int i=0;i<nVolumes;i++) {
    candidateList = (*volumeStore)[i]->GetName();
    if(candidateList == volName) return i+1;
  }
  return 0;
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
