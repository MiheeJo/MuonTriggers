import FWCore.ParameterSet.Config as cms

hltMuTree = cms.EDAnalyzer("HLTMuTree",
  muons = cms.InputTag("muons"),
  vertices = cms.InputTag("hiSelectedVertex"),
  genparticle = cms.InputTag("hiGenParticles"),
  simtrack = cms.InputTag("mergedtruth","MergedTrackTruth"),
  doReco = cms.untracked.bool(True),
  doGen = cms.untracked.bool(False),
  doHLT = cms.untracked.bool(False),
  MuCandTag2 = cms.InputTag("hltL2MuonCandidates"),
  MuCandTag3 = cms.InputTag("hltHIL3MuonCandidates"),
)
