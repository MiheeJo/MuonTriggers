#/bin/bash -
#openHLT set up + updated HLTMuTree (for L2/L3 objects)

# trigger
cvs co -d       CmsHi/HiHLTAlgos UserCode/CmsHi/HiHLTAlgos
# evt
cvs co          UserCode/L1TriggerDPG
cvs co -d       CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010
# trk
cvs co -d       edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer
cvs co -d       edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer
cvs co -d       MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer
rm MitHig/PixelTrackletAnalyzer/src/SimTrackAnalyzer.cc
# jet
cvs co          RecoHI/HiJetAlgos
cvs co          HeavyIonsAnalysis/Configuration
cvs co -d       CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
# photon
cvs co -r V02-02-01  RecoHI/HiEgammaAlgos
cvs co -r V00-00-15  RecoHI/Configuration
cvs co -d CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis

# muon
#cvs co -d HiMuonAlgos/HLTMuTree UserCode/CmsHi/HiMuonAlgos/HLTMuTree
cvs co -d HiMuonAlgos/HLTMuTree UserCode/Miheejo/MuTrig/HLTMuTree
cvs co UserCode/Miheejo/MuTrig/HLTMuTree/test/HiTrigAna_data_fromReco_cfg.py
cp UserCode/Miheejo/MuTrig/HLTMuTree/test/HiTrigAna_data_fromReco_cfg.py CmsHi/HiHLTAlgos/test/

scram build -c
