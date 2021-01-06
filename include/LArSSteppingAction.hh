#ifndef LArSSteppingAction_H
#define LArSSteppingAction_H 1

#include "LArSAnalysisManager.hh"

#include "globals.hh"

//Additional header files
#include <string.h>
#include <cmath>

//G4 header files
#include "G4UserSteppingAction.hh"
#include "G4SteppingManager.hh"
//#include "G4SteppingManager.hh"

class LArSAnalysisManager;

class LArSSteppingAction : public G4UserSteppingAction
{
    public:
        LArSSteppingAction(LArSAnalysisManager*);
        ~LArSSteppingAction(){};

         void UserSteppingAction(const G4Step*);

    private:
        G4String particle;
        LArSAnalysisManager* myAnalysisManager;
};

#endif
