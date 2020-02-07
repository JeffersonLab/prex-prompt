#!/bin/tcsh
gojapan
cd ~/PREX/prompt
set runnum=`cat ~/datafile/rcRunNumber`
./get_charge.sh 5408-$runnum 0
cd charge_plots
convert charge_mon.pdf -trim +repage charge_mon.png
/bin/cp --force charge_mon.png /group/prex/analysis/www/crex/charge/charge_mon.png
/bin/cp --force charge_mon.pdf /group/prex/analysis/www/crex/charge/charge_mon.pdf
convert charge_mon_time.pdf -trim +repage charge_mon_time.png
/bin/cp --force charge_mon_time.png /group/prex/analysis/www/crex/charge/charge_mon_time.png
/bin/cp --force charge_mon_time.pdf /group/prex/analysis/www/crex/charge/charge_mon_time.pdf
convert charge_mon_projected.pdf -trim +repage charge_mon_projected.png
/bin/cp --force out_shifts.txt /group/prex/analysis/www/crex/charge/out_shifts.txt
/bin/cp --force charge_mon_projected.png /group/prex/analysis/www/crex/charge/charge_mon_projected.png
/bin/cp --force charge_mon_projected.pdf /group/prex/analysis/www/crex/charge/charge_mon_projected.pdf
convert charge_mon_tgraph.pdf -trim +repage charge_mon_tgraph.png
/bin/cp --force charge_mon_tgraph.png /group/prex/analysis/www/crex/charge/charge_mon_tgraph.png
/bin/cp --force charge_mon_tgraph.pdf /group/prex/analysis/www/crex/charge/charge_mon_tgraph.pdf
