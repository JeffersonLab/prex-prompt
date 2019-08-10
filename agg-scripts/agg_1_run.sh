#! /bin/sh
runnum=$1;
if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi
# Do aggregation after the second pass of japan is done. Assume all slug aggregation is done by the WAC
#Aggregator pass 0
timenow=$(date +"%Y-%m%d-%H%M");
(./aggregator.sh $runnum > /dev/tty ) >& ./LogFiles/Camguin_run$runnum\_$timenow.txt


echo "\n\nDone analyzing run $runnum \n\n"
