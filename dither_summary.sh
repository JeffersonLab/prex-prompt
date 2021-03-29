#!/bin/tcsh
#gojapan
#cd ~/PREX/prompt/bmodAna

setenv QW_ROOTFILES `readlink -f japanOutput`

source PVDB/environment.csh
set slug=`rcnd ${1} slug`

cd bmodAna

### Also do the run average analysis
### CREX RESPIN scripts
root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_cyclewise_1X_ifarm_respin2.txt\"\);
root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_run_avg_1X_ifarm_respin2.txt\"\);
root -l -b -q plotAD_13746.C\(\"slopes_cyclewise_1X/dithering_slopes_13746_slug${slug}_run${1}.root\",\"$1\"\);
root -l -b -q plotAD_13746.C\(\"slopes_run_avg_1X/dithering_slopes_13746_slug${slug}_run${1}.root\",\"$1\"\);

root -b -q -l "japan_plot_beammod_BPMS_amplitudecheck_crex.C($1, 0)";

### Bonus Prompt features - max analysis for all possible alphas and deltas on all coils
##root -l -b -q bmodAna.C\($1,\"inputs/max_input.txt\"\);
##root -l -b -q plotAD.C\(\"slopes/dithering_slopes_1133557664422_slug${slug}_run${1}.root\"\);


###ADAQ CREX prompt

## After slug 138 the input_CREX_ye list uses 1X instead of 4aX
#root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_ye.txt\"\);
#root -l -b -q plotAD_13746.C\(\"slopes/dithering_slopes_13746_slug${slug}.root\",\"$1\"\);
## Also do the run average analysis
#root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_run_avg.txt\"\);
#root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_run_avg_1X.txt\"\);
#root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_run_avg_4aX_15746.txt\"\);
#root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_run_avg_1X_15746.txt\"\);
##root -l -b -q plotAD_15746.C\(\"slopes_run_avg_1X_15746/dithering_slopes_15746_slug${slug}.root\",\"$1\"\);
#root -l -b -q plotAD_15746.C\(\"slopes_run_avg_4aX_15746/dithering_slopes_15746_slug${slug}.root\",\"$1\"\);
## Also, if convenient, do a max COIL input analysis using 1X BPM
##root -l -b -q runBmodAna.C\($1,\"inputs/max_1X_input.txt\"\);
##root -l -b -q bmodAna.C\($1,\"inputs/max_input.txt\"\);
##root -l -b -q plotAD.C\(\"slopes/dithering_slopes_1133557664422_slug${slug}_run${1}.root\"\);
#
#root -b -q -l "/chafs2/work1/apar/DitherResponse/japan_plot_beammod_BPMS_amplitudecheck_crex.C($1, 0)";
