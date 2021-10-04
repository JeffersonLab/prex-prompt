#! /bin/sh
# Official Copy
#cd /adaqfs/home/apar/PREX/prompt/beam-mod
# Local WAC Copy
#cd ./dithering
stub="seg"
stub2="Segment"
if [ "$#" -ge 2 ]; then
  stub=${2}
fi
do_err="_err"
err_stub=""
if [ "$#" -ge 3 ]; then
  do_err=${3}
fi
nmon=""
nbpms="_5bpms"
if [ "$#" -ge 4 ]; then
  nmon=${4}  # "_allbpms"
  nbpms=${4} # "_allbpms" -> default = "_5bpms"
fi
if [[ $do_err == "no_err" ]]; then
  do_err=""
  err_stub="no_err_"
fi
stub3=$stub
if [[ "$stub" == "seg" ]] ; then
  stub2="Segment"
fi
if [[ "$stub" == "part" ]] ; then
  stub2="Part"
fi
if [[ "$stub" == "part_b" ]] ; then
  stub2="Part_B"
  stub3="part"
fi
#while IFS= read -r line; do
    runnum=$1; # $line
    #root -l -b -q "CorrectTreeFast.C($runnum,\"${stub}\")";
    #void CorrectTree_evMon_DLR(Int_t run_number, TString stub, TString inputFilePath, TString ditSlopeFileName, TString ditTreeName, TString regLagFileName, TString regTreeName, TString lagTreeName, TString comboFileName, TString comboTreeName){
    root -l -b -q "CorrectTree_evMon_DLR.C($runnum, \"${err_stub}${stub}_avg${nmon}\", \"/lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/\", \"/u/group/halla/parity/software/japan_offline/bmodAna/rootScripts/BeamMod/plotMacros/processed_respin2_data/All_dit_outputs_doing_segment_averaging_of_slopes_mini_friended.root\", \"dit_${stub}_avgd${nmon}_friendable\", \"/lustre19/expphy/volatile/halla/parity/crex-respin2/LagrangeOutput/rootfiles${do_err}_eigen_${stub}_avg${nmon}/respin2-rcdb-parts-slowc-segments-${stub}_avg_sens-eigen_reg_lagr.root\", \"mini_eigen_reg${nbpms}_${stub}_avg\", \"mini_eigen_lagr${nbpms}_${stub}_avg\", \"/lustre19/expphy/volatile/halla/parity/crex-respin2/LagrangeOutput/rootfiles/${stub2}_Avg_EigenCombos_double_sorted.root\", \"mini_eigen_reg${nbpms}_sorted_${stub3}_avg\")";

    # Sensitivities are in here: /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes_run_avg_eigenvectors_double_sorted_part_avg_1X/respin2_All_dithering_slopes_run_avg_rcdb_segmented_pruned_usavg_tag_expanded.root
    # dit_part_avgd_tagged_friendable
    # Raw evMon combos are in here: /lustre19/expphy/volatile/halla/parity/crex-respin2/LagrangeOutput/rootfiles/rcdb_segment_eigenvectors_sorted_sorted.root
    # mini_eigen_reg_5bpms_sorted
#done < $1
