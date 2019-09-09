#! /bin/sh
runnum=$1;
if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi

shopt -s extglob
file_list=$(ls -rt ~/PREX/prompt/hallaweb_online/summary/all/run${runnum}*!(*all)/*_*.pdf);
shopt -u extglob
pdfunite ${file_list} \
	~/PREX/prompt/hallaweb_online/summary/all/run${runnum}_000/run${runnum}_000_all.pdf
