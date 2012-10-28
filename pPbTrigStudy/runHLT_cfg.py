# for the list of used tags please see:
# https://twiki.cern.ch/twiki/bin/view/CMS/Onia2MuMuSamples

import FWCore.ParameterSet.Config as cms

# set up process
process = cms.Process("HLT")
process.load('Configuration.StandardSequences.Services_cff')

process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START53_V11::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source("PoolSource",
  secondaryFileNames = cms.untracked.vstring(),
  fileNames          = cms.untracked.vstring(
  _input_
  )
)

process.output = cms.OutputModule("PoolOutputModule",
  outputCommands  = cms.untracked.vstring('drop *',
                                          'keep *_l1extraParticles_*_HLT',
                                          'keep *_genParticles_*_*',
                                          'keep *_source_*_*',
                                          'keep *_hlt*_*_*',
                                          'keep *_*Vertices_*_*',
                                          'keep *_*Tracks_*_*',
                                          'keep *_*Muons_*_*',
                                          'keep *_muons_*_*',
                                          'keep *_hiCentrality_*_*',
                                          'keep *_offlineBeamSpot_*_*',
                                          'keep *_*Qual_*_HLT',
                                          'keep *_TriggerResults_*_HLT', 
                                          'keep *_hltTriggerSummaryAOD_*_*',
                                          'keep *_hltTriggerSummaryRAW_*_*',
                                          'keep *_hltL1GtObjectMap_*_HLT',
                                          'keep L1GlobalTriggerReadoutRecord_gtDigis_*_HLT',
  ),
  fileName       = cms.untracked.string(
    _output_
  ),
  dataset        = cms.untracked.PSet(filterName = cms.untracked.string(''),
                                      dataTier   = cms.untracked.string('DIGI-HLT_RECO')
                                     )
  ) 

process.output_step         = cms.EndPath(process.output)
process.load('HLTrigger.Configuration.paMuon_HLT_cff')

process.schedule            = cms.Schedule()
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.output_step])

# customize the L1 emulator to run customiseL1EmulatorFromRaw with HLT to switchToSimGmtGctGtDigis
process.load( 'Configuration.StandardSequences.RawToDigi_Data_cff' )
process.load( 'Configuration.StandardSequences.SimL1Emulator_cff' )
import L1Trigger.Configuration.L1Trigger_custom
process = L1Trigger.Configuration.L1Trigger_custom.customiseL1GtEmulatorFromRaw( process )
process = L1Trigger.Configuration.L1Trigger_custom.customiseResetPrescalesAndMasks( process )

# customize the HLT to use the emulated results
import HLTrigger.Configuration.customizeHLTforL1Emulator
process = HLTrigger.Configuration.customizeHLTforL1Emulator.switchToL1Emulator( process )
process = HLTrigger.Configuration.customizeHLTforL1Emulator.switchToSimGtDigis( process )

if 'GlobalTag' in process.__dict__:
    process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
    process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
    from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag
    process.GlobalTag = customiseGlobalTag(process.GlobalTag,'START53_V11::All','L1GtTriggerMenu_L1Menu_Collisions2012_v3_mc,L1GtTriggerMenuRcd,frontier://FrontierProd/CMS_COND_31X_L1T')

process.MessageLogger = cms.Service("MessageLogger",
  categories         = cms.untracked.vstring('TriggerSummaryProducerAOD','L1GtTrigReport','HLTrigReport'),
  destinations  = cms.untracked.vstring('detailedInfo'
  ),
  detailedInfo   = cms.untracked.PSet(extension  = cms.untracked.string('.txt') 
  )
)


process.GlobalTag.toGet.append( cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            label = cms.untracked.string('AK5PFchsHLT'),
            tag = cms.string('JetCorrectorParametersCollection_AK5PFchs_2012_V8_hlt_mc'),
            connect = cms.untracked.string('frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS')
) )
process.GlobalTag.toGet.append( cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            label = cms.untracked.string('AK5PFHLT'),
            tag = cms.string('JetCorrectorParametersCollection_AK5PF_2012_V8_hlt_mc'),
            connect = cms.untracked.string('frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS')
) )
