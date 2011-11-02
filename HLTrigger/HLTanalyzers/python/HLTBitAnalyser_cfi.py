import FWCore.ParameterSet.Config as cms

hltbitanalysis = cms.EDAnalyzer("HLTBitAnalyzer",
    ### Trigger objects
    l1GctHFBitCounts                = cms.InputTag("hltGctDigis"),
    l1GctHFRingSums                 = cms.InputTag("hltGctDigis"),
    l1GtObjectMapRecord             = cms.InputTag("hltL1GtObjectMap::TEST"),
    l1GtReadoutRecord               = cms.InputTag("hltGtDigis::TEST"),

    l1extramc                       = cms.string('hltL1extraParticles'),
    l1extramu                       = cms.string('hltL1extraParticles'),
    hltresults                      = cms.InputTag("TriggerResults::TEST"),
    HLTProcessName                  = cms.string("TEST"),
                                
    ### Run parameters
    RunParameters = cms.PSet(
    HistogramFile = cms.untracked.string('hltbitanalysis.root')
    )
                                
)
