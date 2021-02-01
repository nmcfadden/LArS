#ifndef __LARSDETECTORCONSTRUCTION_H__
#define __LARSDETECTORCONSTRUCTION_H__

// LARS header files
#include "LArSMaterials.hh"
#include "LArSDetectorMessenger.hh"
#include "LArSOpticalSurfaces.hh"


// Detector components
#include "LArSConstructLab.hh"
#include "LArSConstructCryostat.hh"
#include "LArSActiveVolume.hh"
#include "LArSPMTCell.hh"


//Additional Header Files
#include <globals.hh>
#include <math.h>
#include <vector>
#include <map>
#include <vector>
#include <numeric>
#include <cassert>

//Root Header Files
#include "TFile.h"
#include "TDirectory.h"
//#include <TParameter.h>

//G4 Header Files
#include <G4Material.hh>
#include <G4UnionSolid.hh>
#include <G4SubtractionSolid.hh>
#include <G4UImanager.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Orb.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SDManager.hh>
#include <G4ThreeVector.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4SystemOfUnits.hh>


class LArSDetectorMessenger;
class LArSDetectorConstruction: public G4VUserDetectorConstruction{

public:
    LArSDetectorConstruction(G4String fName);
    ~LArSDetectorConstruction();

    G4VPhysicalVolume* Construct();
    void SetCheckOverlap(G4bool dCheckOverlap){pCheckOverlap = dCheckOverlap;};

    inline void SetAcrylicWindow(G4bool val){pAcrylicWindow = val;};
    inline bool UseAcrylicWindow(){return pAcrylicWindow;};

    inline void SetPEN(G4bool val){pPen = val;};
    inline bool UsePEN(){return pPen;};

    inline void SetTetratex(G4bool val){pTetretex = val;};
    inline bool UseTetratex(){return pTetretex;};

    inline void SetTPB(G4bool val){pTPB = val;};
    inline bool UseTPB(){return pTPB;};


    static G4double GetGeometryParameter(const char *szParameter);
    G4LogicalVolume* GetMotherVolumeLogical(){return Mother_volume;};
    inline void SetMotherVolumeLogical(G4LogicalVolume* vol){Mother_volume = vol;}

    int SetSensitiveVolumes(G4String volName);

    // LOGICAL VOLUMES
    G4LogicalVolume *Mother_volume;

    // PHYSICAL VOLUMES
    G4VPhysicalVolume *World_volume_physical;
    G4VPhysicalVolume *Steel_cryostat_physical;
    G4VPhysicalVolume *LXe_TPC_physical;
    G4VPhysicalVolume *LAr_physical;


private:
    void ConstructLaboratory();	
    void PrintGeometryInformation();
    void SecondOverlapCheck();
    void VolumesHierarchy();

    // PARAMETERS

    static std::map<G4String, G4double> m_hGeometryParameters;
    void DefineGeometryParameters();


    /////////////////////////////////////////////////////////////////////////
    LArSDetectorMessenger *m_pDetectorMessenger;
    G4String    detRootFile;
    G4bool   pCheckOverlap; 
    G4bool pAcrylicWindow = false; 
    G4bool pPen = false;
    G4bool pTetretex = false;
    G4bool pTPB = false;
};

#endif
