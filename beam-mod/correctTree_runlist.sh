#! /bin/sh
cd /adaqfs/home/apar/PREX/prompt/beam-mod
while IFS= read -r line; do
    runnum=$line;
    root -l -b -q "CorrectTree.C ($runnum)";
#    root -l -b -q "DitAlias.C ($runnum)";
done < $1
