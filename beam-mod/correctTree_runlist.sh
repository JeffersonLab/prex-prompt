#! /bin/sh

while IFS= read -r line; do
    runnum=$line;
    root -l -b -q "CorrectTree.C ($runnum)";
done < $1
