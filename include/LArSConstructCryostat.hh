#ifndef LARSCONSTRUCTCRYOSTAT_H
#define LARSCONSTRUCTCRYOSTAT_H

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

class G4Polycone;
class G4LogicalVolume;
class G4VPhysicalVolume;
class LArSDetectorConstruction;

class LArSConstructCryostat{

public:
    LArSConstructCryostat( LArSDetectorConstruction* );
    ~LArSConstructCryostat();

    G4LogicalVolume* Construct();

    G4LogicalVolume* GetMotherVolume();
    void PrintGeometryInformation();

private:

    LArSDetectorConstruction * Constructor_class;
    
    //Logical volumes
    G4LogicalVolume *Steel_outer_cryostat_logical;
    G4LogicalVolume *Vacuum_volume_logical;
    G4LogicalVolume *Steel_inner_cryostat_logical;
    
    //Physical volumes
    G4VPhysicalVolume *Steel_outer_cryostat_physical;
    G4VPhysicalVolume *Vacuum_volume_physical;
    G4VPhysicalVolume *Steel_inner_cryostat_physical;
    
    
};

#endif
