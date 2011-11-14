# Auto generated configuration file
# using: 
# Revision: 1.334 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: l1EmulatorFromRaw -s RAW2DIGI,L1 -n 100 --conditions auto:com10 --datatier DIGI-RECO --eventcontent FEVTDEBUGHLT --data --filein /store/data/Run2011A/MinimumBias/RAW/v1/000/165/514/28C65E11-E584-E011-AED9-0030487CD700.root,/store/data/Run2011A/MinimumBias/RAW/v1/000/165/514/44C0FC26-EE84-E011-B657-003048F1C424.root --customise=L1Trigger/Configuration/customise_l1EmulatorFromRaw --processName=L1EmulRaw --no_exec

# !!!!!!!!!!!!!!!!!!!!! ATTENTION: this run also the L1 !!!!!!!!! check with camelia when you want to run JUST the HLT

import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')
# Other statements

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('HLTrigger.Configuration.HLT_HIon_l3Mu_cff')
process.GlobalTag.globaltag = 'START44_V7::All'

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))

# Input source
process.source = cms.Source("PoolSource",
                            secondaryFileNames = cms.untracked.vstring(),
                            fileNames          = cms.untracked.vstring(
'rfio:/castor/cern.ch/cms/store/results/heavy-ions/HICorePhysics/StoreResults-HICorePhysics_Skim_MinimumBias_RAW-a606dc809a29a92e17749e5652319ad0-SD_MBHI/HICorePhysics/USER/StoreResults-HICorePhysics_Skim_MinimumBias_RAW-a606dc809a29a92e17749e5652319ad0-SD_MBHI/0002/E0627BAA-ECAE-E011-8DF1-000AE488B9BC.root',
)
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
'''
process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )
process.Timing            = cms.Service("Timing")
'''
process.output = cms.OutputModule("PoolOutputModule",
                                  outputCommands  = cms.untracked.vstring(#'drop *_*_*_*',
                                                                          'keep *',
                                                                          #'keep *_TriggerResults_*_RECO',
                                                                          #'keep *_hltTriggerSummaryRAW_*_RECO',
                                                                          #'keep *_hltTriggerSummaryAOD_*_RECO',
                                                                          #'keep *_hltL1GtObjectMap_*_RECO',
                                                                          #'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
                                                                          #'keep *_hlt*_*_*',
                                                                          #'keep l1extraL1MuonParticles_hltL1extraParticles_*_Hlt2',
                                                                          #'keep l1extraL1MuonParticles_*_*_Hlt2',
                                                                          #'keep recoMuon*_*_*_Hlt2',
                                                                          #'keep recoTrack*_*_*_Hlt2',
                                                                          #'keep triggerTriggerFilterObjectWithRefs_*_*_Hlt2',
                                                                          #'keep recoBeamSpot_*_*_Hlt2',
                                                                          #'keep L2MuonTrajectorySeed_*_*_Hlt2',
                                                                          #'keep L3MuonTrajectorySeed_*_*_Hlt2'
                                                                          ),
                                  fileName       = cms.untracked.string("output.root"),
                                  dataset        = cms.untracked.PSet(filterName = cms.untracked.string(''),
                                                                      dataTier   = cms.untracked.string('DIGI-RECO')
                                                                      )
                                  ) 

# Path and EndPath definitions
process.raw2digi_step       = cms.Path(process.RawToDigi)
process.L1simulation_step   = cms.Path(process.SimL1Emulator)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.output_step         = cms.EndPath(process.output)

# Schedule definition
process.schedule            = cms.Schedule(process.raw2digi_step, process.L1simulation_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.reconstruction_step])
process.schedule.extend([process.output_step])

#process.reconstruction_step,
# Automatic addition of the customisation function from L1Trigger.Configuration.customise_l1EmulatorFromRaw
# re-run the whole L1
from L1Trigger.Configuration.customise_l1EmulatorFromRaw import customise 
process = customise(process)

# customize the HLT to use the emulated results
import HLTrigger.Configuration.customizeHLTforL1Emulator
process = HLTrigger.Configuration.customizeHLTforL1Emulator.switchToL1Emulator( process ) 
process = HLTrigger.Configuration.customizeHLTforL1Emulator.switchToSimGmtGctGtDigis( process )


if 'GlobalTag' in process.__dict__:
    process.GlobalTag.toGet.append(
        cms.PSet(
            record  = cms.string( 'L1GtTriggerMenuRcd' ),
            tag     = cms.string( 'L1GtTriggerMenu_L1Menu_CollisionsHeavyIons2011_v0_mc' ),
            label   = cms.untracked.string( '' ),
            connect = cms.untracked.string( 'frontier://FrontierProd/CMS_COND_31X_L1T' )
        )
    )

# End of customisation functions
