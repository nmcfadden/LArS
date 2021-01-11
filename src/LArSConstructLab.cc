#include "LArSConstructLab.hh"

LArSConstructLab::LArSConstructLab(LArSDetectorConstruction * constructorClass)
{
  //Use Constructor class to get Mother_logical_volume with Get() function
  Constructor_class = constructorClass;
}

LArSConstructLab::~LArSConstructLab() {;}

G4LogicalVolume* LArSConstructLab::Construct(){
    
//Lab is a 5x5x5 m^3 box of air with 25 cm thick concrete walls
//**********************************************MATERIALS**********************************************
    Air = G4Material::GetMaterial("Air");
    Concrete = G4Material::GetMaterial("Rock");

//**********************************************PARAMETERS*********************************************    
    //Hall 
    concrete_thickness = 25.*cm;
    hall_length = 5*m;
    hall_width = 5*m;
    hall_height = 5*m;
    
    
//***********************************************SOLIDS*************************************************
    
    Concrete_hall = new G4Box("Concrete_hall", hall_length/2. + concrete_thickness, hall_width/2. + concrete_thickness, hall_height/2 + concrete_thickness);
    
    Air_volume = new G4Box("Air_volume", hall_length/2., hall_width/2., hall_height/2.);
        

//********************************************LOGICAL VOLUMES*******************************************
    Concrete_hall_logical = new G4LogicalVolume(Concrete_hall, Concrete, "Concrete_hall_logical", 0, 0, 0); 
    
    Air_volume_logical = new G4LogicalVolume(Air_volume, Air, "Air_volume_logical", 0, 0, 0); 
    
    
//********************************************PHYSICAL VOLUMES******************************************

    Concrete_hall_physical = new G4PVPlacement(0, G4ThreeVector(0,0,0), Concrete_hall_logical, "Concrete_hall_physical", Constructor_class->GetMotherVolumeLogical(), false, 0);
        
    Air_volume_physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), Air_volume_logical, "Air_volume_physical", Concrete_hall_logical, false, 0);
    
    
    return Air_volume_logical;
}
    
G4LogicalVolume* LArSConstructLab::GetMotherVolume(){
    return this->Air_volume_logical;
}  
