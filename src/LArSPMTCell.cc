#include "LArSPMTCell.hh"


LArSPMTCell::LArSPMTCell( LArSDetectorConstruction * constructorClass)
{
  Constructor_class = constructorClass;
}

LArSPMTCell::~LArSPMTCell() {;}

G4LogicalVolume* LArSPMTCell::Construct(){

  //LAr volume extends in Z from -219.5*mm to 226*mm
  LAr_logical = Constructor_class->GetMotherVolumeLogical();
  

  //PMT window is 0.1 mm thick
  G4double pmtWindowDiameter = 64*mm;
  G4double pmtWindowThickness = 0.1*mm;//This is just a guess
  G4Tubs* pmtWindow_solid = new G4Tubs("pmtWindow_solid",0,pmtWindowDiameter/2.,pmtWindowThickness/2,0,360*deg);
  G4LogicalVolume * pmtWindow_logical = new G4LogicalVolume(pmtWindow_solid,G4Material::GetMaterial("MgF2"),"pmtWindow_Logical",0,0,0);
  pmtWindow_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(-219.5+148+pmtWindowThickness/(2*mm))*mm ),pmtWindow_logical,"pmtWindow_physical",LAr_logical,0,false,0);

  /*
  G4SDManager *SDManager = G4SDManager::GetSDMpointer(); 
  LArSPmtSensitiveDetector *PMTSD = new LArSPmtSensitiveDetector("PmtHitsCollection");
  SDManager->AddNewDetector(PMTSD); 
  pmtWindow_logical->SetSensitiveDetector(PMTSD);
  */
  //Acrylic window, when not used, its material is set to LAr
  G4double acrylicWindowThickness = 5.0*mm;
  G4double delta = 1*um;//used for small gaps between materials. Gap is filled with LAr
  G4Tubs* acrylicWindow_solid = new G4Tubs("acrylicWindow_solid",0,pmtWindowDiameter/2.,acrylicWindowThickness/2,0,360*deg);
  G4LogicalVolume * acrylicWindow_logical;
  //TODO need to add a messenger command that changes the window,
  //when the window is not being used, we make the material out of LAr
  //acrylicWindow_logical = new G4LogicalVolume(acrylicWindow_solid,G4Material::GetMaterial("Acrylic"),"acrylicWindow_Logical",0,0,0);
  acrylicWindow_logical = new G4LogicalVolume(acrylicWindow_solid,G4Material::GetMaterial("Argon-Liq"),"acrylicWindow_Logical",0,0,0);
  acrylicWindow_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(-219.5+148-acrylicWindowThickness/(2*mm)-delta/mm)*mm ),acrylicWindow_logical,"acrylicWindow_physical",LAr_logical,0,false,0);

  G4double topCellOuterDiameter = 106*mm;
  G4double topCellThickness = 14*mm;
  //Top disk is 14 mm thick with a 64 mm hole for the pmt
  G4Tubs* topCell_solid = new G4Tubs("topCell_solid",pmtWindowDiameter/2.,topCellOuterDiameter/2,topCellThickness/2,0,360*deg);
  G4LogicalVolume * topCell_logical = new G4LogicalVolume(topCell_solid,G4Material::GetMaterial("Aluminum"),"topCell_Logical",0,0,0);
  topCell_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(-219.5+148-topCellThickness/(2*mm))*mm ),topCell_logical,"topCell_physical",LAr_logical,0,false,0);

  G4double wallCellThickness = 1*mm;
  G4double wallCellOuterDiameter = topCellOuterDiameter + 2*wallCellThickness;
  G4double wallCellHeight = 100*mm ;
  G4Tubs* wallCell_solid = new G4Tubs("wallCell_solid",topCellOuterDiameter/2,wallCellOuterDiameter/2.,wallCellHeight/2. + topCellThickness,0,360*deg);
  //Optical properties are added else where, the material of the cell wall does not effect the optical properties
  G4LogicalVolume * wallCell_logical = new G4LogicalVolume(wallCell_solid,G4Material::GetMaterial("Delrin"),"wallCell_logical",0,0,0);
  wallCell_Physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(-219.5+148-topCellThickness/(mm)-wallCellHeight/(2*mm))*mm ),wallCell_logical,"wallCell_physical",LAr_logical,0,false,0);

  G4Tubs* supportRod_solid = new G4Tubs("supportRod_solid",0,6./2*mm,100/2*mm,0,360*deg);
  G4LogicalVolume * supportRod_logical = new G4LogicalVolume(supportRod_solid,G4Material::GetMaterial("Aluminum"),"supportRodLogical",0,0,0);
  G4double rodPlacementRadius = 100./2*mm;
  supportRod_Physical0 = new G4PVPlacement(0,G4ThreeVector(rodPlacementRadius  ,0.     ,(-219.5+148-topCellThickness/(mm)-wallCellHeight/(2*mm))*mm ),supportRod_logical,"supportRod_physical0",LAr_logical,0,false,0);
  supportRod_Physical1 = new G4PVPlacement(0,G4ThreeVector(-rodPlacementRadius*cos(60*PI/180.0),rodPlacementRadius*sin(60*PI/180.0),(-219.5+148-topCellThickness/(mm)-wallCellHeight/(2*mm))*mm ),supportRod_logical,"supportRod_physical1",LAr_logical,0,false,0);
  supportRod_Physical2 = new G4PVPlacement(0,G4ThreeVector(-rodPlacementRadius*cos(60*PI/180.0),-rodPlacementRadius*sin(60*PI/180.0),(-219.5+148-topCellThickness/(mm)-wallCellHeight/(2*mm))*mm ),supportRod_logical,"supportRod_physical2",LAr_logical,0,false,0);

   
  //TODO No alpha source added as a material, will assume it is black
  G4Tubs* bottomCell_solid = new G4Tubs("bottomCell_solid",0,topCellOuterDiameter/2,topCellThickness/2,0,360*deg);
  G4LogicalVolume * bottomCell_logical = new G4LogicalVolume(bottomCell_solid,G4Material::GetMaterial("Aluminum"),"bottomCell_Logical",0,0,0);
  bottomCell_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(-219.5+148-topCellThickness/(mm)-wallCellHeight/(mm)-topCellThickness/(2*mm))*mm ),bottomCell_logical,"bottomCell_physical",LAr_logical,0,false,0);

  //Alpha source used to in particle generator macro to confine alpha to small volume
  G4double alphaDiameter = 1*mm;
  G4double alphaThickness = 0.001*mm;
  G4Tubs* alphaSource_solid = new G4Tubs("alphaSource_solid",0,alphaDiameter/2,alphaThickness/2,0,360*deg);
  G4LogicalVolume * alphaSource_logical = new G4LogicalVolume(alphaSource_solid,G4Material::GetMaterial("Aluminum"),"alphaSource_Logical",0,0,0);
  alphaSource_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(-219.5+148-topCellThickness/(mm)-wallCellHeight/(mm)+alphaThickness/(2*mm))*mm ),alphaSource_logical,"alphaSource_physical",LAr_logical,0,false,0);

  return LAr_logical;
}
    

G4LogicalVolume* LArSPMTCell::GetMotherVolume(){
  return this->LAr_logical;
}
