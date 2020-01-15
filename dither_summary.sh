#!/bin/tcsh
gojapan
cd ~/PREX/prompt/bmodAna
set slug=`rcnd ${1} slug`
root -l -b -q bmodAna.C\($1,\"inputs/input_CREX_ye.txt\"\);
root -l -b -q bmodAna.C\($1,\"inputs/max_input.txt\"\);
root -l -b -q plotAD.C\(\"slopes/dithering_slopes_1133557664422_slug${slug}_run${1}.root\"\);

root -b -q -l "/chafs2/work1/apar/DitherResponse/japan_plot_beammod_BPMS_amplitudecheck_crex.C($1, 0)";
