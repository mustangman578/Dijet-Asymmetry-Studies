#The name of the package:
atlas_subdir (MyAnalysis)

# Add the shared library:
atlas_add_library (MyAnalysisLib
  MyAnalysis/*.h Root/*.cxx
  PUBLIC_HEADERS MyAnalysis
  LINK_LIBRARIES ${ROOT_LIBRARIES} EventLoop EventLoopGrid xAODBase xAODRootAccess xAODEventInfo GoodRunsListsLib PileupReweightingLib PATInterfaces
                   PathResolver xAODTau xAODJet xAODMuon xAODEgamma
                   xAODTracking xAODTruth MuonMomentumCorrectionsLib
                   MuonEfficiencyCorrectionsLib MuonSelectorToolsLib
JetCalibToolsLib
                   JetSelectorToolsLib AthContainers
                   ElectronPhotonFourMomentumCorrectionLib
                   ElectronEfficiencyCorrectionLib
ElectronPhotonSelectorToolsLib
                   IsolationSelectionLib IsolationCorrectionsLib
                   ElectronPhotonShowerShapeFudgeToolLib
                   FTagAnalysisInterfacesLib MuonAnalysisInterfacesLib
                   PhotonEfficiencyCorrectionLib METUtilitiesLib METInterface
                   TauAnalysisToolsLib AsgTools xAODMissingET JetResolutionLib
                   AssociationUtilsLib JetEDM JetUncertaintiesLib
                   JetCPInterfaces xAODBTaggingEfficiencyLib TrigConfxAODLib
                   TrigDecisionToolLib xAODCutFlow JetMomentToolsLib
                   TriggerMatchingToolLib xAODMetaDataCnv xAODMetaData
                   JetJvtEfficiencyLib PMGToolsLib JetSubStructureUtils
JetTileCorrectionLib
                   ${release_libs})

if (XAOD_STANDALONE)
 # Add the dictionary (for AnalysisBase only):
 atlas_add_dictionary (MyAnalysisDict
  MyAnalysis/MyAnalysisDict.h
  MyAnalysis/selection.xml
  LINK_LIBRARIES MyAnalysisLib)
endif ()

if (NOT XAOD_STANDALONE)
  # Add a component library for AthAnalysis only:
  atlas_add_component (MyAnalysis
    src/components/*.cxx
    LINK_LIBRARIES MyAnalysisLib)
endif ()

# Install files from the package:
atlas_install_joboptions( share/*_jobOptions.py )
atlas_install_scripts( share/*_eljob.py )
