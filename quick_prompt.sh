#! /bin/bash
runnum=$1;
if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi

minirun=0
if [ $# -ge 2 ]
then
  echo "Doing minirun $2 (starts at minirun 0, and has 9000 good multiplets per minirun, assume here we are doing 2x as large event ranges, 100000 events long, to compensate for potential beam trips)"
  minirun=$2
fi
startEvts=$((100000*${minirun}))
endEvts=$((100000*${minirun}+100000))
if [[ $2 == "-1" ]]
then
  startEvts=0
  endEvts=2000000
fi

echo "Doing events $startEvts to $endEvts"

./qwparity -r $runnum -c prex.conf \
    --rootfile-stem quick_ \
    -e $startEvts:$endEvts;

./fast_postpan.sh $runnum;

./fast_summary.sh $runnum;

evince FastPlots/run${runnum}_000/run${runnum}_000_all.pdf &
