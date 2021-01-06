#include "LArSLXeHit.hh"

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

//#include "LArSLXeHit.hh"


G4Allocator<LArSLXeHit> LArSLXeHitAllocator;

LArSLXeHit::LArSLXeHit() {}

LArSLXeHit::~LArSLXeHit()
{
	if(m_pParticleType) delete m_pParticleType;
	if(m_pParentType) delete m_pParentType;
	if(m_pCreatorProcess) delete m_pCreatorProcess;
	if(m_pDepositingProcess) delete m_pDepositingProcess;
}

LArSLXeHit::LArSLXeHit(const LArSLXeHit &hLArSLXeHit):G4VHit()
{
	m_iTrackId = hLArSLXeHit.m_iTrackId;
	m_iParentId = hLArSLXeHit.m_iParentId;
	m_pParticleType = hLArSLXeHit.m_pParticleType;
	m_pParentType = hLArSLXeHit.m_pParentType;
	m_pCreatorProcess = hLArSLXeHit.m_pCreatorProcess;
	m_pDepositingProcess = hLArSLXeHit.m_pDepositingProcess;
	m_hPosition = hLArSLXeHit.m_hPosition;
	m_dEnergyDeposited = hLArSLXeHit.m_dEnergyDeposited;
	m_dKineticEnergy = hLArSLXeHit.m_dKineticEnergy;
	m_dTime = hLArSLXeHit.m_dTime;
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	m_hPreMomentumDir = hLArSLXeHit.m_hPreMomentumDir;
	m_hPostMomentumDir = hLArSLXeHit.m_hPostMomentumDir;
	m_dPreKineticEnergy = hLArSLXeHit.m_dPreKineticEnergy;
	m_dPostKineticEnergy = hLArSLXeHit.m_dPostKineticEnergy;
}

const LArSLXeHit &
LArSLXeHit::operator=(const LArSLXeHit &hLArSLXeHit)
{
	m_iTrackId = hLArSLXeHit.m_iTrackId;
	m_iParentId = hLArSLXeHit.m_iParentId;
	m_pParticleType = hLArSLXeHit.m_pParticleType;
	m_pParentType = hLArSLXeHit.m_pParentType;
	m_pCreatorProcess = hLArSLXeHit.m_pCreatorProcess;
	m_pDepositingProcess = hLArSLXeHit.m_pDepositingProcess;
	m_hPosition = hLArSLXeHit.m_hPosition;
	m_dEnergyDeposited = hLArSLXeHit.m_dEnergyDeposited;
	m_dKineticEnergy = hLArSLXeHit.m_dKineticEnergy;
	m_dTime = hLArSLXeHit.m_dTime;
	m_hPreMomentumDir = hLArSLXeHit.m_hPreMomentumDir;
	m_hPostMomentumDir = hLArSLXeHit.m_hPostMomentumDir;
	m_dPreKineticEnergy = hLArSLXeHit.m_dPreKineticEnergy;
	m_dPostKineticEnergy = hLArSLXeHit.m_dPostKineticEnergy;
	
	return *this;
}

G4int
LArSLXeHit::operator==(const LArSLXeHit &hLArSLXeHit) const
{
	return ((this == &hLArSLXeHit) ? (1) : (0));
}

void LArSLXeHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	
	if(pVVisManager)
	{
		G4Circle hCircle(m_hPosition);
		G4Colour hColour(1.000, 0.973, 0.184);
		G4VisAttributes hVisAttributes(hColour);
		
		hCircle.SetScreenSize(0.1);
		hCircle.SetFillStyle(G4Circle::filled);
		hCircle.SetVisAttributes(hVisAttributes);
		pVVisManager->Draw(hCircle);
	}
}

void LArSLXeHit::Print()
{
	 G4cout << "-------------------- LXe hit --------------------" 
		<< "Id: " << m_iTrackId
		<< " Particle: " << *m_pParticleType
		<< " ParentId: " << m_iParentId
		<< " ParentType: " << *m_pParentType << G4endl
		<< " CreatorProcess: " << *m_pCreatorProcess
		<< " DepositingProcess: " << *m_pDepositingProcess << G4endl
		<< " Position: " << m_hPosition.x()/mm
		<< " " << m_hPosition.y()/mm
		<< " " << m_hPosition.z()/mm
		<< " mm" << G4endl
		<< " EnergyDeposited: " << m_dEnergyDeposited/keV << " keV"
		<< " KineticEnergyLeft: " << m_dKineticEnergy/keV << " keV"
		<< " Time: " << m_dTime/s << " s" << G4endl
		<< " Momentum direction before hit: " << m_hPreMomentumDir.x()	// DR 20161012
		<< " " << m_hPreMomentumDir.y()
		<< " " << m_hPreMomentumDir.z() << G4endl
		<< " Momentum direction after hit: " << m_hPostMomentumDir.x()
		<< " " << m_hPostMomentumDir.y()
		<< " " << m_hPostMomentumDir.z() << G4endl
		<< " KineticEnergy before hit: " << m_dPreKineticEnergy/keV << " keV"
		<< " Kinetic Energy after hit: " << m_dPostKineticEnergy/keV << " keV" << G4endl;
}

