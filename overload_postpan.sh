#! /bin/sh
runnum=$1;

echo -e "\n\n\n\n\n    Starting overload_postpan.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting overload_postpan.sh\n\n\n\n\n";

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

    overloadConf="overload_reg.conf"
    comboBPMConf="comboBPM_reg.conf" 

    if [ $(($run_num)) -ge 3390 ]
    then
      overloadConf="overload_reg.3390-3802.conf"
      comboBPMConf="comboBPM_reg.3390-3802.conf"
    fi

    if [ $(($run_num)) -ge 3803 ]
    then
      overloadConf="overload_reg.3803-.conf"
      comboBPMConf="comboBPM_reg.3803-.conf"
    fi

    # if [ $(($run_num)) -ge 3803 ]
    # then
    #   overloadConf="overload_reg.3803-4294.conf"
    #   comboBPMConf="comboBPM_reg.3803-4294.conf"
    # fi
    # if [ $(($run_num)) -ge 4295 ]
    # then
    #   overloadConf="overload_reg.4295-.conf"
    #   comboBPMConf="comboBPM_reg.4295-.conf"
    # fi

    ./postpan/redana \
    	-f $rootfile \
    	-c ./postpan/conf/$overloadConf ; 

    if [ $(($run_num)) -ge 3390 ]
    then
    	./postpan/redana \
    	    -f $rootfile \
    	    -c ./postpan/conf/$comboBPMConf;
    fi
done

