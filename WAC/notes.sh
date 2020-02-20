#!/bin/tcsh
echo "\nTo get information about a run use the PVDB interface rcnd"
echo '\e[1;34m'"\t\trcnd ####"'\e[0m'
echo "To view prompt plots"
echo "\tOn the web go to "
echo "\t\thttps://prex.jlab.org/analysis/crex"
echo "\tFrom the command line go to"
echo "\t\t~/PREX/prompt/hallaweb_online/summary/all/run####_000/"
echo "\tFor the highlights execute command"
echo '\e[1;34m'"\t\tpromptPREXplots ####"'\e[0m'
echo "To make WAC comments on a run do"
echo '\e[1;34m'"\t\tslcomment&"'\e[0m'
echo "To look do all of these at once for a given run do"
echo '\e[1;34m'"\t\tcheck_1.sh ####"'\e[0m'
echo "To look at the Panguin plots for a given run do"
echo "\tFor a current run that is ongoing"
echo '\e[1;34m'"\t\tpanguin"'\e[0m'
echo "\tFor a prior run that has been prompted"
echo '\e[1;34m'"\t\tpanguin_offline ####"'\e[0m'
echo "To update the PVDB with your official blessings on runs"
echo "(and please be careful that your changes are picked up) do"
echo '\e[1;34m'"\t\tpvdb_edit&"'\e[0m'

echo "\nIf some runs need to have conditions changed in the PVDB"
echo "please ask Cameron or Sanghwa to do it... anything is possible"
echo "with the power of python"

echo "\n* Populate the \e[1;34mrun_list/slug###.list\e[0m files with the GOOD"
echo "  blessed runs that should be used in all WAC meeting plots"
echo "* Keep notes on calibrations, special runs, problems, and"
echo "  suspicious things, as well as cuts applied per run in the"
echo "  CREX WAC notes wiki pages. This will also help with WAC meetings"
echo "\n* To make WAC plots do"
echo '\e[1;34m'"\t./EZ_WAC.sh run_list/slug###.list"'\e[0m'

echo "\nTo make dithering corrections and associated plots:"
echo "* First verify and prune out bad runs"
echo "\t(we are doing Run-wise analysis for CREX online data analysis)"
echo '\e[1;34m'"\t./dithering/verify_dithering_slopes.sh slugNumber"'\e[0m'
echo "  - Check on the now uploaded plots labelled as alphas and deltas"
echo "  - If any given run has a clear deviation, remove it with:"
echo '\e[1;34m'"\t./dithering/remove_dithering_cycle.sh slugNumber cycleNumber"'\e[0m'
echo "  - Where cycle number is the X axis on the plots you looked at"
echo "  - Remake the above plots to verify the change to the slopes file"
echo "  - Once you are satisfied the slopes are valid do the corrections"
echo "* Do dithering correction"
echo '\e[1;34m'"\t./dithering/dither_correct_aggregate.sh run_list/slug###.list StubArg"'\e[0m'
echo "  - The StubArg should be left blank for the traditional"
echo "    4aX, coils 13746 analysis."
echo "  - For the 1X, coils 13746 analysis (our new default) give StubArg = '_1X'"
echo "    Similarly, give such a StubArg to dither_make_grand_plots.sh,"
echo "    on top of the original"
echo "  - Once you are happy that all data is corrected and aggregated"
echo "    Make the grand plots for by doing (stubArg only needed for _1X):"
echo '\e[1;34m'"\t./dither_make_grand_plots.sh run_list/slug###.list StubArg"'\e[0m'

echo "\n* To add or update cuts"
echo "\tGo to the japan_WAC_only JAPAN copy, copy a prior cuts file,"
echo "\tand edit the cuts as needed."
echo "\t\tAsk an analyzer expert for help if you are unsure."
echo "\t\tFollow Git etiquette for committing and propagating updates."
echo "\t\tFull instructions are posted on the wiki."
echo "* To reprompt a specific run after applying cuts"
echo "\tGo to the ~/PREX/prompt folder and do"
echo '\e[1;34m'"\t\t./prompt.sh ####"'\e[0m'
echo "\tOr launch a dedicated terminal doing the analysis on another"
echo "\t(aonl#) machine with"
echo '\e[1;34m'"\t\t./terminal_prompt_1.sh aonl# ####"'\e[0m'

echo "\nThe most recent run in progress is"
set runNum=`~/scripts/getRunNumber`
echo "Run number:    \e[1;35m$runNum"'\e[0m'
echo "Slug number:   \e[1;35m`rcnd $runNum slug`"'\e[0m'
echo "Run condition: \e[1;35m`rcnd $runNum run_type`"'\e[0m'
echo "Target type:   \e[1;35m`rcnd $runNum target_type`"'\e[0m'
echo "User comment:  \e[1;35m`rcnd $runNum user_comment`"'\e[0m'
echo "\n  \e[1;31m****** This directory for WAC analysis (WACs only, please) ******\n\e[0m"
