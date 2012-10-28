# for the list of used tags please see:
# https://twiki.cern.ch/twiki/bin/view/CMS/Onia2MuMuSamples

import FWCore.ParameterSet.Config as cms

# set up process
process = cms.Process("Onia2MuMuPAT")
process.load('Configuration.StandardSequences.Services_cff')

process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START53_V11::All'



# produce missing l1extraParticles
process.load('Configuration.StandardSequences.L1Reco_cff')
process.L1Reco_step = cms.Path(process.l1extraParticles)

# BSC or HF coincidence (masked unprescaled L1 bits)
process.load('L1Trigger.Skimmer.l1Filter_cfi')
process.bscOrHfCoinc = process.l1Filter.clone(
    algorithms = cms.vstring('L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_instance1', 'L1_NotBsc2_BscMinBiasOR', 'L1_HcalHfCoincidencePm')
    )
    

# Common offline event selection
process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")

# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltOniaHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltOniaHI.HLTPaths = ["HLT_PAL1DoubleMuOpenSingleAND_v1",
                              "HLT_PAMu1_Track1_Mgt2_v1",
                              "HLT_PAMu3_Track1_Mgt2_v1",
                              "HLT_PAL1SingleMuOpen_v2",
                              "HLT_PAMu1_v1",
                              "HLT_PAL1SingleMu3_v2",
                              "HLT_PAMu3_v1",
                              "HLT_PAL1SingleMu7_v2",
                              "HLT_PAMu7_v1",
                              "HLT_PAL1SingleMu12_v2",
                              "HLT_PAL1DoubleMu0_v2",
                              "HLT_PAL1DoubleMu0_HighQ_v1",
                              "HLT_PAL2Mu3_NHitQ_v1",
                              "HLT_PAL2DoubleMu0_v1",
                              "HLT_PAL2DoubleMu0_NHitQ_v1",
                              "HLT_PAL2DoubleMu0_L1HighQL2NHitQ_v1"]
process.hltOniaHI.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltOniaHI.throw = False
process.hltOniaHI.andOr = True

from HiSkim.HiOnia2MuMu.onia2MuMuPAT_cff import *

# ------ these were the modified pieces
onia2MuMuPAT(process, GlobalTag=process.GlobalTag.globaltag, MC=True, HLT="HLT", Filter=False)
process.genMuons.src                                = cms.InputTag("genParticles")
process.onia2MuMuPatGlbGlb.primaryVertexTag         = cms.InputTag("offlinePrimaryVertices")
process.onia2MuMuPatGlbGlb.addMuonlessPrimaryVertex = False
process.onia2MuMuPatGlbGlb.resolvePileUpAmbiguity   = False
process.patMuonsWithoutTrigger.pvSrc = "offlinePrimaryVertices"
#process.muonMatchHLTL3.matchedCuts = cms.string('coll("hltPAL3MuonCandidates")')
# ------ these were the modified pieces


process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    _input_
  ),
)





process.outOnia2MuMu.fileName = cms.untracked.string(
  _output_
)
process.outTnP.fileName       = cms.untracked.string( 'tnp_MC.root' )

process.outOnia2MuMu.outputCommands.extend(cms.untracked.vstring('keep *_generator_*_*'))
process.outOnia2MuMu.outputCommands.extend(cms.untracked.vstring('keep *_genParticles_*_*'))
process.outOnia2MuMu.outputCommands.extend(cms.untracked.vstring('keep *'))


#--------------------------------
process.options               = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.maxEvents             = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.patMuonSequence = cms.Sequence( process.hltOniaHI *
                                        process.genMuons *
                                        process.patMuonsWithTriggerSequence
                                        )
process.out_step        = cms.EndPath(process.outOnia2MuMu)
process.endjob_step     = cms.Path(process.endOfProcess) 

process.schedule            = cms.Schedule(process.L1Reco_step)
process.schedule.extend([process.Onia2MuMuPAT])
process.schedule.extend([process.endjob_step,process.out_step])

