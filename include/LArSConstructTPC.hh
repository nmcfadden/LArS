#ifndef LARSCONSTRUCTTPC_H
#define LARSCONSTRUCTTPC_H

#include "LArSDetectorConstruction.hh"
#include "LArSPmtSensitiveDetector.hh"
#include "LArSSensitiveDetector.hh"
#include "LArSPmtHit.hh"
#include "LArSLXeHit.hh"
#include "LArSDetectorMessenger.hh"
#include "LArSMaterials.hh"

//G4 Header Files
#include <G4SystemOfUnits.hh>
#include <G4SDManager.hh>
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"

//Optical surface properties
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>


#include "math.h"
#define PI 3.14159265
class LArSDetectorConstruction;
//class LArSPmtSensitiveDetector;

class LArSConstructTPC{

public:
    LArSConstructTPC(LArSDetectorConstruction *p);
    ~LArSConstructTPC();
 
    G4LogicalVolume* Construct();
    void PrintGeometryInformation();

private:

    //Materials
    G4Material *LXe;
    G4Material *GXe;
    G4Material *SS304LSteel;
    G4Material *Copper;
    G4Material *SiPM_material;
    G4Material *Teflon;

    //Solids
    G4Polycone *LXe_volume;
    G4Polycone *GXe_volume; 
    G4SubtractionSolid *GXe_volume_cut = NULL;
    G4Torus *Copper_torus;
    G4Box *Teflon_pillar_box;
    G4SubtractionSolid *Teflon_pillar_box_cut = NULL;
    G4Tubs *Cathode_mesh;
    //G4Box *SiPM_array;
    //G4Tubs *SiPM_cylinder;
    G4Tubs *Teflon_top_array_orig;
    G4Box *Teflon_top_array_sub1_box1;
    G4Box *Teflon_top_array_sub1_box2;
    G4Tubs *Teflon_top_array_sub1_tubs;
    G4Cons *Teflon_top_array_sub1_cone;
    G4Trd *Teflon_top_array_sub1_trapezoid1;
    G4Trd *Teflon_top_array_sub1_trapezoid2;
    G4UnionSolid *Teflon_top_array_sub1_union1;
    G4UnionSolid *Teflon_top_array_sub1_union2;
    G4UnionSolid *Teflon_top_array_sub1_union3;
    G4UnionSolid *Teflon_top_array_sub1_union4;
    G4UnionSolid *Teflon_top_array_sub1_union5;
    G4UnionSolid *Teflon_top_array_sub1_union6;
    G4UnionSolid *Teflon_top_array_sub1_union7;
    G4UnionSolid *Teflon_top_array_sub1_union8;
    G4UnionSolid *Teflon_top_array_sub1_union9;
    G4UnionSolid *Teflon_top_array_sub1_union10;
    G4UnionSolid *Teflon_top_array_sub1;

    
    //Logical Volumes
    G4LogicalVolume *LXe_volume_logical;
    G4LogicalVolume *GXe_volume_logical;
    G4LogicalVolume *Copper_torus_logical;
    G4LogicalVolume *Teflon_pillar_box_logical;
    G4LogicalVolume *Cathode_mesh_logical;
    G4LogicalVolume *Anode_mesh_logical;
    G4LogicalVolume *Copper_fsr_logical;
    //G4LogicalVolume *SiPM_array_logical;
    //G4LogicalVolume *SiPM_array_logical;
    G4LogicalVolume *Teflon_top_array_logical;
    
    //Physical Volumes
    G4VPhysicalVolume *LXe_volume_physical;
    G4VPhysicalVolume *GXe_volume_physical;
    G4VPhysicalVolume *Copper_FSR_physical;  
    G4VPhysicalVolume *Teflon_pillar_physical;
    G4VPhysicalVolume *Cathode_mesh_physical;
    G4VPhysicalVolume *Anode_mesh_physical;
    //G4VPhysicalVolume *SiPM_array_physical;
    G4VPhysicalVolume *Teflon_top_array_physical;
   
    //Parameters
    //Liquid Xenon
    G4double LXe_height;
    G4double General_r_inner[4] = {0.,0.,0.,0.};
    G4double General_phi_start;
    G4double General_phi_total;
    G4double General_num_z_planes;
    G4double LXe_z_plane[4] = {0.,0.,0.,0.};
    G4double LXe_r_outer[4] = {0.,0.,0.,0.};

    //Gaseous Xenon
    G4double GXe_z_plane[4] = {0.,0.,0.,0.};
    G4double GXe_r_outer[4] = {0.,0.,0.,0.};
     
    //Field shaping rings
    G4double Copper_ring_radius;
    G4double Copper_toroidal_radius;
    G4double FSR_number;
    G4double FSR_separation;
    G4double Copper_ring_z_position;
    G4ThreeVector Copper_ring_position;
    
    //Cathode Mesh
    G4double Cathode_mesh_thickness;
    G4double Cathode_mesh_radius; 
    
    //TPC
    G4double TPC_x_offset;
    G4double TPC_y_offset;
    G4double TPC_z_offset;

    
    //Teflon_pillar
    G4double Teflon_pillar_number;
    G4double Teflon_pillar_height;
    G4double Teflon_pillar_width;
    G4double Teflon_pillar_length;
    G4double Teflon_pillar_upper_offset;
    G4double Teflon_pillar_lower_offset;
    G4double Teflon_pillar_placing_radius;
    G4RotationMatrix *Teflon_pillar_rotation = new G4RotationMatrix;
    G4RotationMatrix *Teflon_pillar_rotation_placement = new G4RotationMatrix;
    G4ThreeVector Teflon_pillar_position;


    //SiPM top array - lower teflon holder
    G4double Teflon_top_array_radius;
    G4double Teflon_top_array_baseheight;
    G4double Teflon_top_array_cutout1_width;
    G4double Teflon_top_array_cutout1_chamfer_width;
    G4double Teflon_top_array_cutout1_chamfer_height;
    G4double Teflon_top_array_cutout1_cornerradius_inner;
    G4double Teflon_top_array_cutout1_cornerradius_outer;


/*
    //Parameters SiPM array
    G4int topSiPM_Number;
    G4double topSiPM_Length;
    G4double topSiPM_Thickness;
    G4double Mesh_Zcomponent;
    G4double SiPM6mm_Length;
    G4double SiPM6mm_Thickness;
*/

    //Visualization
    G4VisAttributes *TeflonVisAtt;
    G4VisAttributes *LXeVisAtt;
    G4VisAttributes *GXeVisAtt;
    G4VisAttributes *ElectrodesVisAtt;
    G4VisAttributes *CathodeVisAtt;
    G4VisAttributes *BottomscreenVisAtt;
    G4VisAttributes *RingsVisAtt;
    G4VisAttributes *SensorVisAtt;


};

#endif
