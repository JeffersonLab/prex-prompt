#! /bin/sh
cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt_merge/prex-prompt/beam-mod
while IFS= read -r line; do
    runnum=$line;
    root -l -b -q "CorrectTree.C ($runnum)";
#    root -l -b -q "DitAlias.C ($runnum)";
done < $1
