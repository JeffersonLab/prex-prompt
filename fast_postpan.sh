#! /bin/sh
runnum=$1;

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

postpanConf="combo_reg.conf"
if [ $(($run_num)) -ge 3390 ]
then
  postpanConf="combo_reg.3390-3582.conf"
fi
if [ $(($runnum)) -ge 3583 ]
then
  postpanConf="combo_reg.3583-3802.conf"
fi
if [ $(($run_num)) -ge 3803 ]
then
  postpanConf="combo_reg.3803-4294.conf"
fi
if [ $(($run_num)) -ge 4295 ]
then
  postpanConf="combo_reg.4295-.conf"
fi

./postpan/redana \
	-f ./japanOutput/quick_${runnum}.000.root \
  -c ./postpan/conf/$postpanConf ; 
