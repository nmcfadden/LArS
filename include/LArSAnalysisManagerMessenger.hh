#ifndef __LARSANALYSISMANAGERMESSENGER_H__  
#define __LARSANALYSISMANAGERMESSENGER_H__

#include "LArSAnalysisManager.hh"


//Additional Header Files
#include <globals.hh>

//Additional Header Files
#include <fstream>
#include <iomanip>

//G4 Header Files
#include <G4UImessenger.hh>
#include <G4UnitsTable.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4ParticleTable.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithABool.hh>
#include <G4Tokenizer.hh>
#include <G4ios.hh>
#include <G4SystemOfUnits.hh>

//LARS Classes
class LArSAnalysisManager;

//G4 Classes
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class LArSAnalysisManagerMessenger: public G4UImessenger
{
  public:
    LArSAnalysisManagerMessenger(LArSAnalysisManager *pAnalysisManager);
    ~LArSAnalysisManagerMessenger();

    void SetNewValue(G4UIcommand *pUIcommand, G4String hString);

  private:
    LArSAnalysisManager *m_pAnalysisManager;

    G4UIdirectory *m_pAnalysisManagerDir;

    //Commands for LArS 
    G4UIcmdWithABool *m_pSetFastSimCmd;
};

#endif
