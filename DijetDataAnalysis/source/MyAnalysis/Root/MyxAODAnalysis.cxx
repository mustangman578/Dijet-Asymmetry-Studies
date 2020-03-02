#include <AsgTools/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>
#include <TSystem.h>
#include <xAODJet/JetContainer.h>
#include <xAODCore/ShallowCopy.h>

using namespace std;


MyxAODAnalysis :: MyxAODAnalysis (const std::string& name,ISvcLocator *pSvcLocator): EL::AnaAlgorithm (name, pSvcLocator)
, m_grl ("GoodRunsListSelectionTool/grl", this)
, m_jetCleaning ("JetCleaningTool/JetCleaning", this)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  This is also where you
  // declare all properties for your algorithm.  Note that things like
  // resetting statistics variables or booking histograms should
  // rather go into the initialize() function.
}



StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  
  ANA_MSG_INFO ("in initialize");

  // Initialize GRL Tool
  const char* GRLFilePath = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data16_13TeV/20161101/data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml"; // For data16
  const char* fullGRLFilePath = gSystem->ExpandPathName (GRLFilePath);
  std::vector<std::string> vecStringGRL;
  vecStringGRL.push_back(fullGRLFilePath);
  ANA_CHECK(m_grl.setProperty( "GoodRunsListVec", vecStringGRL));
  ANA_CHECK(m_grl.setProperty("PassThrough", false)); // if true (default) will ignore result of GRL and will just pass all events
  ANA_CHECK(m_grl.initialize());

  // Initialize Jet Cleaning Tool
  ANA_CHECK (m_jetCleaning.setProperty( "CutLevel", "LooseBad"));
  ANA_CHECK (m_jetCleaning.setProperty("DoUgly", false));
  ANA_CHECK (m_jetCleaning.initialize());

  // Initialize Jet Calibration Tool

  TString jetAlgo = "AntiKt4EMPFlow";
  // Config file WITHOUT TG3 applied
  TString config = "JES_JMS_MC16Recommendation_Consolidated_data_only_PFlow_July2019_Rel21.config";
  // Calibration sequence WITHOUT TG3 applied
  TString calibSeq = "JetArea_Residual_EtaJES_GSC_JMS_Insitu";
  TString calibArea = "00-04-82"; // Calibration Area tag (see below)
  bool isData = true;
  m_JetCalibrationTool_handle.setTypeAndName("JetCalibrationTool/name");
  if( !m_JetCalibrationTool_handle.isUserConfigured() )
	{
		ANA_CHECK( m_JetCalibrationTool_handle.setProperty("JetCollection",jetAlgo.Data()) );
    		ANA_CHECK( m_JetCalibrationTool_handle.setProperty("ConfigFile",config.Data()) );
    		ANA_CHECK( m_JetCalibrationTool_handle.setProperty("CalibSequence",calibSeq.Data()) );
    		ANA_CHECK( m_JetCalibrationTool_handle.setProperty("CalibArea",calibArea.Data()) );
    		ANA_CHECK( m_JetCalibrationTool_handle.setProperty("IsData",isData) );
	}

  // Ntuple initialize

  ANA_CHECK (book (TTree ("analysis", "My analysis ntuple")));
  TTree* m_tree = tree ("analysis");

  // calibrated jet individual
  m_jetEta_calib_1 = new std::vector<float>();
  m_tree->Branch ("JetEta_calib_1", &m_jetEta_calib_1);
  m_jetPt_calib_1 = new std::vector<float>();
  m_tree->Branch ("JetPt_calib_1", &m_jetPt_calib_1);
  m_jetPhi_calib_1 = new std::vector<float>();
  m_tree->Branch ("JetPhi_calib_1", &m_jetPhi_calib_1);

  m_jetEta_calib_2 = new std::vector<float>();
  m_tree->Branch ("JetEta_calib_2", &m_jetEta_calib_2);
  m_jetPt_calib_2 = new std::vector<float>();
  m_tree->Branch ("JetPt_calib_2", &m_jetPt_calib_2);
  m_jetPhi_calib_2 = new std::vector<float>();
  m_tree->Branch ("JetPhi_calib_2", &m_jetPhi_calib_2);

  m_jetEta_calib_3 = new std::vector<float>();
  m_tree->Branch ("JetEta_calib_3", &m_jetEta_calib_3);
  m_jetPt_calib_3 = new std::vector<float>();
  m_tree->Branch ("JetPt_calib_3", &m_jetPt_calib_3);
  m_jetPhi_calib_3 = new std::vector<float>();
  m_tree->Branch ("JetPhi_calib_3", &m_jetPhi_calib_3);
  return StatusCode::SUCCESS;
}

