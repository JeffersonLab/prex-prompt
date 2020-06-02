#! /bin/sh
runnum=$1;

echo -e "\n\n\n\n\n    Starting lagrange.sh\n\n\n\n\n";
>&2 echo -e "\n\n\n\n\n    Starting lagrange.sh\n\n\n\n\n";

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

level="Prompt"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./japanOutput/prex$level\_pass1_$runnum.!(*farm*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    trim=${rootfile%.root}
    run_dot_seg=${trim#*pass1_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    echo $(($run_num))
    echo $run_num

    conf="ifarm-respin.conf"
    if [ $(($run_num)) -ge 3404 ]
    then
      conf="ifarm-respin.3404-.conf"
    fi
    if [ $(($run_num)) -ge 4735 ]
    then
      conf="ifarm-respin.4735-.conf"
    fi

    ./lagrange/dance \
    	-f $rootfile \
    	-c ./lagrange/conf/$conf ; 
done

