#!/bin/tcsh
gojapan
cd ~/PREX/prompt
set runnum=`cat ~/datafile/rcRunNumber`
./get_charge.sh 5408-$runnum 0
convert charge_mon.pdf -trim +repage charge_mon.png
/bin/cp --force charge_mon.png hallaweb_online/slug/slug_list/charge_mon.png
/bin/cp --force charge_mon.pdf hallaweb_online/slug/slug_list/charge_mon.pdf
