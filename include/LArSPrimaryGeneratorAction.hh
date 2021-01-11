#ifndef __LARSPRIMARYGENERATORACTION_H__
#define __LARSPRIMARYGENERATORACTION_H__

//Root Header Files
#include <TFile.h>
#include <TH1.h>
#include <TParameter.h>

//DAWRIN Header Files
#include "LArSPrimaryGeneratorMessenger.hh"
#include "LArSParticleSource.hh"

//Additional Header Files
#include <globals.hh>
#include <Randomize.hh>


//G4Header Files
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4GeneralParticleSource.hh>
#include <G4ParticleGun.hh>
#include <G4EmCalculator.hh>

//G4 Header Files
#include <G4RunManagerKernel.hh>
#include <G4Event.hh>
#include <G4GeneralParticleSource.hh>
#include <G4Material.hh>
#include <G4ThreeVector.hh>
#include <G4TransportationManager.hh>
#include <G4Navigator.hh>
#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4PrimaryVertex.hh>
#include <G4ParticleDefinition.hh>
#include <G4Point3D.hh>
#include <G4Vector3D.hh>
#include <G4SingleParticleSource.hh>
#include <G4SystemOfUnits.hh>


enum{
  HIST_WEIGHT
};

class LArSParticleSource;
class G4Event;

class LArSPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
  LArSPrimaryGeneratorAction(G4String fName);
  ~LArSPrimaryGeneratorAction();

public:
  const long *GetEventSeeds() { return m_lSeeds; }
  const G4String &GetParticleTypeOfPrimary() { return m_hParticleTypeOfPrimary; }
  G4double GetEnergyOfPrimary() { return m_dEnergyOfPrimary; }
  G4ThreeVector GetPositionOfPrimary() { return m_hPositionOfPrimary; }
  G4ThreeVector GetForcedPositionOfPrimary() { return m_hForcedPositionOfPrimary; }

  G4double ComputeForcedTransportWeight(G4ThreeVector x0, G4ThreeVector dir, G4double Len, G4double e); //changed L to Len
  void     SetVarianceReduction(G4bool doit)      {VarianceReduction = doit;};
  void     SetVarianceReductionMode(G4int val)    {VarianceReductionMode = val;};
  void     SetSurvivalProbabilityCut(G4double val){p_survive_cut = val;};
  void     SetFT_cyl_center(G4ThreeVector xc){ft_cyl_center = xc;};
  void     SetFT_cyl_length(G4double      Len ){ft_cyl_L      = Len;}; //changed L to Len
  void     SetFT_cyl_radius(G4double      R ){ft_cyl_R      = R;}; 
  
  void     SetWriteEmpty(G4bool doit){writeEmpty = doit;};
  G4bool   GetWriteEmpty(){return writeEmpty;};
  
  void     GeneratePrimaries(G4Event *pEvent);
  
  void     GeneratePrimariesStandard(G4Event *pEvent);
  //void     GeneratePrimariesAccelerated(G4Event *pEvent); 
  void     GeneratePrimariesAccelerated( void ); //changed by Patricia
  void     FillHistograms();
  G4int    IntersectWithTarget(G4ThreeVector x0, G4ThreeVector dir);
  G4double GetNumberOfRejectedPrimaries(){return numberOfRejectedPrimaries;};
  G4double GetNumberOfAcceptedPrimaries(){return numberOfAcceptedPrimaries;};
  G4double ComputeGammaMeanFreePath(G4double e, G4String matName);
  
private:

  enum{
    KILL_ONLY,
    KILL_RR,
    KILL_FT_EDGE,
    KILL_FT_PATH
  };

 // messenger
  LArSPrimaryGeneratorMessenger *m_pMessenger;
  //
  G4bool           writeEmpty;
  
  //
  long             m_lSeeds[2];
  G4String         m_hParticleTypeOfPrimary;
  G4double         m_dEnergyOfPrimary;
  G4ThreeVector    m_hPositionOfPrimary;
  G4ThreeVector    m_hDirectionOfPrimary;

  // if you choose to force the vertex position to somewhere else....
  G4bool           VarianceReduction;
  G4int            VarianceReductionMode;
  G4ThreeVector    m_hForcedPositionOfPrimary;
  G4ParticleTable* particleTable;
  G4ParticleGun*   particleGun;
  G4Navigator*     theNavigator;

  // survival probability cut 
  G4double         p_survive_cut;

  // forced transport target cylinder
  G4double         ft_cyl_R;
  G4double         ft_cyl_L;
  G4ThreeVector    ft_cyl_center;

  std::vector<G4ThreeVector> ft_cyl_intersect;
  std::vector<G4double>      ft_cyl_intersect_s;

  // accounting 
  G4int            ntry_max;
  G4double         numberOfRejectedPrimaries;
  G4double         numberOfAcceptedPrimaries;
  G4double         runWeight;
  // em calculator
  G4EmCalculator   emCalc;

  // histograms
  TFile      *_f_prim;
  TDirectory *_generator;
  G4String   generatorRootFile;

  TParameter<double> *nRejectParameter;
  TParameter<double> *nAcceptParameter;
  
  TH1F       *_log_primary_w;
  TH1F       *_cost_all;
  TH1F       *_cost_accept;
  TH1F       *_energy_all;
  TH1F       *_energy_accept;

  LArSParticleSource   *m_pParticleSource;

};

#endif
