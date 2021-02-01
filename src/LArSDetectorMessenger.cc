//XENON Header Files
#include "LArSDetectorMessenger.hh"


LArSDetectorMessenger::LArSDetectorMessenger(LArSDetectorConstruction *pLArSDetector)
:m_pLArSDetector(pLArSDetector)
{
    // check for overlapping objetcs
    m_pCheckOverlapCmd = new G4UIcmdWithABool("/LArS/detector/setCheckOverlap", this);
    m_pCheckOverlapCmd->SetGuidance("Check for overlapping objects in the geometry.");
    m_pCheckOverlapCmd->SetParameterName("CheckOverlap", false); 
    m_pCheckOverlapCmd->AvailableForStates(G4State_PreInit);
    m_pLArSDetector->SetCheckOverlap(false);

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


}

LArSDetectorMessenger::~LArSDetectorMessenger()
{
    delete m_pCheckOverlapCmd;
    delete m_pSetAcrylicWindowCmd;
    delete m_pSetPENCmd;
    delete m_pSetTetratexCmd;
    delete m_pSetTPBCmd;
}



void LArSDetectorMessenger::SetNewValue(G4UIcommand *pUIcommand, G4String hNewValue)
{
  if(pUIcommand == m_pCheckOverlapCmd){
    m_pLArSDetector->SetCheckOverlap(m_pCheckOverlapCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetAcrylicWindowCmd){
    m_pLArSDetector->SetAcrylicWindow(m_pSetAcrylicWindowCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetPENCmd){
    m_pLArSDetector->SetPEN(m_pSetPENCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetTetratexCmd){
    m_pLArSDetector->SetTetratex(m_pSetTetratexCmd->GetNewBoolValue(hNewValue));
  }
  else if(pUIcommand == m_pSetTPBCmd){
    m_pLArSDetector->SetTPB(m_pSetTPBCmd->GetNewBoolValue(hNewValue));
  }

}


