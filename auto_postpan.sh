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

    ./postpan/redana \
    	-f $rootfile \
    	-c ./postpan/conf/combo_reg.conf ;

    # if [ ! -d ./hallaweb_online/summary/run$run_seg ]; then
    # 	mkdir ./hallaweb_online/summary/run$run_seg;
    # fi

    # cp  ./results/prexPrompt_$run_seg\_postpan_summary.txt \
    # 	./hallaweb_online/summary/run$run_seg/;

done

