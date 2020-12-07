#! /bin/bash
root -b -q 'MergeBurst.C("slug'$1'")';
root -b -q 'MergePostpan.C("slug'$1'")';
hadd -f ./rootfiles/slug${1}_merged.root ./rootfiles/BurstMerged_slug${1}.root ./rootfiles/PostpanMerged_slug${1}.root

