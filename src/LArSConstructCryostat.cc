#include "LArSConstructCryostat.hh"


LArSConstructCryostat::LArSConstructCryostat( LArSDetectorConstruction * constructorClass)
{
  Constructor_class = constructorClass;
}

LArSConstructCryostat::~LArSConstructCryostat() {;}

G4LogicalVolume* LArSConstructCryostat::Construct(){

//**********************************************PARAMETERS*********************************************    
   //Materials
   G4Material *Vacuum = G4Material::GetMaterial("Vacuum");;
   G4Material *Steel = G4Material::GetMaterial("SS304LSteel");;
    
   //General
   G4double General_r_inner[4] = {0.,0.,0.,0.};
   General_r_inner[0] = 0.*m;
   General_r_inner[1] = 0.*m;
   General_r_inner[2] = 0.*m;
   General_r_inner[3] = 0.*m;

   G4double General_phi_start = 0.*deg;
   G4double General_phi_total = 360*deg;
   G4double General_wallthickness = 4*mm;
    
   //Outer cryostat
   G4double Outer_cryostat_z_plane[4] = {0.,0.,0.,0.};
   Outer_cryostat_z_plane[0] = -250*mm;
   Outer_cryostat_z_plane[1] = 226*mm;
   Outer_cryostat_z_plane[2] = 226*mm;
   Outer_cryostat_z_plane[3] = 250*mm;
   
   G4double Outer_cryostat_r_outer[4] = {0.,0.,0.,0.};
   Outer_cryostat_r_outer[0] = 300./2*mm;
   Outer_cryostat_r_outer[1] = 300./2*mm;
   Outer_cryostat_r_outer[2] = 355./2*mm;
   Outer_cryostat_r_outer[3] = 355./2*mm;
   
   //Vacuum
   G4double Vacuum_z_plane[2] = {0.,0.};
   Vacuum_z_plane[0] = -250*mm + General_wallthickness;
   Vacuum_z_plane[1] = 226*mm ;
       
   //G4double Vacuum_r_outer[4] = {0.,0.,0.,0.};
   G4double Vacuum_r_outer[2] = {0.,0.};
   Vacuum_r_outer[0] = Outer_cryostat_r_outer[0] - General_wallthickness;
   Vacuum_r_outer[1] = Outer_cryostat_r_outer[1] - General_wallthickness;
   
   //Inner cryostat
   G4double Inner_cryostat_z_plane[2] = {0.,0.};
   Inner_cryostat_z_plane[0] = -223.5*mm;
   Inner_cryostat_z_plane[1] = 226*mm;
       
   G4double Inner_cryostat_r_outer[2] = {0.,0.};
   Inner_cryostat_r_outer[0] = 129*mm;
   Inner_cryostat_r_outer[1] = 129*mm;
   
  
//***********************************************SOLIDS*************************************************
   G4Polycone *Steel_outer_cryostat = new G4Polycone("Steel_outer_cryostat", General_phi_start, General_phi_total, 4, Outer_cryostat_z_plane, General_r_inner, Outer_cryostat_r_outer);
   
   G4Polycone *Vacuum_volume = new G4Polycone("Vacuum_volume", General_phi_start, General_phi_total, 2, Vacuum_z_plane, General_r_inner, Vacuum_r_outer);
   
   G4Polycone *Steel_inner_cryostat = new G4Polycone("Steel_inner_cryostat", General_phi_start, General_phi_total, 2, Inner_cryostat_z_plane, General_r_inner, Inner_cryostat_r_outer);
   
//********************************************LOGICALVOLUMES*******************************************
   //Logical volumes
   Steel_outer_cryostat_logical = new G4LogicalVolume(Steel_outer_cryostat, Steel, "Steel_outer_cryostat_logical", 0, 0, 0); 
   
   Vacuum_volume_logical = new G4LogicalVolume(Vacuum_volume, Vacuum, "Vacuum_volume_logical", 0, 0, 0); 
   
   Steel_inner_cryostat_logical = new G4LogicalVolume(Steel_inner_cryostat, Steel, "Steel_inner_cryostat_logical", 0, 0, 0); 
   
   
//********************************************PHYSICALVOLUMES******************************************
   //Physical volumes
  Steel_outer_cryostat_physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), Steel_outer_cryostat_logical, "Steel_outer_cryostat_physical", Constructor_class->GetMotherVolumeLogical(), false, 0);

  Vacuum_volume_physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), Vacuum_volume_logical, "Vacuum_volume_physical", Steel_outer_cryostat_logical, false, 0);
  
  Steel_inner_cryostat_physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), Steel_inner_cryostat_logical, "Steel_inner_cryostat_physical", Vacuum_volume_logical, false, 0);
  
 
  return Steel_inner_cryostat_logical;
}

G4LogicalVolume* LArSConstructCryostat::GetMotherVolume(){
    return this->Steel_inner_cryostat_logical;
}
