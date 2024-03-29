# Auto generated configuration file
# using: 
# Revision: 1.341 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: l1EmulatorFromRaw -s RAW2DIGI,L1,HLT:HIon -n 100 --conditions auto:hltonline --datatier DIGI-RECO --eventcontent FEVTDEBUGHLT --data --filein /store/hidata/HIRun2010/HIAllPhysics/RAW/v1/000/150/590/02D89852-5DEC-DF11-9E11-001D09F282F5.root --customise=L1Trigger/Configuration/customise_l1EmulatorFromRaw --custom_conditions=L1GtTriggerMenu_L1Menu_Collisions2011_v5,L1GtTriggerMenuRcd,frontier://FrontierProd/CMS_COND_31X_L1T --processName=L1EmulRawHLT --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HiTrigAna')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('HLTrigger.Configuration.HLT_HIon_data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(300)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
    #'/store/hidata/HIRun2010/HICorePhysics/RAW-RECO/v2/000/150/590/4CEB2F45-25ED-DF11-AC92-00E08178C06B.root'
    #'file:/net/hisrv0001/home/davidlw/scratch1/HLTStudies/CMSSW_4_4_0_NewZS/src/RECO_highptInNewNotOld_NewZS_Jet50U.root'
    #'rfio:/castor/cern.ch/user/y/yjlee/HIData2011/recoTest/reco-Run180892-D2E86FE1-FA06-E111-99DC-003048D2C01E.root'
"rfio:/castor/cern.ch/user/h/hckim/cms442patch5/2010HIData_HLT_RECO_r1/2010HIData_HLT_RECO_r1_1.root","rfio:/castor/cern.ch/user/h/hckim/cms442patch5/2010HIData_HLT_RECO_r1/2010HIData_HLT_RECO_r1_10.root",
    )
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Other statements
process.GlobalTag.globaltag = 'GR_R_44_V7::All'

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFhits"),
	nonDefaultGlauberModel = cms.string(""),
	centralitySrc = cms.InputTag("hiCentrality")
	)

# Analyzers
# openhlt
process.load('L1Trigger.Configuration.L1Extra_cff')
process.load('RecoHI.HiCentralityAlgos.CentralityBin_cfi')
process.load('HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi')
process.hltbitanalysis.UseTFileService			= cms.untracked.bool(True)

process.hltana = process.hltbitanalysis.clone(
   l1GtReadoutRecord		= cms.InputTag("gtDigis"),
   l1GctHFBitCounts     = cms.InputTag("gctDigis"),
   l1GctHFRingSums      = cms.InputTag("gctDigis"),
   l1extramu            = cms.string('l1extraParticles'),
   l1extramc            = cms.string('l1extraParticles'),
   # Change process name with your final process name. Default is HLT
   hltresults           = cms.InputTag("TriggerResults","","RECO"),
   HLTProcessName       = cms.string("RECO")
  )

# HiEvt Analyzer
process.load("CmsHi.HiHLTAlgos.hievtanalyzer_cfi")
process.hiEvtAnalyzer.doEvtPlane = False
process.hiEvtAnalyzer.doMC = False

# Jet Analyzers
process.load("PhysicsTools.PatAlgos.patHeavyIonSequences_cff")
process.icPu5corr = process.patJetCorrFactors.clone(
   src = cms.InputTag("iterativeConePu5CaloJets"),
   levels = cms.vstring('L2Relative','L3Absolute'),
   payload = cms.string('AK5Calo'),
   primaryVertices = cms.InputTag("hiSelectedVertex")
  )
process.patJets.jetSource  = cms.InputTag("iterativeConePu5CaloJets")
process.patJets.addBTagInfo         = False
process.patJets.addTagInfos         = False
process.patJets.addDiscriminators   = False
process.patJets.addAssociatedTracks = False
process.patJets.addJetCharge        = False
process.patJets.addJetID            = False
process.patJets.getJetMCFlavour     = False
process.patJets.addGenPartonMatch   = False
process.patJets.addGenJetMatch      = False
process.patJets.embedGenJetMatch    = False
process.patJets.embedGenPartonMatch = False
process.patJets.embedCaloTowers	    = False
process.patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("icPu5corr"))

from CmsHi.JetAnalysis.inclusiveJetAnalyzer_cff import *
process.icPu5JetAnalyzer = inclusiveJetAnalyzer.clone(
	jetTag = 'patJets',
	hltTrgNames = ['HLT_HIJet55_v1','HLT_HIJet65_v1','HLT_HIJet80_v1','HLT_HIJet95_v1'],
	useCentrality = False,
	useVtx = cms.untracked.bool(False),
	isMC = False
	)


#### supercluster analyzer
process.load("CmsHi.PhotonAnalysis.simpleSCTree_cfi")

#### muon anlayzer
process.load("HiMuonAlgos.HLTMuTree.hltMuTree_cfi")
process.hltMuTree.doHLT = cms.untracked.bool(True)

### Track analyzer
process.load("MitHig.PixelTrackletAnalyzer.trackAnalyzer_cff")
process.anaTrack.trackPtMin = 4
process.anaTrack.useQuality = True
process.anaTrack.trackSrc = cms.InputTag("hiSelectedTracks")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("openhlt_data.root")
)

# Path and EndPath definitions
process.recoextra_step = cms.Path(process.L1Extra*process.centralityBin*process.icPu5corr*process.patJets)
process.ana_step = cms.Path(process.hltana*process.hiEvtAnalyzer*process.icPu5JetAnalyzer*process.simpleSCTree*process.hltMuTree*process.anaTrack)

# Schedule definition
process.schedule = cms.Schedule(process.recoextra_step,process.ana_step)
