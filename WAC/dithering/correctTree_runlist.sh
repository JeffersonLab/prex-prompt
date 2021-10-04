#! /bin/sh
# Official Copy
#cd /adaqfs/home/apar/PREX/prompt/beam-mod
# Local WAC Copy
cd ./dithering
stub="seg"
if [ "$#" -ge 2 ]; then
  stub=${2}
fi
stub2="Segment"
if [ "$#" -ge 3 ]; then
  stub2=${3}
  # Part
  # Part_B
  # Segment
  # And Slug (not used)
fi
while IFS= read -r line; do
    runnum=$line;
    #root -l -b -q "CorrectTreeFast.C($runnum,\"${stub}\")";
    root -l -b -q "CorrectTree_evMon_DLR.C($runnum, \"${stub}_avg\", \"/lustre19/expphy/volatile/halla/parity/crex-respin2/japanOutput/\", \"/u/group/halla/parity/software/japan_offline/bmodAna/rootScripts/BeamMod/plotMacros/processed_respin2_data/All_dit_outputs_doing_segment_averaging_of_slopes_mini_friended.root\", \"dit_${stub}_avgd_friendable\", \"/lustre19/expphy/volatile/halla/parity/crex-respin2/LagrangeOutput/rootfiles_err_eigen_${stub}_avg/respin2-rcdb-parts-slowc-segments-${stub}_avg_sens-eigen_reg_lagr.root\", \"mini_eigen_reg_5bpms_${stub}_avg\", \"mini_eigen_lagr_5bpms_${stub}_avg\", \"/lustre19/expphy/volatile/halla/parity/crex-respin2/LagrangeOutput/rootfiles/${stub2}_Avg_EigenCombos_double_sorted.root\", \"mini_eigen_reg_5bpms_sorted_${stub}_avg\")";

    # Sensitivities are in here: /lustre19/expphy/volatile/halla/parity/crex-respin2/bmodOutput/slopes_run_avg_eigenvectors_double_sorted_part_avg_1X/respin2_All_dithering_slopes_run_avg_rcdb_segmented_pruned_usavg_tag_expanded.root
    # dit_part_avgd_tagged_friendable
    # Raw evMon combos are in here: /lustre19/expphy/volatile/halla/parity/crex-respin2/LagrangeOutput/rootfiles/rcdb_segment_eigenvectors_sorted_sorted.root
    # mini_eigen_reg_5bpms_sorted
done < $1
