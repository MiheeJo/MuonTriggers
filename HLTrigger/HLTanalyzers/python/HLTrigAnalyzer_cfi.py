import FWCore.ParameterSet.Config as cms

hltriganalysis = cms.EDAnalyzer("HLTrigAnalyzer",
    ### Trigger objects
    l1GtReadoutRecord               = cms.InputTag("hltGtDigis::TEST"),
    hltresults                      = cms.InputTag("TriggerResults::TEST"),
    HLTProcessName                  = cms.string("TEST"),
                                
    ### Run parameters
    RunParameters = cms.PSet(
    HistogramFile = cms.untracked.string('hltriganalysis.root')
    )
                                
)
