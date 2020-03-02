#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>

#include <AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h>
#include <AsgTools/AnaToolHandle.h>

// Histograms
#include <TH1.h>
#include <TH2.h>

// Jet Cleaning
#include <JetInterface/IJetSelector.h>

// JER
#include <JetResolution/IJERTool.h>

// Jet Calibration Tool
#include <JetCalibTools/IJetCalibrationTool.h>
#include "JetCalibTools/JetCalibrationTool.h"

// Jet Vertexing Tool
#include <JetMomentTools/JetVertexTaggerTool.h> //Working on this

// Ntuple
#include <TTree.h>
#include <vector>

class MyxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

 // Destructor for Ntuples
  ~MyxAODAnalysis ()  override;

 //calibrated jets individual
   std::vector<float> *m_jetPhi_calib_1 = nullptr;
   std::vector<float> *m_jetEta_calib_1 = nullptr;
   std::vector<float> *m_jetPt_calib_1 = nullptr;
   std::vector<float> *m_jetPhi_calib_2 = nullptr;
   std::vector<float> *m_jetEta_calib_2 = nullptr;
   std::vector<float> *m_jetPt_calib_2 = nullptr;
   std::vector<float> *m_jetPhi_calib_3 = nullptr;
   std::vector<float> *m_jetEta_calib_3 = nullptr;
   std::vector<float> *m_jetPt_calib_3 = nullptr;
  
  // GRL Tool
  asg::AnaToolHandle<IGoodRunsListSelectionTool> m_grl; //!

  // Jet Cleaning Tool
  asg::AnaToolHandle<IJetSelector> m_jetCleaning; //!

  // Jet Calibration Tool
  asg::AnaToolHandle<IJetCalibrationTool> m_JetCalibrationTool_handle; //!

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

private:
  // Configuration, and any other types of variables go here.
  //float m_cutValue;
  //TTree *m_myTree;
  //TH1 *m_myHist;
  
  int jetCount; //!
};

#endif
