import ROOT
f_name = "nom_compound_1p1_tagged_selected_SKIM_skimmed_2022EE__SignalMC_XHY4b__MX-3000_MY-600_n-10000_i-0.root"

rdf = ROOT.RDataFrame("Events", f_name)
rdf = rdf.Filter("flag1p1")
print(rdf.Count().GetValue())

f_name = "nom_tagged_selected_SKIM_skimmed_2022EE__SignalMC_XHY4b__MX-3000_MY-600_n-10000_i-0.root"
rdf = ROOT.RDataFrame("Events", f_name)
print(rdf.Count().GetValue())

f_name = "nomdebug_compound_1p1_tagged_selected_SKIM_skimmed_2022EE__SignalMC_XHY4b__MX-3000_MY-600_n-10000_i-0.root"
rdf = ROOT.RDataFrame("Events", f_name)
print(rdf.Count().GetValue())
