#! /bin/sh
runnum=$1;

echo -e "\n\n\n\n\n    Starting auto_postpan.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting auto_postpan.sh\n\n\n\n\n";

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 $QW_ROOTFILES/prex$level\_pass2_$runnum.!(*farm*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass1_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    echo $(($run_num))
    echo $run_num

    postpanConf="std_reg.conf"
    if [ $(($run_num)) -ge 3404 ]
    then
      postpanConf="std_reg.3404-3802.conf"
    fi
    if [ $(($run_num)) -ge 3803 ]
    then
      postpanConf="std_reg.3803-.conf"
    fi

    ./postpan/redana \
    	-f $rootfile \
    	-c ./postpan/conf/$postpanConf ; 

    # if [ ! -d ./hallaweb_online/prex2/summary_respin/run$run_seg ]; then
    # 	mkdir ./hallaweb_online/prex2/summary_respin/run$run_seg;
    # fi

    # cp  ./results/prexPrompt_$run_seg\_postpan_summary.txt \
    # 	./hallaweb_online/prex2/summary_respin/run$run_seg/;

done

