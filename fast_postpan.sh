#! /bin/sh
runnum=$1;

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

./postpan/redana \
	-f ./japanOutput/quick_${runnum}.000.root \
	-c ./postpan/conf/combo_reg.3583-.conf ; 
#	-c ./postpan/conf/combo_reg.conf ;
# From run 3583- use the 3583-.conf file, manually runranged
