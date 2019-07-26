#! /bin/sh

while IFS= read -r line; do
    runnum=$line;
    root -l "CorrectTree.C ($runnum)";
done < $1
