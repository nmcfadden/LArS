#ifndef __XEBRARUNACTION_H__
#define __XEBRARUNACTION_H__

#include "LArSRunActionMessenger.hh"
#include "LArSAnalysisManager.hh"


//Additional Header Files
#include <Randomize.hh>
#include <sys/time.h>

//G4 header files
#include <G4UserRunAction.hh>
#include "G4UImanager.hh"
#include "G4VVisManager.hh"

class G4Run;

class LArSAnalysisManager;


class LArSRunAction: public G4UserRunAction
{
public:
	LArSRunAction(LArSAnalysisManager *pAnalysisManager=0);
	~LArSRunAction();

public:
	void BeginOfRunAction(const G4Run *pRun);
	void EndOfRunAction(const G4Run *pRun);
        
	void SetRanSeed(G4int hRanSeed) { m_hRanSeed = hRanSeed; }
//	void SetForcedTransport(G4bool doit) { m_hForcedTransport = doit; }

private:
	G4int m_hRanSeed;
//        G4bool m_hForcedTransport;
	LArSAnalysisManager *m_pAnalysisManager;
	LArSRunActionMessenger *m_pMessenger;
};

#endif
