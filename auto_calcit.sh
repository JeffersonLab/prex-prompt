#! /bin/sh
runnum=$1;

echo -e "\n\n\n\n\n    Starting auto_calcit.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting auto_calcit.sh\n\n\n\n\n";

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

# Unset jlab CE 2.3 env, reset 2.4 env

level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 $QW_ROOTFILES/prex$level\_pass2_$runnum.!(*farm*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass2_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    sensConf="sens.conf"
    if [ $(($run_num)) -ge 3130 ]
    then
      sensConf="sens.3130-.conf"
    fi
    if [ $(($run_num)) -ge 3390 ]
    then
      sensConf="sens.3390-.conf"
    fi
    if [ $(($run_num)) -ge 3803 ]
    then
      sensConf="sens.3803-.conf"
    fi
    if [ $(($run_num)) -ge 5376 ]
    then
      sensConf="sens.5376-.conf"
    fi  
    ./lagrange/calcit \
    	-f $rootfile \
    	-c ./lagrange/conf/$sensConf ; 

    if [ $(($run_num)) -le 3321 ]
    then
	./lagrange/calcit-ramp \
    	    -f $rootfile \
    	    -c ./lagrange/conf/$sensConf ; 
    fi
done

