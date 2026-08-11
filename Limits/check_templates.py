import ROOT
f_name1 = "Templates/Templates_1p1_all.root"
f_name2 = "keep/Templates_1p1_all.root"
f1 = ROOT.TFile.Open(f_name1, "READ")
f2 = ROOT.TFile.Open(f_name2, "READ")

for key in f1.GetListOfKeys():
    hist1 = key.ReadObj()
    hist_name = hist1.GetName()
    if "Allyear" in hist_name or "WZ" in hist_name or "Jet" in hist_name:
        continue
    hist2 = f2.Get(hist_name)
    if isinstance(hist1, ROOT.TH2) and  isinstance(hist2, ROOT.TH2):
        print(hist1.GetEntries(), hist2.GetEntries(), hist_name)
        #if hist1.GetEntries() > 10 and abs(hist1.GetEntries() - hist2.GetEntries()) / hist1.GetEntries() > 0.2:
        #    raise ValueError("bad hist")
    else:
        print(hist_name)
    del hist1
    del hist2
