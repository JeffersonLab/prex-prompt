#!/bin/bash
cd charge_plots

source /apps/root/5.34.36/setroot_CUE.bash
PLOT_FLAG=1

echo "If you want to get plots then edit the script and set PLOT_FLAG=1, and use ROOT 5"
echo ""

if [ $# -eq 2 ]; then
    PLOT_FLAG=$2
fi

script_dir=/adaqfs/home/apar/pvdb/prex/examples

if [ $# -ge 1 ]; then
    # get charge for the given run range
    python $script_dir/acc_charge.py --run=$1
    python $script_dir/acc_charge_time.py --run=$1
else
    # get charge for all production runs
    python $script_dir/acc_charge.py
    python $script_dir/acc_charge_time.py
fi

# Other examples
# 1) Set run range
# python $script_dir/acc_charge.py --run=3000-4000
# 2) Use a run list
# python $script_dir/acc_charge.py --list list.txt
# 3) Select runs marked as Good only
# python $script_dir/acc_charge.py --list list.txt --goodrun=True

    root -b -q ${script_dir}/DrawChargeMon.C
    root -b -q ${script_dir}/DrawChargeMon_time.C
    root -b -q ${script_dir}/DrawChargeMon_TGraph.C
    root -b -q ${script_dir}/DrawChargeMon_projected.C
if [ $PLOT_FLAG -eq 1 ]; then
    evince charge_mon.pdf&
    evince charge_mon_time.pdf&
fi

rm -f out.txt
