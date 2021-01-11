//XEBRA header files
#include "LArSSensitiveDetector.hh"

#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>

#include <map>


using std::map;

LArSSensitiveDetector::LArSSensitiveDetector(G4String hName): G4VSensitiveDetector(hName)
{
	collectionName.insert("LArHitsCollection");
}

LArSSensitiveDetector::~LArSSensitiveDetector()
{
}

void LArSSensitiveDetector::Initialize(G4HCofThisEvent* pHitsCollectionOfThisEvent)
{
	m_pLXeHitsCollection = new LArSLXeHitsCollection(SensitiveDetectorName, collectionName[0]);

	static G4int iHitsCollectionID = -1;

	if(iHitsCollectionID < 0)
		iHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	
	pHitsCollectionOfThisEvent->AddHitsCollection(iHitsCollectionID, m_pLXeHitsCollection);

	m_hParticleTypes.clear();
}

G4bool LArSSensitiveDetector::ProcessHits(G4Step* pStep, G4TouchableHistory *)
{
	G4double dEnergyDeposited = pStep->GetTotalEnergyDeposit();
	G4Track *pTrack = pStep->GetTrack();

	LArSLXeHit* pHit = new LArSLXeHit();

	pHit->SetTrackId(pTrack->GetTrackID());

	if(!m_hParticleTypes.count(pTrack->GetTrackID()))
		m_hParticleTypes[pTrack->GetTrackID()] = pTrack->GetDefinition()->GetParticleName();

	pHit->SetParentId(pTrack->GetParentID());
	pHit->SetParticleType(pTrack->GetDefinition()->GetParticleName());

	if(pTrack->GetParentID())
		pHit->SetParentType(m_hParticleTypes[pTrack->GetParentID()]);
	else
		pHit->SetParentType(G4String("none"));

	if(pTrack->GetCreatorProcess())
		pHit->SetCreatorProcess(pTrack->GetCreatorProcess()->GetProcessName());
	else
		pHit->SetCreatorProcess(G4String("Null"));

	pHit->SetDepositingProcess(pStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
	pHit->SetPosition(pStep->GetPostStepPoint()->GetPosition());
	pHit->SetEnergyDeposited(dEnergyDeposited);
	pHit->SetKineticEnergy(pTrack->GetKineticEnergy());
	pHit->SetTime(pTrack->GetGlobalTime());
	
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	pHit->SetPreMomentumDir(pStep->GetPreStepPoint()->GetMomentumDirection());
	pHit->SetPostMomentumDir(pStep->GetPostStepPoint()->GetMomentumDirection());
	pHit->SetPreKineticEnergy(pStep->GetPreStepPoint()->GetKineticEnergy());
	pHit->SetPostKineticEnergy(pStep->GetPostStepPoint()->GetKineticEnergy());

	m_pLXeHitsCollection->insert(pHit);

	return true;
}

void LArSSensitiveDetector::EndOfEvent(G4HCofThisEvent *){ 
}

