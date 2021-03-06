#ifndef __LARSRUNACTIONMESSENGER_H__
#define __LARSRUNACTIONMESSENGER_H__

#include <G4UImessenger.hh>
#include <globals.hh>

class LArSRunAction;

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

class LArSRunActionMessenger: public G4UImessenger
{
public:
  LArSRunActionMessenger(LArSRunAction *pRunAction);
  ~LArSRunActionMessenger();
  
  void SetNewValue(G4UIcommand *pCommand, G4String hNewValues);
private:
  LArSRunAction           *m_pRunAction;
  G4UIdirectory              *m_pDirectory;
  G4UIcmdWithAnInteger       *m_pRanSeedCmd;
//  G4UIcmdWithABool           *m_pForcedTransportCmd;
};

#endif
