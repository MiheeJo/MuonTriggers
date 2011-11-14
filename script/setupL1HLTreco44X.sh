#/bin/bash
# Get L1, HLT configuration
cvs co -r $CMSSW_VERSION L1Trigger/Configuration/python
cvs co -r $CMSSW_VERSION HLTrigger/Configuration/python

# Get hlt menu (if necessary, try on interactively. not working with this option)
#hltGetConfiguration /users/miheejo/test1/442HIonV30/V1 --data --unprescale --cff --offline --process TestHlt > $CMSSW_BASE/src/HLTrigger/Configuration/python/HLT_HIon_l3Mu_cff.py 

# Get _cfg.py for running
cvs co -d UserCode/test UserCode/Miheejo/MuTrig/test/
cp UserCode/test/HLT_HIon_l3Mu_cff.py HLTrigger/Configuration/python

scram b
