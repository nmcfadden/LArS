#include "LArSActiveVolume.hh"


LArSActiveVolume::LArSActiveVolume( LArSDetectorConstruction * constructorClass)
{
  Constructor_class = constructorClass;
}

LArSActiveVolume::~LArSActiveVolume() {;}

G4LogicalVolume* LArSActiveVolume::Construct(){

//**********************************************PARAMETERS*********************************************    
  //Materials
  G4Material *LAr = G4Material::GetMaterial("Argon-Liq");;
   
  G4double General_phi_start = 0.*deg;
  G4double General_phi_total = 360*deg;

  G4double z_plane[2] = {0.,0.};
  z_plane[0] = -219.5*mm;
  z_plane[1] = 226*mm;

  G4double r_inner[2] = {0.,0.};
  r_inner[0] = 0.*m;
  r_inner[1] = 0.*m;

  G4double r_outer[2] = {0.,0.};
  r_outer[0] = 125*mm;
  r_outer[1] = 125*mm;
  //***********************************************SOLIDS*************************************************
  G4Polycone * LAr_Solid = new G4Polycone("LArSolid",General_phi_start, General_phi_total, 2,z_plane,r_inner,r_outer);
    
    
//********************************************LOGICALVOLUMES*******************************************
  //Logical volumes
  LAr_logical = new G4LogicalVolume(LAr_Solid, LAr, "LAr_logical", 0, 0, 0); 
    
    
    
//********************************************PHYSICALVOLUMES******************************************
  LAr_physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), LAr_logical, "LAr_physical", Constructor_class->GetMotherVolumeLogical(), false, 0);
    
  return LAr_logical;
}
    

G4LogicalVolume* LArSActiveVolume::GetMotherVolume(){
  return this->LAr_logical;
}
