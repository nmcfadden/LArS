//XENON Header Files
#include "LArSDetectorMessenger.hh"


LArSDetectorMessenger::LArSDetectorMessenger(LArSDetectorConstruction *pXeDetector)
:m_pXeDetector(pXeDetector)
{
    
    m_pDetectorDir = new G4UIdirectory("/Xe/detector/");
    m_pDetectorDir->SetGuidance("detector control.");

    m_pTeflonReflectivityCmd = new G4UIcmdWithADouble("/Xe/detector/setTeflonReflectivity", this);
    m_pTeflonReflectivityCmd->SetGuidance("Define teflon reflectivity.");
    m_pTeflonReflectivityCmd->SetParameterName("R", false);
    m_pTeflonReflectivityCmd->SetRange("R >= 0. && R <= 1.");
    m_pTeflonReflectivityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pLXeScintillationCmd = new G4UIcmdWithABool("/Xe/detector/setLXeScintillation", this);
    m_pLXeScintillationCmd->SetGuidance("Switch on/off LXe scintillation in the sensitive volume.");
    m_pLXeScintillationCmd->SetParameterName("LXeScint", false); 
    m_pLXeScintillationCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    // DR 20160701 - Activation Gd-LS scintillation
    m_pGdLScintScintillationCmd = new G4UIcmdWithABool("/Xe/detector/setGdLScintScintillation", this);
    m_pGdLScintScintillationCmd->SetGuidance("Switch on/off GdLScint scintillation in the sensitive volume.");
    m_pGdLScintScintillationCmd->SetParameterName("GdLScintScint", false); 
    m_pGdLScintScintillationCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pLXeAbsorbtionLengthCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setLXeAbsorbtionLength", this);
    m_pLXeAbsorbtionLengthCmd->SetGuidance("Define LXe absorbtion length.");
    m_pLXeAbsorbtionLengthCmd->SetParameterName("AbsL", false);
    m_pLXeAbsorbtionLengthCmd->SetRange("AbsL >= 0.");
    m_pLXeAbsorbtionLengthCmd->SetUnitCategory("Length");
    m_pLXeAbsorbtionLengthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pLXeRayScatterLengthCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setLXeRayScatterLength", this);
    m_pLXeRayScatterLengthCmd->SetGuidance("Define LXe Rayleigh Scattering length.");
    m_pLXeRayScatterLengthCmd->SetParameterName("ScatL", false);
    m_pLXeRayScatterLengthCmd->SetRange("ScatL >= 0.");
    m_pLXeRayScatterLengthCmd->SetUnitCategory("Length");
    m_pLXeRayScatterLengthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    // check for overlapping objetcs
    m_pCheckOverlapCmd = new G4UIcmdWithABool("/LArS/detector/setCheckOverlap", this);
    m_pCheckOverlapCmd->SetGuidance("Check for overlapping objects in the geometry.");
    m_pCheckOverlapCmd->SetParameterName("CheckOverlap", false); 
    m_pCheckOverlapCmd->AvailableForStates(G4State_PreInit);
    m_pXeDetector->SetCheckOverlap(false);

    m_pSetAcrylicWindowCmd = new G4UIcmdWithABool("/LArS/detector/setAcrylicWindow",this);
    m_pSetAcrylicWindowCmd->SetGuidance("Set Acrylic Window.");
    m_pSetAcrylicWindowCmd->SetParameterName("AcrylicWindow", false);
    m_pSetAcrylicWindowCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    m_pSetPENCmd  = new G4UIcmdWithABool("/LArS/detector/setPEN",this);
    m_pSetPENCmd->SetGuidance("Set PEN.");
    m_pSetPENCmd->SetParameterName("PEN", false);
    m_pSetPENCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    m_pSetTetratexCmd  = new G4UIcmdWithABool("/LArS/detector/setTetratex",this);
    m_pSetTetratexCmd->SetGuidance("Set Tetratex.");
    m_pSetTetratexCmd->SetParameterName("Tetratex", false);
    m_pSetTetratexCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    m_pSetTPBCmd  = new G4UIcmdWithABool("/LArS/detector/setTPB",this);
    m_pSetTPBCmd->SetGuidance("Set TPB.");
    m_pSetTPBCmd->SetParameterName("TPB", false);
    m_pSetTPBCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

 
//******************************************
// Added by Alex 
//******************************************
        

    m_pLXeMeshMaterialCmd = new G4UIcmdWithAString("/Xe/detector/setLXeMeshMaterial",this);
    m_pLXeMeshMaterialCmd->SetGuidance("Select material of the LXe Meshes.");
    m_pLXeMeshMaterialCmd->SetParameterName("choice",false);
    m_pLXeMeshMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pGXeMeshMaterialCmd = new G4UIcmdWithAString("/Xe/detector/setGXeMeshMaterial",this);
    m_pGXeMeshMaterialCmd->SetGuidance("Select material of the GXe Meshes.");
    m_pGXeMeshMaterialCmd->SetParameterName("choice",false);
    m_pGXeMeshMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    m_pGXeTeflonReflectivityCmd = new G4UIcmdWithADouble("/Xe/detector/setGXeTeflonReflectivity", this);
    m_pGXeTeflonReflectivityCmd->SetGuidance("Define teflon (into the GXe) reflectivity.");
    m_pGXeTeflonReflectivityCmd->SetParameterName("R", false);
    m_pGXeTeflonReflectivityCmd->SetRange("R >= 0. && R <= 1.");
    m_pGXeTeflonReflectivityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  
    m_pGXeAbsorbtionLengthCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setGXeAbsorbtionLength", this);
    m_pGXeAbsorbtionLengthCmd->SetGuidance("Define GXe absorbtion length.");
    m_pGXeAbsorbtionLengthCmd->SetParameterName("GAbsL", false);
    m_pGXeAbsorbtionLengthCmd->SetRange("GAbsL >= 0.");
    m_pGXeAbsorbtionLengthCmd->SetUnitCategory("Length");
    m_pGXeAbsorbtionLengthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pLXeMeshTransparencyCmd = new G4UIcmdWithADouble("/Xe/detector/setLXeMeshTransparency", this);
    m_pLXeMeshTransparencyCmd->SetGuidance("Define LXe mesh transparency.");
    m_pLXeMeshTransparencyCmd->SetParameterName("Transpa", false);
    m_pLXeMeshTransparencyCmd->SetRange("Transpa >= 0. && Transpa <= 1.");
    m_pLXeMeshTransparencyCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pGXeMeshTransparencyCmd = new G4UIcmdWithADouble("/Xe/detector/setGXeMeshTransparency", this);
    m_pGXeMeshTransparencyCmd->SetGuidance("Define GXe mesh transparency.");
    m_pGXeMeshTransparencyCmd->SetParameterName("Transpa", false);
    m_pGXeMeshTransparencyCmd->SetRange("Transpa >= 0. && Transpa <= 1.");
    m_pGXeMeshTransparencyCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    m_pLXeRefractionIndexCmd = new G4UIcmdWithADouble("/Xe/detector/setLXeRefractionIndex", this);
    m_pLXeRefractionIndexCmd->SetGuidance("Define LXe refraction index (MC: 1.63).");
    m_pLXeRefractionIndexCmd->SetParameterName("LXeR", false);
    m_pLXeRefractionIndexCmd->SetRange("LXeR >= 1.56 && LXeR <= 1.69");
    m_pLXeRefractionIndexCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

}

