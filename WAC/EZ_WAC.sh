#!/bin/tcsh
if ($# != 1) then
  echo "Error, should pass the runlist (run_list/slug###.list) as an argument"
else
  ./make_grand_plots.sh $1
  ./PQB_make_grand_plots.sh $1
endif
