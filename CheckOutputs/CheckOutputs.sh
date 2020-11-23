#!/bin/bash

run_list="../prex-runlist/simple_list/all.list"

while IFS= read -r line
do
    rootfile="../japanOutput/prexPrompt_pass1_$line"".000.root"
    postpanroot="/volatile/halla/parity/postpan_respin/prexPrompt_$line""_000_regress_postpan.root"
    plotsdir="../hallaweb_online/prex2/summary_respin/all/run$line""_000/"
    regressionplots="*summary_regression_maindet*"
    output=`rootls $rootfile`

    mulcheck=`echo $output | grep mul -wo`
    if [ "$mulcheck" = "" ]
    then
        echo "$line is missing mul tree in rootfile."
    fi

    errorcheck=`echo $output | grep Error -wo`
    if [ "$errorcheck" = "Error" ]
    then
        echo "$line is missing japanOutput rootfile."
    fi

    potpanrootcheck=`rootls $postpanroot | grep Error -wo`
    if [ "$postpanrootcheck" = "Error" ]
    then
        echo "$line is missing postpan_summary rootfile."
    fi

    plotsdircheck=`ls $plotsdir`
    if [ "$plotsdircheck" = "" ]
    then
        echo "$line is missing plots directory."
    else
        regressionplotscheck=`ls $plotsdir$regressionplots | grep match -wo`
        if [ "$regressionplotscheck" = "match" ]
        then
            echo "$line is missing regression plots."
        fi
    fi
    
done < "$run_list"
