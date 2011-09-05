import FWCore.ParameterSet.Config as cms

process = cms.Process("hltAnaMu")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.GlobalTag.globaltag = 'GR_R_41_V0::All'
process.GlobalTag.globaltag = 'GR_R_42_V18::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
      "rfio:/castor/cern.ch/user/m/mironov/cmssw424hltpatch1/HICorePhysics_L1SingleMu3_RAWHLTRECO/root/l1SingleMu3_f0.root",
    )
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("muTree_ups912.root")
)

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
  centralityVariable = cms.string("HFhits"),
  nonDefaultGlauberModel = cms.string(""),
  centralitySrc = cms.InputTag("hiCentrality")
)


process.analysis = cms.EDAnalyzer('HLTMuTree',
  muons = cms.InputTag("muons"),
  vertices = cms.InputTag("hiSelectedVertex"),
#  vertices = cms.InputTag("offlinePrimaryVertices"),
  doReco = cms.untracked.bool(True),
  doGen = cms.untracked.bool(False),
  genparticle = cms.InputTag("hiGenParticles"),
  simtrack = cms.InputTag("mergedtruth","MergedTrackTruth"),
)

process.p = cms.Path(process.analysis)