// Destructor for Ntuple
MyxAODAnalysis::~MyxAODAnalysis()
{
// calibrated jets individual
   if (m_jetEta_calib_1) delete m_jetEta_calib_1;
   if (m_jetPt_calib_1)  delete m_jetPt_calib_1;
   if (m_jetPhi_calib_1)  delete m_jetPhi_calib_1;

   if (m_jetEta_calib_2) delete m_jetEta_calib_2;
   if (m_jetPt_calib_2)  delete m_jetPt_calib_2;
   if (m_jetPhi_calib_2)  delete m_jetPhi_calib_2;

   if (m_jetEta_calib_3) delete m_jetEta_calib_3;
   if (m_jetPt_calib_3)  delete m_jetPt_calib_3;
   if (m_jetPhi_calib_3)  delete m_jetPhi_calib_3;
}

StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  

  //ANA_MSG_INFO ("in execute");
  // retrieve the eventInfo object from the event store
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK (evtStore()->retrieve (eventInfo, "EventInfo"));

  bool isMC = false;
  // Check if the event is MC
  if (eventInfo->eventType (xAOD::EventInfo::IS_SIMULATION))
	{
		isMC = true;
	}
  if (!isMC)
	{
		if (!m_grl->passRunLB(*eventInfo))
			{
				return StatusCode::SUCCESS; // go to next event
			}
	}

  //--------------
  // shallow copy
  //-------------
  
  // get jet container of interest
  const xAOD::JetContainer* jets = nullptr;
  ANA_CHECK(evtStore()->retrieve( jets, "AntiKt4EMPFlowJets" ));	
  // calibrated jets individual 
  m_jetEta_calib_1->clear();
  m_jetPt_calib_1->clear();
  m_jetPhi_calib_1->clear();

  m_jetEta_calib_2->clear();
  m_jetPt_calib_2->clear();
  m_jetPhi_calib_2->clear();

  m_jetEta_calib_3->clear();
  m_jetPt_calib_3->clear();
  m_jetPhi_calib_3->clear();
 
  auto shallowCopy = xAOD::shallowCopyContainer (*jets);
  std::unique_ptr<xAOD::JetContainer> shallowJets (shallowCopy.first);
  std::unique_ptr<xAOD::ShallowAuxContainer> shallowAux (shallowCopy.second);
  
  jetCount = 0;
  for (auto jetSC : *shallowJets)
  {
    if (shallowJets->size() <= 3)
	{
		jetCount++;
		if (!m_jetCleaning->keep (*jetSC)) //only keep good clean jets
			{
				continue;
			}
	}
    m_JetCalibrationTool_handle->applyCalibration(*jetSC); // Calibrate the jet
    if (jetCount == 1)
	{
		m_jetPt_calib_1->push_back ((jetSC)->pt() * 0.001); // GeV
		m_jetEta_calib_1->push_back ((jetSC)->eta());
		m_jetPhi_calib_1->push_back ((jetSC)->phi());
	}
    if (jetCount == 2)
	{
		m_jetPt_calib_2->push_back ((jetSC)->pt() * 0.001); // GeV
                m_jetEta_calib_2->push_back ((jetSC)->eta());
                m_jetPhi_calib_2->push_back ((jetSC)->phi());
	}
    if (jetCount == 3)
	{
		m_jetPt_calib_3->push_back ((jetSC)->pt() * 0.001); // GeV
                m_jetEta_calib_3->push_back ((jetSC)->eta());
                m_jetPhi_calib_3->push_back ((jetSC)->phi());
	}	 	
  }
  tree ("analysis")->Fill (); 
  return StatusCode::SUCCESS;
}



StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.
  return StatusCode::SUCCESS;
}
