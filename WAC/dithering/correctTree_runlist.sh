#! /bin/sh
# Official Copy
#cd /adaqfs/home/apar/PREX/prompt/beam-mod
# Local WAC Copy
cd /adaqfs/home/apar/PREX/prompt/WAC/dithering
if [ "$#" -ge 2 ]; then
  stub=${2}
fi
while IFS= read -r line; do
    runnum=$line;
    root -l -b -q "CorrectTreeFast.C ($runnum,\"${stub}\")";
done < $1
