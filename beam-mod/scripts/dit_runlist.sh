#! /bin/sh
rm -f dit_slopes.root;
listname=$1
basename=${listname#$(dirname $listname)/}
tag=${basename%.*}
echo $basename;
echo $tag;

while IFS= read -r line; do
    runnum=$line;
    ./auto-dit.sh $runnum;
done < $1

mv dit_slopes.root ~/PREX/prompt/beam-mod/rootfiles/dit_slopes_$tag.root
