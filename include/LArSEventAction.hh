#ifndef __XEBRAEVENTACTION_H__
#define __XEBRAEVENTACTION_H__

#include "LArSAnalysisManager.hh"

#include <G4UserEventAction.hh>
#include <G4Event.hh>
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"


class G4Event;

class LArSEventAction : public G4UserEventAction
{
public:
	LArSEventAction(LArSAnalysisManager *pAnalysisManager = 0);
	~LArSEventAction();

public:
	void BeginOfEventAction(const G4Event *pEvent);
	void EndOfEventAction(const G4Event *pEvent);

private:
	LArSAnalysisManager *m_pAnalysisManager;
};

#endif // __XEBRAEVENTACTION_H__

