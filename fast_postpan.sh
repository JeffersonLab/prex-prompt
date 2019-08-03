#! /bin/sh
runnum=$1;

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

postpanConf="combo_reg.conf"
if [ $(($runnum)) -ge 3583 ]
then
  postpanConf="combo_reg.3583-3802.conf"
fi
if [ $(($runnum)) -ge 3803 ]
then
  postpanConf="combo_reg.3803-.conf"
fi

./postpan/redana \
	-f ./japanOutput/quick_${runnum}.000.root \
  -c ./postpan/conf/$postpanConf ; 
