#ifndef LARSDetectorMessenger_h
#define LARSDetectorMessenger_h 1

#include "LArSDetectorConstruction.hh"


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
class LArSDetectorConstruction;

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

class LArSDetectorMessenger: public G4UImessenger
{
  public:
    LArSDetectorMessenger(LArSDetectorConstruction *pLArSDetector);
    ~LArSDetectorMessenger();

    void     SetNewValue(G4UIcommand *pUIcommand, G4String hString);

  private:
    LArSDetectorConstruction *m_pLArSDetector;

    G4UIdirectory *m_pDetectorDir;

    // do we want tot check for overlapping objects?
    G4UIcmdWithABool          *m_pCheckOverlapCmd;

    //Commands for LArS
    G4UIcmdWithABool *m_pSetAcrylicWindowCmd;
    G4UIcmdWithABool *m_pSetPENCmd;
    G4UIcmdWithABool *m_pSetTetratexCmd;
    G4UIcmdWithABool *m_pSetTPBCmd;
};

#endif
