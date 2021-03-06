#ifndef __LARSPHYSICSMESSENGER_H__
#define __LARSPHYSICSMESSENGER_H__

//  LArSPhysicsMessenger class.
//  Allow for setting of preferences in the PhysicsList

#include <G4UImessenger.hh>
#include <globals.hh>

class LArSPhysicsList;

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

class LArSPhysicsMessenger: public G4UImessenger
{
public:
  LArSPhysicsMessenger(LArSPhysicsList *pPhysicsList);
  ~LArSPhysicsMessenger();
  
  void SetNewValue(G4UIcommand *pCommand, G4String hNewValues);
private:
  LArSPhysicsList          *m_pPhysicsList;
  G4UIdirectory              *m_pDirectory;
  G4UIcmdWithAString         *m_pEMlowEnergyModelCmd;
  G4UIcmdWithAString         *m_pHadronicModelCmd;
  G4UIcmdWithABool           *m_pCerenkovCmd;
  G4UIcmdWithABool           *m_pHistosCmd;
};

#endif
