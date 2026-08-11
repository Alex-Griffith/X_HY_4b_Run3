import ROOT
import matplotlib.pyplot as plt
import numpy as np
ROOT.gStyle.SetOptStat(0000)
ROOT.gStyle.SetOptFit(1111)
#ROOT.gROOT.SetBatch(True)
extra = "All2p1_Only1p1"
toy_file = "Control_MX-3000_MY-600_workspace/SignalMC_XHY4b_1x1_area/higgsCombineSnapshot.GoodnessOfFit.mH125.123456.root" 
obs_file = "Control_MX-3000_MY-600_workspace/SignalMC_XHY4b_1x1_area/higgsCombineSnapshot.GoodnessOfFit.mH125.root" 

rdf = ROOT.RDataFrame("limit", toy_file)

np_rdf = rdf.AsNumpy()
print(np_rdf["limit"])
toys = np_rdf["limit"]
fig = plt.figure(figsize = (10, 6))
ax = fig.add_subplot(1,1,1)
counts, bin_edges = np.histogram(toys, bins=np.linspace(100, 600, 21))

# Compute bin centers
bin_centers = 0.5 * (bin_edges[1:] + bin_edges[:-1])

# Poisson errors
errors = np.sqrt(counts)

ax.errorbar(bin_centers, counts, yerr=errors, fmt='o', capsize=3)

f = ROOT.TFile.Open(obs_file, "READ")
tree = f.limit
for entry in tree:
    obs_limit = entry.limit
    break
print(obs_limit)
ax.annotate(
    '',                                # no text
    xy=(obs_limit, 0.0),                     # arrow end
    xytext=(obs_limit, max(counts) / 2),                 # arrow start
    arrowprops=dict(
        arrowstyle='->', 
        color='blue',
        linewidth=2
    )
)
p = sum([point > obs_limit for point in toys])/ len(toys)
print(p)
ax.text(30, max(counts) * 0.9, f"p = {p:.4f}")
#plt.savefig(f"F_test.png")
fig.savefig("gof_1x1.png")
h  = ROOT.TH1F("h", "h", 21, 100, 600)
for toy in toys:
    h.Fill(toy)

c = ROOT.TCanvas("c", "c" )
h.Fit("gaus")
h.Draw("E")
h.GetXaxis().SetTitle(f"Saturated GoodnessOfFit")
h.SetTitle(f"{extra}")
print(h.GetMaximum())
arrow = ROOT.TArrow(obs_limit, h.GetMaximum() / 2, obs_limit, 0, 0.02, ">")  
arrow.SetLineColor(ROOT.kRed)
arrow.SetLineWidth(2)
arrow.Draw()
text = ROOT.TLatex()
text.SetTextSize(0.04)
text.SetTextColor(ROOT.kBlue)
text.DrawLatex(obs_limit, h.GetMaximum() / 4, f"p = {p:.4f}")
c.Update()
# (x, y, "text")
c.Draw()

c.Print(f"TH_gof_{extra}.png")

