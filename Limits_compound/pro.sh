MX=$1
MY=$2
MX=3000
MY=600

#./make_json.sh All1p1_Only2p1 
#./make_json.sh All2p1_Only1p1 
mode=All2p1_Only1p1
./make_json.sh $mode
#python XYH.py --tf 1x1 --sig $MX-$MY --r_fail VB1 --r_pass VS2 --make --makeCard --wsp Control_"$mode"_MX-"$MX"_MY-"$MY"
python XYH.py --tf 1x1 --sig $MX-$MY --r_fail VB1 --r_pass VS2 --fit --plot --wsp Control_"$mode"_MX-"$MX"_MY-"$MY"
#python XYH.py --tf 1x1 --sig $MX-$MY --r_fail SB2 --r_pass SR2 --make --makeCard --wsp Loose_"$mode"_MX-"$MX"_MY-"$MY"

#./run_fit.sh  --fitdir Control_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/ -b -v 3 
#./run_fit_diagnostics.sh --fitdir Control_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/ -b -v 3 

status=${PIPESTATUS[0]}
echo $status
control_file=Control_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/higgsCombineSnapshot.MultiDimFit.mH125.root
#control_file_1=Control_"$mode"_MX-"$MX"_MY-"$MY"_workspace_All1p1_Only2p1/SignalMC_XHY4b_1x1_area/higgsCombineSnapshot.MultiDimFit.mH125.root
root -b -q load_parameters.C\(\"$control_file\"\)
#root -b -q load_parameters.C\(\"$control_file_1\"\)

#./run_limits.sh --fitdir Loose_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/ -l -v 2

####################################f test###########################################################
#tfs=(0x0 1x0 0x1 1x1 1x2 2x1)
#./run_GoF.sh  --fitdir Control_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/ -b -v 1

#./run_signal_injection.sh  --fitdir Loose_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/ -b -v 1 -r 0
#./run_signal_injection.sh  --fitdir Loose_"$mode"_MX-"$MX"_MY-"$MY"_workspace/SignalMC_XHY4b_1x1_area/ -b -v 1 -r 3
