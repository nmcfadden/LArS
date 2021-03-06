#ifndef LARSCONSTRUCTLAB_H
#define LARSCONSTRUCTLAB_H

//Xebra header files
#include "LArSDetectorConstruction.hh"

//G4 Header Files
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>
#include <G4VUserDetectorConstruction.hh>

class G4Polycone;
class G4LogicalVolume;
class G4VPhysicalVolume;
class LArSDetectorConstruction;

class LArSConstructLab{

public:
    LArSConstructLab(LArSDetectorConstruction *);
    ~LArSConstructLab();
 
    G4LogicalVolume* Construct();
    
    G4LogicalVolume* GetMotherVolume();
    void PrintGeometryInformation();

private:
    
    LArSDetectorConstruction * Constructor_class;

   //Materials
    G4Material *Vacuum;
    G4Material *Air;
    G4Material *Concrete;

    //Solids
    G4Box *Mother_volume;
    G4Box *Concrete_hall;
    G4Box *Air_volume;
    G4Box *Air_window_1;
    G4Box *Air_window_2;
    
    //Logical volumes
    G4LogicalVolume *Mother_volume_logical;
    G4LogicalVolume *Concrete_hall_logical;
    G4LogicalVolume *Air_volume_logical;
    G4LogicalVolume *Air_window_1_logical;
    G4LogicalVolume *Air_window_2_logical;
    
    //Physical volumes
    G4VPhysicalVolume *Mother_volume_physical;
    G4VPhysicalVolume *Concrete_hall_physical;
    G4VPhysicalVolume *Air_volume_physical;

    
    //Parameters
    G4double concrete_thickness;
    G4double hall_length;
    G4double hall_width;
    G4double hall_height;
    G4double window_height;
    
};

#endif
