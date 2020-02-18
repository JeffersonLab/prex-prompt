#! /bin/sh
runnum=$1;

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./japanOutput/prex$level\_pass1_$runnum.!(*jlab.org*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass1_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    postpanConf="combo_reg.conf"
    if [ $(($run_num)) -ge 3390 ]
    then
      postpanConf="combo_reg.3390-3402.conf"
    fi
    if [ $(($run_num)) -ge 3403 ]
    then
      postpanConf="combo_reg.3403-3582.conf"
    fi
    if [ $(($run_num)) -ge 3583 ]
    then
      postpanConf="combo_reg.3583-3802.conf"
    fi
    if [ $(($run_num)) -ge 3803 ]
    then
      postpanConf="combo_reg.3803-4304.conf"
    fi
    if [ $(($run_num)) -ge 4305 ]
    then
      postpanConf="combo_reg.4305-.conf"
    fi
    if [ $(($run_num)) -ge 5376 ]
    then
      postpanConf="burst.conf"
    fi
    if [ $(($run_num)) -ge 6491 ]
    then
      postpanConf="burst.6491-.conf"
    fi
    ./postpan/redana \
    	-f $rootfile \
    	-c ./postpan/conf/$postpanConf ; 
    #	-c ./postpan/conf/combo_reg.conf ;
    # From run 3583- use the 3583-.conf file, manually runranged

    # if [ ! -d ./hallaweb_online/summary/run$run_seg ]; then
    # 	mkdir ./hallaweb_online/summary/run$run_seg;
    # fi

    # cp  ./results/prexPrompt_$run_seg\_postpan_summary.txt \
    # 	./hallaweb_online/summary/run$run_seg/;

done

