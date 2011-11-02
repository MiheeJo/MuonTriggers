import FWCore.ParameterSet.Config as cms

##################################################################

# useful options
gtDigisExist=0
isData=1

OUTPUT_HIST='hltrigs.root'
NEVTS=10

##################################################################

process = cms.Process("ANALYSIS")

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      "rfio:/castor/cern.ch/user/m/mironov/cmssw442/l1replay/vandy/hlt_l1mureplay_10_1_WPG.root",
#         '/store/relval/CMSSW_4_2_0_pre8/RelValWE/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V7-v1/0045/167F1B19-E956-E011-BD41-002618943969.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( NEVTS ),
    skipBadFiles = cms.bool(True)
    )

process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.GlobalTag.globaltag = 'GR_R_44_V7::All' #'START42_V9::All'
process.GlobalTag.pfnPrefix=cms.untracked.string('frontier://FrontierProd/')

process.load('Configuration/StandardSequences/SimL1Emulator_cff')

# OpenHLT specificss
# Define the HLT reco paths
#process.load("HLTrigger.HLTanalyzers.HLT_FULL_cff")
# Remove the PrescaleService which, in 31X, it is expected once HLT_XXX_cff is imported

#process.DQM = cms.Service( "DQM",)
#process.DQMStore = cms.Service( "DQMStore",)

# AlCa OpenHLT specific settings

# Define the analyzer modules
process.load("HLTrigger.HLTanalyzers.HLTrigAnalyzer_cfi")
process.hltriganalysis.hltresults = cms.InputTag( 'TriggerResults','','TEST' )
process.hltriganalysis.RunParameters.HistogramFile=OUTPUT_HIST

'''
if (gtDigisExist):
    process.analyzeThis = cms.Path( process.hltriganalysis )
else:
    process.analyzeThis = cms.Path(process.HLTBeginSequence + process.hltriganalysis )
    process.hltriganalysis.l1GtReadoutRecord = cms.InputTag( 'hltGtDigis','',process.name_() )
'''
process.analyzeThis = cms.Path( process.hltriganalysis )

# pdt
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Schedule the whole thing
process.schedule = cms.Schedule( 
    process.analyzeThis )

#########################################################################################
#
#nc=0
if (isData):  # replace all instances of "rawDataCollector" with "source" in InputTags
    from FWCore.ParameterSet import Mixins
    for module in process.__dict__.itervalues():
        if isinstance(module, Mixins._Parameterizable):
            for parameter in module.__dict__.itervalues():
                if isinstance(parameter, cms.InputTag):
                    if parameter.moduleLabel == 'source':
                        parameter.moduleLabel = 'hltRawDataRepacker'
                        #print "Replacing in module: ", module
                        #nc=nc+1
#print "Number of replacements: ", nc
