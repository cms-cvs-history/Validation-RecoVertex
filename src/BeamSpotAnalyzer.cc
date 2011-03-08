// -*- C++ -*-
//
// Package:    Validation/RecoVertex
// Class:      BeamSpotAnalyzer
// 
/**\class BeamSpotAnalyzer BeamSpotAnalyzer.cc Validation/RecoVertex/plugins/BeamSpotAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andrea Venturi
//         Created:  Mon Oct 27 17:37:53 CET 2008
// $Id: BeamSpotAnalyzer.cc,v 1.2 2010/11/30 09:07:06 venturia Exp $
//
//


// system include files
#include <memory>

// user include files

#include <vector>
#include <map>
#include <limits>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"

#include "Validation/RecoVertex/interface/BeamSpotHistogramMaker.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"


//
// class decleration
//

class BeamSpotAnalyzer : public edm::EDAnalyzer {
   public:
      explicit BeamSpotAnalyzer(const edm::ParameterSet&);
      ~BeamSpotAnalyzer();


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  virtual void endRun(const edm::Run&, const edm::EventSetup&);
  virtual void endJob() ;

      // ----------member data ---------------------------

  BeamSpotHistogramMaker _bshm;
  edm::InputTag _bscollection;


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
BeamSpotAnalyzer::BeamSpotAnalyzer(const edm::ParameterSet& iConfig):
  _bshm(iConfig.getParameter<edm::ParameterSet>("bsHistogramMakerPSet")),
  _bscollection(iConfig.getParameter<edm::InputTag>("bsCollection"))
{
   //now do what ever initialization is needed

  //

  _bshm.book();

}


BeamSpotAnalyzer::~BeamSpotAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
BeamSpotAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  // get BS

  Handle<reco::BeamSpot> bs;
  iEvent.getByLabel(_bscollection,bs);
  _bshm.fill(iEvent.orbitNumber(),*bs);

}


// ------------ method called once each job just before starting event loop  ------------
void 
BeamSpotAnalyzer::beginJob()
{ }

void
BeamSpotAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {

  _bshm.beginRun(iRun.run());

}

void
BeamSpotAnalyzer::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {

}
// ------------ method called once each job just after ending the event loop  ------------
void 
BeamSpotAnalyzer::endJob() {
}


//define this as a plug-in
DEFINE_FWK_MODULE(BeamSpotAnalyzer);
