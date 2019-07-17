#! /bin/sh

while IFS= read -r line; do
    runnum=$line;
    ./auto_postpan.sh $runnum;
done < $1
