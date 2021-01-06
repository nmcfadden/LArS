#ifndef __XEBRALXESENSITIVEDETECTOR_H__
#define __XEBRALXESENSITIVEDETECTOR_H__

#include "LArSLXeHit.hh"

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class LArSLXeSensitiveDetector: public G4VSensitiveDetector
{
public:
        //Constructor
	LArSLXeSensitiveDetector(G4String hName);
        //Destructor
	~LArSLXeSensitiveDetector();

        //mandatory base class
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);

        //optional functions
	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);

private:
	LArSLXeHitsCollection *m_pLXeHitsCollection;
	std::map<int,G4String> m_hParticleTypes;
};

#endif
