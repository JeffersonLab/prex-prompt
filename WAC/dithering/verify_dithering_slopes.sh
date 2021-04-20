#!/bin/bash
cd /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/bmodAna/
if [ "$#" -ne 1 ]; then
  echo "Error: just give the slug number directly"
  exit;
fi
slug=$1
if [ ! -d "/u/group/prex/analysis/www/crex/agg-respin1/ErrorFlag_slug/slug_list/slug${slug}/" ]
then
  mkdir /u/group/prex/analysis/www/crex/agg-respin1/ErrorFlag_slug/slug_list/slug${slug}
fi 
root -l -b -q plotAD_13746.C\(\"slopes_run_avg_1X/dithering_slopes_13746_slug${slug}.root\"\);
/bin/cp --force /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/bmodAna/slopes_run_avg_1X/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf /u/group/prex/analysis/www/crex/agg-respin1/ErrorFlag_slug/slug_list/slug${slug}/
# For cyclewise analysis do this:
root -l -b -q plotAD_13746.C\(\"slopes_cyclewise_1X/dithering_slopes_13746_slug${slug}.root\"\);
/bin/cp --force /u/group/halla/parity/software/japan_offline/prompt/prex-prompt/bmodAna/slopes_cyclewise_1X/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf /u/group/prex/analysis/www/crex/agg-respin1/ErrorFlag_slug/slug_list/slug${slug}/dithering_slopes_13746_slug${slug}_cyclewise_alphas-deltas.pdf

echo ""
echo ""
echo "Made: /u/group/prex/analysis/www/crex/agg-respin1/ErrorFlag_slug/slug_list/slug${slug}/dithering_slopes_13746_slug${slug}_alphas-deltas.pdf"
echo "Made: /u/group/prex/analysis/www/crex/agg-respin1/ErrorFlag_slug/slug_list/slug${slug}/dithering_slopes_13746_slug${slug}_cyclewise_alphas-deltas.pdf"
echo ""
cd -
