#ifndef LARSPMTCELL_H
#define LARSPMTCELL_H

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

#define PI 3.14159265

class LArSPMTCell{

public:
    LArSPMTCell( LArSDetectorConstruction* );
    ~LArSPMTCell();

    G4LogicalVolume* Construct();

    G4LogicalVolume* GetMotherVolume();
    void PrintGeometryInformation();
    inline G4VPhysicalVolume* GetPhysicalVolume(){return pmtWindow_physical;};
    inline G4VPhysicalVolume* GetTPBVolume() {return TPB_physical;};

private:

    LArSDetectorConstruction * Constructor_class;
    
    //Logical volumes
    G4LogicalVolume *LAr_logical;
    
    //Physical volumes
    G4VPhysicalVolume *LAr_physical;
    G4VPhysicalVolume *pmtWindow_physical;
    G4VPhysicalVolume *acrylicWindow_physical;
    G4VPhysicalVolume *topCell_physical;
    G4VPhysicalVolume *wallCell_Physical;
    G4VPhysicalVolume *supportRod_Physical0;
    G4VPhysicalVolume *supportRod_Physical1;
    G4VPhysicalVolume *supportRod_Physical2;
    G4VPhysicalVolume *bottomCell_physical;
    G4VPhysicalVolume *PEN_physical;
    G4VPhysicalVolume *alphaSource_physical;
    G4VPhysicalVolume *TPB_physical;
    
    
};

#endif
