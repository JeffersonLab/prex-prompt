#!/bin/tcsh
gojapan
cd ~/PREX/prompt/bmodAna
set slug=${1}
set stub=""
if ( $#argv >= 2 ) then
  set stub=${2}
endif
root -l -b -q plotAD_13746.C\(\"slopes_run_avg${stub}/dithering_slopes_13746_slug${slug}.root\"\);
/bin/cp --force ~/PREX/prompt/bmodAna/slopes_run_avg${stub}/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf ~/PREX/prompt/hallaweb_online/dithering${stub}_slug/slug_list/slug${slug}/

if ( ${stub} == "_1X" ) then 
  root -l -b -q runBmodAna.C'(1,"inputs/max_1X_input.txt","run_list/slug'$slug'.list")'
  root -l -b -q plotAD_1X.C'("slopes_1X/dithering_slopes_111333555764_slug'$slug'.root")'
  /bin/cp --force slopes_1X/dithering_slopes_111333555764_slug${slug}_alphas-deltas.pdf ~/PREX/prompt/hallaweb_online/dithering${stub}_slug/slug_list/slug${slug}/
endif

