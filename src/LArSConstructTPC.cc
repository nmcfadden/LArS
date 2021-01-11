#include "LArSConstructTPC.hh"


LArSConstructTPC::LArSConstructTPC(LArSDetectorConstruction *){}

LArSConstructTPC::~LArSConstructTPC() {;}

G4LogicalVolume* LArSConstructTPC::Construct(){
    using std::stringstream;
    stringstream Teflon_pillar_name;
    stringstream FSR_name;

//**********************************************MATERIALS**********************************************
    LXe = G4Material::GetMaterial("LXe");
    GXe = G4Material::GetMaterial("GXe");
    Copper = G4Material::GetMaterial("Copper");
    SS304LSteel = G4Material::GetMaterial("SS304LSteel");
    SiPM_material = G4Material::GetMaterial("SiPM_material");
    Teflon = G4Material::GetMaterial("Teflon");
    
//**********************************************PARAMETERS*********************************************    
    //General
    General_r_inner[0] = 0.*m;
    General_r_inner[1] = 0.*m;
    General_r_inner[2] = 0.*m;
    General_r_inner[3] = 0.*m;
    General_phi_start = 0.*deg;
    General_phi_total = 360*deg;
    General_num_z_planes = 4;
    
    //Parameters TPC
    TPC_x_offset = -0.05*mm;
    TPC_y_offset = -24.09*mm;
    TPC_z_offset = 159.57*mm;
    
    //Liquid Xenon  
    LXe_z_plane[0] = 0*mm;
    LXe_z_plane[1] = 2765.87*mm;
    LXe_z_plane[2] = 3095.87*mm;
    LXe_z_plane[3] = 3109.77*mm;
         
    LXe_r_outer[0] = 124*mm;
    LXe_r_outer[1] = 124*mm;
    LXe_r_outer[2] = 173.3*mm;
    LXe_r_outer[3] = 173.3*mm;
    
    //Gaseous Xenon
    //GXe_z_plane[0] = LXe_height+TPC_z_offset;
    GXe_z_plane[0] = 2793.94*mm;
    GXe_z_plane[1] = 3095.87*mm;
    GXe_z_plane[2] = 3010.87*mm;
    GXe_z_plane[3] = 3109.77*mm;
       
    //GXe_r_outer[0] = GXe_r_outer[0] + (GXe_z_plane[0]-LXe_z_plane[1])*49.3/330*mm;
    GXe_r_outer[0] = ((2793.94-2765.87)*49.3/330+124)*mm;
    GXe_r_outer[1] = 173.3*mm;
    GXe_r_outer[2] = 173.3*mm;
    GXe_r_outer[3] = 173.3*mm;

    //Parameters PTFE pillars
    Teflon_pillar_height = 2753.12*mm;
    Teflon_pillar_width  = 16.81*mm;
    Teflon_pillar_length = 10.*mm;
    Teflon_pillar_upper_offset = 136.51*mm;
    Teflon_pillar_lower_offset = 36.62*mm;
    Teflon_pillar_placing_radius = 80*mm;
    Teflon_pillar_number = 6.;
    
    //Field shaping rings
    Copper_toroidal_radius = 3.2*mm;
    Copper_ring_radius = 77.5*mm;
    FSR_number = 172.;
    FSR_separation = (Teflon_pillar_height-Teflon_pillar_upper_offset-Teflon_pillar_lower_offset)/(FSR_number-1);

    //SiPM top array - lower teflon holder
    Teflon_top_array_radius = 80.0*mm;
    Teflon_top_array_baseheight = 3.0*mm;
    Teflon_top_array_cutout1_width = 13.7*mm;
    Teflon_top_array_cutout1_chamfer_width = 1.0*mm;
    Teflon_top_array_cutout1_chamfer_height = 1.0*mm;
    Teflon_top_array_cutout1_cornerradius_inner = 1.0*mm;
    Teflon_top_array_cutout1_cornerradius_outer = Teflon_top_array_cutout1_cornerradius_inner + Teflon_top_array_cutout1_chamfer_width;

   
/*
    //Cathode Mesh
    Cathode_mesh_thickness = 2*mm;

    //Parameters SiPM-Top. One topSiPM cell consists of 16 6x6 mm SiPMs
    topSiPM_Number = 26;
    topSiPM_Length = 24.6*mm;
    topSiPM_Thickness = 1.*mm;
*/
//***********************************************SOLIDS*************************************************

    LXe_volume = new G4Polycone("LXe_volume", General_phi_start, General_phi_total, General_num_z_planes, LXe_z_plane, General_r_inner, LXe_r_outer);
    
    GXe_volume = new G4Polycone("GXe_volume", General_phi_start, General_phi_total, General_num_z_planes, GXe_z_plane, General_r_inner, GXe_r_outer);

    Copper_torus = new G4Torus("Copper_torus",0.,Copper_toroidal_radius, Copper_ring_radius, General_phi_start, General_phi_total);
    
    Teflon_pillar_box = new G4Box("Teflon_pillar_box", Teflon_pillar_length/2., Teflon_pillar_width/2., Teflon_pillar_height/2.);
    
   
    // Cutting out copper rings from Teflon_pillars. 
    for(int a=0; a < FSR_number; ++a){
        Copper_ring_z_position = Teflon_pillar_height/2 - Teflon_pillar_upper_offset - a*FSR_separation;
        Copper_ring_position = G4ThreeVector(Teflon_pillar_placing_radius, 0. , Copper_ring_z_position);
        
        if(!Teflon_pillar_box_cut){
            Teflon_pillar_box_cut = new G4SubtractionSolid("Teflon_pillar_box-Copper_torus", Teflon_pillar_box, Copper_torus,0, Copper_ring_position);
        }
        else{
            Teflon_pillar_box_cut = new G4SubtractionSolid("Teflon_pillar_box_cut-Copper_torus", Teflon_pillar_box_cut, Copper_torus,0, Copper_ring_position); 
        }
    }
    
    
    //Cutting out Copper rings and Teflon_pillars from GXe. 
    for(int a=0; a < FSR_number; ++a){
        Copper_ring_z_position = Teflon_pillar_height/2 + TPC_z_offset - Teflon_pillar_upper_offset - a*FSR_separation;
        if((Copper_ring_z_position + Copper_toroidal_radius) < GXe_z_plane[0]){
            break;
        }
       
        Copper_ring_position = G4ThreeVector(TPC_x_offset, TPC_y_offset , Copper_ring_z_position);
        if(!GXe_volume_cut){
            GXe_volume_cut = new G4SubtractionSolid("GXe_volume-Copper_torus", GXe_volume, Copper_torus,0, Copper_ring_position); 
        }
        else{
            GXe_volume_cut = new G4SubtractionSolid("GXe_volume_cut-Copper_torus", GXe_volume_cut, Copper_torus,0, Copper_ring_position); 
        }   
    }
    
    
    for(int b=0; b < Teflon_pillar_number; b++){
        G4RotationMatrix *Rotation_matrix = new G4RotationMatrix;
        Rotation_matrix->rotateZ(-2*PI/Teflon_pillar_number*(double)b*rad);
        Rotation_matrix->invert();
        Teflon_pillar_position = G4ThreeVector(TPC_x_offset-Teflon_pillar_placing_radius*cos(b*2*PI/Teflon_pillar_number),TPC_y_offset-Teflon_pillar_placing_radius*sin(b*2*PI/Teflon_pillar_number),Teflon_pillar_height/2 + TPC_z_offset);
        if(!GXe_volume_cut){
            GXe_volume_cut = new G4SubtractionSolid("GXe_volume-Teflon_pillar_box", GXe_volume, Teflon_pillar_box, G4Transform3D(*Rotation_matrix, Teflon_pillar_position));
        }
        else{
            GXe_volume_cut = new G4SubtractionSolid("GXe_volume_cut-Teflon_pillar_box", GXe_volume_cut, Teflon_pillar_box, G4Transform3D(*Rotation_matrix, Teflon_pillar_position));
        }

    }
        
    
    //SiPM top array: lower teflon holder
    Teflon_top_array_orig = new G4Tubs("Teflon_top_array_orig", 0.0*mm, Teflon_top_array_radius, Teflon_top_array_baseheight / 2, 0.*deg, 360.*deg);

    Teflon_top_array_sub1_box1 = new G4Box("Teflon_top_array_sub1_box1", Teflon_top_array_cutout1_width/2., Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_baseheight/2.);
    Teflon_top_array_sub1_box2 = new G4Box("Teflon_top_array_sub1_box2", Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_cutout1_width/2., Teflon_top_array_baseheight/2.);
    Teflon_top_array_sub1_tubs = new G4Tubs("Teflon_top_array_sub1_tubs", 0.0*mm, Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_baseheight / 2, 0.*deg, 360.*deg);
    Teflon_top_array_sub1_cone = new G4Cons("Teflon_top_array_sub1_cone", 0.0*mm, Teflon_top_array_cutout1_cornerradius_outer, 0.0*mm, Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_cutout1_chamfer_height / 2, 0.*deg, 360.*deg);
    Teflon_top_array_sub1_trapezoid1 = new G4Trd("Teflon_top_array_sub1_trapezoid1", Teflon_top_array_cutout1_width/2. + Teflon_top_array_cutout1_chamfer_width, Teflon_top_array_cutout1_width/2., Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_cutout1_chamfer_height/2.);
    Teflon_top_array_sub1_trapezoid2 = new G4Trd("Teflon_top_array_sub1_trapezoid2", Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner, Teflon_top_array_cutout1_width/2. + Teflon_top_array_cutout1_chamfer_width, Teflon_top_array_cutout1_width/2., Teflon_top_array_cutout1_chamfer_height/2.);

    Teflon_top_array_sub1_union1 = new G4UnionSolid("Teflon_top_array_sub1_union1", Teflon_top_array_sub1_box1, Teflon_top_array_sub1_box2, 0, G4ThreeVector(0.*mm, 0.*mm, 0.*mm));
    Teflon_top_array_sub1_union2 = new G4UnionSolid("Teflon_top_array_sub1_union2", Teflon_top_array_sub1_union1, Teflon_top_array_sub1_trapezoid1, 0, G4ThreeVector(0.*mm, 0.*mm, Teflon_top_array_cutout1_chamfer_height/2. - Teflon_top_array_baseheight/2.));
    Teflon_top_array_sub1_union3 = new G4UnionSolid("Teflon_top_array_sub1_union3", Teflon_top_array_sub1_union2, Teflon_top_array_sub1_trapezoid2, 0, G4ThreeVector(0.*mm, 0.*mm, Teflon_top_array_cutout1_chamfer_height/2. - Teflon_top_array_baseheight/2.));

    Teflon_top_array_sub1_union4 = new G4UnionSolid("Teflon_top_array_sub1_union4", Teflon_top_array_sub1_union3, Teflon_top_array_sub1_tubs, 0, G4ThreeVector((Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), 0.*mm));
    Teflon_top_array_sub1_union5 = new G4UnionSolid("Teflon_top_array_sub1_union5", Teflon_top_array_sub1_union4, Teflon_top_array_sub1_tubs, 0, G4ThreeVector(-(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), 0.*mm));
    Teflon_top_array_sub1_union6 = new G4UnionSolid("Teflon_top_array_sub1_union6", Teflon_top_array_sub1_union5, Teflon_top_array_sub1_tubs, 0, G4ThreeVector((Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), -(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), 0.*mm));
    Teflon_top_array_sub1_union7 = new G4UnionSolid("Teflon_top_array_sub1_union7", Teflon_top_array_sub1_union6, Teflon_top_array_sub1_tubs, 0, G4ThreeVector(-(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), -(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), 0.*mm));

    Teflon_top_array_sub1_union8 = new G4UnionSolid("Teflon_top_array_sub1_union8", Teflon_top_array_sub1_union7, Teflon_top_array_sub1_cone, 0, G4ThreeVector((Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_chamfer_height/2. - Teflon_top_array_baseheight/2.)));
    Teflon_top_array_sub1_union9 = new G4UnionSolid("Teflon_top_array_sub1_union9", Teflon_top_array_sub1_union8, Teflon_top_array_sub1_cone, 0, G4ThreeVector(-(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_chamfer_height/2. - Teflon_top_array_baseheight/2.)));
    Teflon_top_array_sub1_union10 = new G4UnionSolid("Teflon_top_array_sub1_union10", Teflon_top_array_sub1_union9, Teflon_top_array_sub1_cone, 0, G4ThreeVector((Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), -(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_chamfer_height/2. - Teflon_top_array_baseheight/2.)));
    Teflon_top_array_sub1 = new G4UnionSolid("Teflon_top_array_sub1", Teflon_top_array_sub1_union10, Teflon_top_array_sub1_cone, 0, G4ThreeVector(-(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), -(Teflon_top_array_cutout1_width/2. - Teflon_top_array_cutout1_cornerradius_inner), (Teflon_top_array_cutout1_chamfer_height/2. - Teflon_top_array_baseheight/2.)));


/*
     
    
    Cathode_mesh_cylinder = new G4Tubs("Cathode_Mesh_Cylinder", 0.,PTFE_innerRadius, CathodeMesh_Thickness/2.,0.*deg, 360.*deg);
    
    SiPM_array_box = new G4Box("topSiPM_Box",topSiPM_Length/2.,topSiPM_Length/2.,topSiPM_Thickness/2.);

*/
 //**************************************************LOGICALVOLUMES*****************************************************

    LXe_volume_logical = new G4LogicalVolume(LXe_volume, LXe, "LXe_volume_logical", 0, 0, 0); 
    
    GXe_volume_logical = new G4LogicalVolume(GXe_volume_cut, GXe, "GXe_volume_logical", 0, 0, 0);  
    
    Copper_torus_logical = new G4LogicalVolume(Copper_torus, Copper, "Copper_torus_logical", 0, 0, 0);
    
    Teflon_pillar_box_logical = new G4LogicalVolume(Teflon_pillar_box_cut, Teflon, "Teflon_pillar_box_logical", 0, 0, 0);

    Teflon_top_array_logical = new G4LogicalVolume(Teflon_top_array_sub1, Teflon, "Teflon_top_array_logical", 0, 0, 0);

/*    
    CathodeMesh_Logical = new G4LogicalVolume(CathodeMesh_Cylinder,LXe, "CathodeMesh_Logical", 0, 0, 0);
    topSiPM_Logical = new G4LogicalVolume(topSiPM_Box,SiPM_material, "topSiPM_Logical", 0, 0, 0);
*/   
    
//***********************************************PHYSICALVOLUME*******************************************************
    GXe_volume_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), GXe_volume_logical,"GXe_volume_physical", LXe_volume_logical, false, 0);
    
    
    //Placing Copper field shaping rings. 
    for(int a=0; a < FSR_number; ++a){
        Copper_ring_z_position = Teflon_pillar_lower_offset + TPC_z_offset + a*FSR_separation;
        FSR_name.str("");
        FSR_name << "Copper_FSR_" << a;
        Copper_FSR_physical = new G4PVPlacement(0, G4ThreeVector(TPC_x_offset,TPC_y_offset,Copper_ring_z_position), Copper_torus_logical, FSR_name.str(), LXe_volume_logical, false, 0);
        }
     
    
    

    //Placing Teflon_pillars
    for(int b=0; b < Teflon_pillar_number; b++){
        G4RotationMatrix *Rotation_matrix = new G4RotationMatrix;
        Rotation_matrix->rotateZ(-2*PI/Teflon_pillar_number*(double)b*rad);
        Rotation_matrix->invert();
        Teflon_pillar_position = G4ThreeVector(TPC_x_offset-Teflon_pillar_placing_radius*cos(b*2*PI/Teflon_pillar_number),TPC_y_offset-Teflon_pillar_placing_radius*sin(b*2*PI/Teflon_pillar_number),Teflon_pillar_height/2 + TPC_z_offset);
        Teflon_pillar_name.str("");
        Teflon_pillar_name << "Teflon_pillar_physical_" << b;
        Teflon_pillar_physical = new G4PVPlacement(G4Transform3D(*Rotation_matrix, Teflon_pillar_position), Teflon_pillar_box_logical,Teflon_pillar_name.str(),LXe_volume_logical,false,0);
    }
    
    
    //Placing top array
    //Teflon_top_array_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,(GXe_z_plane[3] - Teflon_top_array_baseheight)), Teflon_top_array_logical,"Teflon_top_array_physical", GXe_volume_logical, false, 0);

  /*  

     //Placing SiPMs
    G4int iSiPMNb = 0;
    G4double topSiPMz = -7.55*cm;
    G4double topSiPMy = 12.3*mm;
    for(G4int f =0; f< 6; f++){
        ++iSiPMNb;
        name1.str("");
        name1 << "topSiPM_Physical_" << iSiPMNb;
        G4double topSiPMx = (-61.5 + 24.6*(double)f)*mm ;
        topSiPM1_Physical = new G4PVPlacement(0,G4ThreeVector(topSiPMx,topSiPMy,topSiPMz), topSiPM_Logical,name1.str(),GXe_Logical,false,iSiPMNb,true);
        ++iSiPMNb;
        name1.str("");
        name1 << "topSiPM_Physical_" << iSiPMNb;
        topSiPM1_Physical = new G4PVPlacement(0,G4ThreeVector(topSiPMx,-topSiPMy,topSiPMz), topSiPM_Logical,name1.str(),GXe_Logical,false,iSiPMNb,true);
    }

    topSiPMy = 36.9*mm;
    for(G4int f =0; f< 5; f++){
        ++iSiPMNb;
        name1.str("");
        name1 << "topSiPM_Physical_" << iSiPMNb;
        G4double topSiPMx = (-49.2 + 24.6*(double)f)*mm ;
        topSiPM1_Physical = new G4PVPlacement(0,G4ThreeVector(topSiPMx,topSiPMy,topSiPMz), topSiPM_Logical,name1.str(),GXe_Logical,false,iSiPMNb,true);
        ++iSiPMNb;
        name1.str("");
        name1 << "topSiPM_Physical_" << iSiPMNb;
        topSiPM1_Physical = new G4PVPlacement(0,G4ThreeVector(topSiPMx,-topSiPMy,topSiPMz), topSiPM_Logical,name1.str(),GXe_Logical,false,iSiPMNb,true);
    }

    topSiPMy = 49.2*mm;
    for(G4int f =0; f< 2; f++){
        iSiPMNb++;
        name1.str("");
        name1 << "topSiPM_Physical_" << iSiPMNb;
        G4double topSiPMx = (-12.3 + 24.6*(double)f)*mm ;
        topSiPM1_Physical = new G4PVPlacement(0,G4ThreeVector(topSiPMx,topSiPMy,topSiPMz), topSiPM_Logical,name1.str(),GXe_Logical,false,iSiPMNb,true);
        iSiPMNb++;
        name1.str("");
        name1 << "topSiPM_Physical_" << iSiPMNb;
        topSiPM1_Physical = new G4PVPlacement(0,G4ThreeVector(topSiPMx,-topSiPMy,topSiPMz), topSiPM_Logical,name1.str(),GXe_Logical,false,iSiPMNb,true);
    }
*/
    
    
    //*****************************************Defining sensitivity*****************************************
    G4SDManager *pSDManager = G4SDManager::GetSDMpointer(); 
    LArSSensitiveDetector *pLXeSD = new LArSSensitiveDetector("LArSSD");
    pSDManager->AddNewDetector(pLXeSD); 
    LXe_volume_logical->SetSensitiveDetector(pLXeSD);
    

    //*********************************Print Masses*********************************************
