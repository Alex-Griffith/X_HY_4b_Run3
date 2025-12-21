import ROOT
import matplotlib.pyplot as plt
import numpy as np
ROOT.gStyle.SetOptStat(0000)
ROOT.gStyle.SetOptFit(1111)
ROOT.gROOT.SetBatch(True)
nom_r = 3
mx = 3000
my = 600
extra = "All2p1_Only1p1"
f_name = f"Loose_MX-{mx}_MY-{my}_workspace/SignalMC_XHY4b_1x1_area/higgsCombiner_{nom_r}.FitDiagnostics.mH125.123456.root" 
print(f_name)
f = ROOT.TFile.Open(f_name, "READ")
limit = f.limit
index = 3
rs = []
deltars = []
sigs = []
for entry in limit:
    if entry.iToy != index:
        r = entry.limit
        deltar = entry.limitErr
    else:
        print(index, r, deltar)
        rs.append(r)
        deltars.append(deltar)
        sigs.append((r - nom_r) / deltar)
        index += 1

fig = plt.figure(figsize = (10, 6))
ax = fig.add_subplot(1, 1, 1)
counts, bin_edges = np.histogram(sigs, bins=np.linspace(-5, 5, 21))

# Compute bin centers
bin_centers = 0.5 * (bin_edges[1:] + bin_edges[:-1])

# Poisson errors
errors = np.sqrt(counts)

ax.errorbar(bin_centers, counts, yerr=errors, fmt='o', capsize=3)

fig.savefig(f"signal_injection_r_{nom_r}_MX_{mx}_MY_{my}_{extra}.png")
h  = ROOT.TH1F(f"r_{nom_r}_MX_{mx}_MY_{my}_{extra}", f"r_{nom_r}_MX_{mx}_MY_{my}_{extra}",21, -5, 5)
for sig in sigs:
    h.Fill(sig)

c = ROOT.TCanvas("c", "c" )
h.Fit("gaus")
h.Draw("E")
h.GetXaxis().SetTitle(f"(r-{nom_r})/rErr")
h.SetTitle(f"r = {nom_r}, MX = {mx}, MY = {my}, channel: {extra}")
c.Print(f"TH_signal_injection_r_{nom_r}_MX_{mx}_MY_{my}_{extra}.png")

