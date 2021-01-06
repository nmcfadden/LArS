#include <G4SystemOfUnits.hh>

#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

#include "LArSPmtHit.hh"


G4Allocator<LArSPmtHit> LArSPmtHitAllocator;

LArSPmtHit::LArSPmtHit() {}

LArSPmtHit::~LArSPmtHit() {}

LArSPmtHit::LArSPmtHit(const LArSPmtHit &hLArSPmtHit):G4VHit()
{
	m_hPosition = hLArSPmtHit.m_hPosition;
	m_dTime = hLArSPmtHit.m_dTime;
	m_iPmtNb = hLArSPmtHit.m_iPmtNb;
}

const LArSPmtHit &
LArSPmtHit::operator=(const LArSPmtHit &hLArSPmtHit)
{
	m_hPosition = hLArSPmtHit.m_hPosition;
	m_dTime = hLArSPmtHit.m_dTime;
	m_iPmtNb = hLArSPmtHit.m_iPmtNb;
	
	return *this;
}

G4int
LArSPmtHit::operator==(const LArSPmtHit &hLArSPmtHit) const
{
	return ((this == &hLArSPmtHit) ? (1) : (0));
}

void LArSPmtHit::Draw()
{
}

void LArSPmtHit::Print()
{
	G4cout << "Pmt hit ---> " 
		<< "Pmt#" << m_iPmtNb
		<< " Position: " << m_hPosition.x()/mm
		<< " " << m_hPosition.y()/mm
		<< " " << m_hPosition.z()/mm
		<< " mm"
		<< " Time: " << m_dTime/s << " s" << G4endl;
}

