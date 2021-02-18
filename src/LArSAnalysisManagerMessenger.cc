//LArS Header files
#include "LArSAnalysisManagerMessenger.hh"


LArSAnalysisManagerMessenger::LArSAnalysisManagerMessenger(LArSAnalysisManager *pAnalysisManager)
:m_pAnalysisManager(pAnalysisManager)
{
    //declaring the command
    m_pSetFastSimCmd = new G4UIcmdWithABool("/LArS/analysismanager/setFastSim",this);
    m_pSetFastSimCmd->SetGuidance("Set Fast simulation - only pmt hits and NScint in the root file.");
    m_pSetFastSimCmd->SetParameterName("FastSim", false);
    m_pSetFastSimCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


}

LArSAnalysisManagerMessenger::~LArSAnalysisManagerMessenger()
{
    delete m_pSetFastSimCmd;
}



void LArSAnalysisManagerMessenger::SetNewValue(G4UIcommand *pUIcommand, G4String hNewValue)
{
  if(pUIcommand == m_pSetFastSimCmd){
    m_pAnalysisManager->SetFastSim(m_pSetFastSimCmd->GetNewBoolValue(hNewValue));// get boolean value passed to the command in the preinit macro and then pass this to the function SetFastSim which is defined for LArSAnalysisManager objects
  }

}


