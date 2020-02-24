#!/bin/bash
cd ~/PREX/prompt/bmodAna/
if [ "$#" -ne 1 ]; then
  echo "Error: just give the slug number directly"
  exit;
fi
slug=$1
if [ ! -d "/adaqfs/home/apar/PREX/prompt/hallaweb_online/dithering_1X_slug/slug_list/slug${slug}/" ]
then
  mkdir /adaqfs/home/apar/PREX/prompt/hallaweb_online/dithering_1X_slug/slug_list/slug${slug}
fi 
if [ ! -d "/adaqfs/home/apar/PREX/prompt/hallaweb_online/dithering_slug/slug_list/slug${slug}/" ]
then
  mkdir /adaqfs/home/apar/PREX/prompt/hallaweb_online/dithering_slug/slug_list/slug${slug}
fi 
root -l -b -q plotAD_13746.C\(\"slopes_run_avg/dithering_slopes_13746_slug${slug}.root\"\);
/bin/cp --force ~/PREX/prompt/bmodAna/slopes_run_avg/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf ~/PREX/prompt/hallaweb_online/dithering_slug/slug_list/slug${slug}/
root -l -b -q plotAD_13746.C\(\"slopes_run_avg_1X/dithering_slopes_13746_slug${slug}.root\"\);
/bin/cp --force ~/PREX/prompt/bmodAna/slopes_run_avg_1X/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf ~/PREX/prompt/hallaweb_online/dithering_1X_slug/slug_list/slug${slug}/
# For cyclewise analysis do this:
#root -l -b -q plotAD_13746.C\(\"slopes/dithering_slopes_13746_slug${slug}.root\",\"$1\"\);
#/bin/cp --force ~/PREX/prompt/bmodAna/slopes/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf ~/PREX/prompt/hallaweb_online/dithering_1X_slug/slug_list/slug${slug}/dithering_slopes_13746_slug${slug}_cyclewise_alphas-deltas.pdf

echo ""
echo ""
echo "Made: ~/PREX/prompt/hallaweb_online/dithering_1X_slug/slug_list/slug${slug}/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf"
echo "Made: ~/PREX/prompt/hallaweb_online/dithering_slug/slug_list/slug${slug}/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf"
echo ""
cd -
