import FWCore.ParameterSet.Config as cms

process = cms.Process('HltAna')

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
"rfio:/castor/cern.ch/user/m/mironov/cmssw440/newL1/root/hlt_f9.root",
))

# tree output
process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("hiOHTrees.root"))

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))

#load some general stuff
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_44_V4::All'
#process.GlobalTag.globaltag = 'START43_V4::All'

process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.RawToDigi_cff')

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFhits"),
	nonDefaultGlauberModel = cms.string(""),
	centralitySrc = cms.InputTag("hiCentrality")
	)


from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_hf_cfi")
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.load("RecoLuminosity.LumiProducer.lumiProducer_cff")

process.load("RecoHI.HiCentralityAlgos.HiCentrality_cfi")
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceBasicClusters = False
process.hiCentrality.produceZDChits = False
process.hiCentrality.produceETmidRapidity = False
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = False
process.hiCentrality.producePixelTracks = False

# Define the analyzer modules
process.load("HLTrigger.HLTanalyzers.HI_HLTAnalyser_cff")
process.hltanalysis.RunParameters.Debug = False
process.hltanalysis.RunParameters.UseTFileService = True
process.hltanalysis.RunParameters.Monte = False
process.hltanalysis.RunParameters.DoMC = False

process.hltanalysis.RunParameters.DoMuons = True
process.hltanalysis.RunParameters.DoL2Muons = True
process.hltanalysis.RunParameters.DoL3Muons = True
process.hltanalysis.RunParameters.DoJets = False
process.hltanalysis.RunParameters.DoPhotons = False
process.hltanalysis.RunParameters.DoSuperClusters = False

process.hltanalysis.RunParameters.DoPhotons = False
process.hltanalysis.RunParameters.DoSuperClusters = False
process.hltanalysis.RunParameters.DoVertex = False
process.hltanalysis.RunParameters.DoHeavyIon = False

process.hltanalysis.MuCandTag2 = cms.InputTag("hltL2MuonCandidates")
process.hltanalysis.MuCandTag3 = cms.InputTag("hltHIL3MuonCandidates")
#process.hltanalysis.MuCandTag3 = cms.InputTag("hltHIL3IOIter0MuonCandidates")
#process.hltanalysis.MuCandTag3 = cms.InputTag("hltHIL3IOIter1MuonCandidates")
#process.hltanalysis.MuCandTag3 = cms.InputTag("hltHIL3IOIter12MuonCandidates")

process.hltanalysis.l1GtReadoutRecord = cms.InputTag("hltGtDigis")
process.hltanalysis.hltresults = "TriggerResults::TestHlt"
#process.hltanalysis.HLTProcessName = "TestHlt"
#process.hltanalysis.hltresults = "TriggerResults::L1HltRecoAna"
#process.hltanalysis.HLTProcessName = "L1HltRecoAna"


# =============== Final Paths =====================
'''
process.ana_step = cms.Path(
    process.lumiProducer
    *
    process.hcalDigis
    *
    process.hfreco
    *    
    process.hiCentrality * process.centralityBin * process.hltanalysis
    )
'''
process.ana_step = cms.Path(process.hltanalysis)
