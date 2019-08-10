#!/bin/bash

PLOT_FLAG=1

echo "If you want to get plots then edit the script and set PLOT_FLAG=1, and use ROOT 5"

script_dir=/adaqfs/home/apar/pvdb/prex/examples

goods="True"
if [ $# -eq 2 ] 
then
    goods=$2
fi

if [ $# -ge 1 ]; then
    # get charge for the given run range
    python $script_dir/acc_charge.py --run=$1 --goodrun=$goods
else
    # get charge for all production runs
    python $script_dir/acc_charge.py --goodrun=$goods
fi

# Other examples
# 1) Set run range
# python $script_dir/acc_charge.py --run=3000-4000
# 2) Use a run list
# python $script_dir/acc_charge.py --list list.txt
# 3) Select runs marked as Good only
# python $script_dir/acc_charge.py --list list.txt --goodrun=True

if [ $PLOT_FLAG -eq 1 ]; then
    root -b -q ${script_dir}/DrawChargeMon.C
    evince charge_mon.pdf&
fi

rm -f out.txt
