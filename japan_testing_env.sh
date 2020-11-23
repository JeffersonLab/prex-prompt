#!/bin/sh
flag="$1"

#Current flags:
#ifarm, default ifarm links for respins
#rradloff, links for testing small jobs 

if [ -z "$flag" ]
then
    echo "No flag set, exiting.";
    exit 1;
fi

if [ "$flag" = "ifarm" ]
then
    echo "Flag set to $flag, resetting links to default ifarm values.";
fi

if [ "$flag" = "rradloff" ]
then
    echo "Flag set to $flag, setting links to robert's volitile directories.";
fi

rm -f aggOutput
rm -f Aggregator
rm -f aggRootfiles
rm -f Analysis
rm -f BMODextractor
rm -f BMODoutputs
rm -f ditherOutput
rm -f FastPlots
rm -f hallaweb_online
rm -f japanOutput
rm -f LogFiles
rm -f LRBoutput
rm -f Parity
rm -f qwparity
rm -f rcdb
rm -f results
rm -f SummaryPlots
rm -f SummaryText

if [[ $flag == "ifarm" ]]
then
  ln -s /volatile/halla/parity/aggOutput aggOutput
  ln -s /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/aggregator Aggregator
  ln -s /lustre19/expphy/volatile/halla/parity/prex-respin2/aggRootfiles aggRootfiles
  ln -s /u/group/halla/parity/software/japan_offline/operations/Analysis Analysis
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/BMODextractor BMODextractor
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/DitherCorrection BMODoutputs
  ln -s /lustre19/expphy/volatile/halla/parity/prex-respin2/ditherOutput ditherOutput
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/fastOutputs FastPlots
  ln -s /u/group/prex/analysis/www hallaweb_online
  ln -s /lustre19/expphy/volatile/halla/parity/prex-respin2/japanOutput japanOutput
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/LogFiles LogFiles
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/LRBoutput LRBoutput
  ln -s /u/group/halla/parity/software/japan_offline/operations/Parity Parity
  ln -s /u/group/halla/parity/software/japan_offline/operations/build/qwparity qwparity
  ln -s PVDB/rcdb rcdb
  ln -s /lustre19/expphy/volatile/halla/parity/prex-respin2/postpan_respin results
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/SummaryPlots SummaryPlots
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/SummaryText SummaryText
fi

if [[ $flag == "rradloff" ]]
then
#important environment variables for testing:
#setenv QW_DATA "/lustre19/expphy/volatile/hallc/qweak/rradloff/prex"
#setenv PREX_PLOT_DIR "/lustre19/expphy/volatile/hallc/qweak/rradloff/prex"
#setenv QW_PRMINPUT "/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/Parity/prminput"
#setenv QW_ROOTFILES "/lustre19/expphy/volatile/hallc/qweak/rradloff/prex"
#setenv WEB_DIR "/lustre19/expphy/volatile/hallc/qweak/rradloff/prex"

  ln -s /volatile/halla/parity/aggOutput aggOutput
  ln -s /u/group/halla/parity/software/japan_offline/aggregator/rootScripts/aggregator Aggregator
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex aggRootfiles
  ln -s /u/group/halla/parity/software/japan_offline/operations/Analysis Analysis
  ln -s /u/group/halla/parity/software/japan_offline/prompt/PromptLinks/BMODextractor BMODextractor
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex BMODoutputs
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex ditherOutput
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex FastPlots
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex hallaweb_online
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex japanOutput
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex LogFiles
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex LRBoutput
  ln -s /u/group/halla/parity/software/japan_offline/operations/Parity Parity
  ln -s /u/group/halla/parity/software/japan_offline/operations/build/qwparity qwparity
  ln -s PVDB/rcdb rcdb
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex results
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex SummaryPlots
  ln -s /lustre19/expphy/volatile/hallc/qweak/rradloff/prex SummaryText
fi