LArSDetectorMessenger::~LArSDetectorMessenger()
{

    delete m_pCheckOverlapCmd;
    delete m_pSetAcrylicWindowCmd;
    delete m_pSetPENCmd;
    delete m_pSetTetratexCmd;
    delete m_pSetTPBCmd;

    // Added by Alex:
    delete m_pLXeMeshMaterialCmd;
    delete m_pGXeMeshMaterialCmd;
    delete m_pTeflonReflectivityCmd;
    delete m_pGXeTeflonReflectivityCmd;
    delete m_pLXeScintillationCmd;
    delete m_pLXeAbsorbtionLengthCmd;
    delete m_pGXeAbsorbtionLengthCmd;
    delete m_pLXeRayScatterLengthCmd;
    delete m_pLXeRefractionIndexCmd;
    delete m_pLXeMeshTransparencyCmd;
    delete m_pGXeMeshTransparencyCmd;
    delete m_pDetectorDir;
}



void LArSDetectorMessenger::SetNewValue(G4UIcommand *pUIcommand, G4String hNewValue)
{
  if(pUIcommand == m_pCheckOverlapCmd){
    m_pXeDetector->SetCheckOverlap(m_pCheckOverlapCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetAcrylicWindowCmd){
    m_pXeDetector->SetAcrylicWindow(m_pSetAcrylicWindowCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetPENCmd){
    m_pXeDetector->SetPEN(m_pSetPENCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetTetratexCmd){
    m_pXeDetector->SetTetratex(m_pSetTetratexCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetTPBCmd){
    m_pXeDetector->SetTPB(m_pSetTPBCmd->GetNewBoolValue(hNewValue));
  }

    // Added by Alex:

    if(pUIcommand == m_pLXeScintillationCmd)
        m_pXeDetector->SetLXeScintillation(m_pLXeScintillationCmd->GetNewBoolValue(hNewValue));

    if(pUIcommand == m_pTeflonReflectivityCmd)
        m_pXeDetector->SetTeflonReflectivity(m_pTeflonReflectivityCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pGXeTeflonReflectivityCmd)
        m_pXeDetector->SetGXeTeflonReflectivity(m_pGXeTeflonReflectivityCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pLXeAbsorbtionLengthCmd)
        m_pXeDetector->SetLXeAbsorbtionLength(m_pLXeAbsorbtionLengthCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pGXeAbsorbtionLengthCmd)
        m_pXeDetector->SetGXeAbsorbtionLength(m_pGXeAbsorbtionLengthCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pLXeRayScatterLengthCmd)
        m_pXeDetector->SetLXeRayScatterLength(m_pLXeRayScatterLengthCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pLXeMeshTransparencyCmd)
        m_pXeDetector->SetLXeMeshTransparency(m_pLXeMeshTransparencyCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pGXeMeshTransparencyCmd)
        m_pXeDetector->SetGXeMeshTransparency(m_pGXeMeshTransparencyCmd->GetNewDoubleValue(hNewValue));

    if(pUIcommand == m_pLXeRefractionIndexCmd)
        m_pXeDetector->SetLXeRefractionIndex(m_pLXeRefractionIndexCmd->GetNewDoubleValue(hNewValue));
}


