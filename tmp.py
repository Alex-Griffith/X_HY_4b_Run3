import ROOT

f_name = "root://cmseos.fnal.gov//store/user/xinlongl/XHY4bRun3_skim/masked_skimmed_2022EE__Data__JetMET__Run2022F-22Sep2023-v2__NANOAOD.txt_n-2_i-97.root"
f = ROOT.RDataFrame("Events", f_name)
f = f.Filter("nFatJet < 2")
f.Snapshot("Events", "Data_2022EE_Run2022F-22Sep2023-v2_testnFatJet.root")
f = ROOT.RDataFrame("Runs", f_name)
opts = ROOT.RDF.RSnapshotOptions()
opts.fMode = "UPDATE"
f.Snapshot("Runs", "Data_2022EE_Run2022F-22Sep2023-v2_testnFatJet.root", "", opts)
### TESTING ###

#f = ROOT.RDataFrame("Events", f_name)
#f = f.Filter("nFatJet < 2")
#f = f.Define("FatJetPt", "FatJet_pt.at(0) + FatJet_pt.at(1)")

#f.Snapshot("Events", "tmp.root")