/*    
    const G4double dSiPMMass = 26* topSiPM_Logical->GetMass(false, false)/kg;
    const G4double dSiPMVolume = dSiPMMass/(SiPM_material->GetDensity()*m3/kg);
    G4cout << "SiPM (for 26 units): " << dSiPMMass << " kg " << "    =============    "  << dSiPMVolume << " m3 " << G4endl;
    
    const G4double dLXeMass =  LXe_Logical->GetMass(false, false)/kg;
    const G4double dLXeVolume = dLXeMass/(LXe->GetDensity()*m3/kg);
    G4cout << "LXe: " << dLXeMass << " kg " << "    =============    "  << dLXeVolume << " m3 " << G4endl;

    const G4double dconcreteMass = 2* Concretehall_Logical->GetMass(false, false)/kg;
    const G4double dconcreteVolume = dconcreteMass/(Concrete->GetDensity()*m3/kg);
    G4cout << "concrete hall: " << dconcreteMass << " kg " << "    =============    "  << dconcreteVolume << " m3 " << G4endl;

    const G4double dcopperMass = 140* Copper_Logical->GetMass(false, false)/kg;
    const G4double dcopperVolume = dcopperMass/(Copper->GetDensity()*m3/kg);
    G4cout << "Copper(for 140 rings): " << dcopperMass << " kg " << "    =============    "  << dcopperVolume << " m3 " << G4endl;

    const G4double dsteeloMass =  Steel_Enclosure_Logical->GetMass(false, false)/kg;
    const G4double dsteeloVolume = dsteeloMass/(SS304LSteel->GetDensity()*m3/kg);
    const G4double dsteeliMass =  Steel_TPC_Logical->GetMass(false, false)/kg;
    const G4double dsteeliVolume = dsteeliMass/(SS304LSteel->GetDensity()*m3/kg);
    G4cout << "outer cryostat + inner cryostat" << dsteeloMass+dsteeliMass << " kg " << "    =============    "  << dsteeloVolume+dsteeliVolume << " m3 " << G4endl;
*/

    return LXe_volume_logical;
}



