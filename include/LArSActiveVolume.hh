#ifndef LARSACTIVEVOLUME_H
#define LARSACTIVEVOLUME_H

//LArS header files
#include "LArSDetectorConstruction.hh"

//G4 Header Files
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4Polycone.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>
#include <G4VUserDetectorConstruction.hh>

class G4LogicalVolume;
class G4VPhysicalVolume;
class LArSDetectorConstruction;

class LArSActiveVolume{

public:
    LArSActiveVolume( LArSDetectorConstruction* );
    ~LArSActiveVolume();

    G4LogicalVolume* Construct();

    G4LogicalVolume* GetMotherVolume();
    void PrintGeometryInformation();
    inline G4VPhysicalVolume* GetPhysicalVolume(){return LAr_physical;};

private:

    LArSDetectorConstruction * Constructor_class;
    
    //Logical volumes
    G4LogicalVolume *LAr_logical;
    
    //Physical volumes
    G4VPhysicalVolume *LAr_physical;
    
    
};

#endif
