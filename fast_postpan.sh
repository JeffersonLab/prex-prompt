#! /bin/sh
runnum=$1;

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

./postpan/redana \
    -f ./japanOutput/quick_${runnum}.000.root \
    -c ./postpan/conf/quick.conf
