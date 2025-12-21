import ROOT
f_name = "root://cmseos.fnal.gov//store/user/xinlongl/XHY4bRun3_skim/skimmed_2022EE__SignalMC_XHY4b__MX-3000_MY-600.txt_n-2_i-0.root"

rdf = ROOT.RDataFrame("Events", f_name)
rdf = rdf.Filter("nFatJet >= 3")
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
print("TEST0: ", rdf.Count().GetValue())
