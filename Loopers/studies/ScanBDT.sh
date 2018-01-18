#!/bin/bash
# Study to scan through the BDT1/2/3 values to support making ROC curves...

#BDT1:
last="0\.85"
#for i in 0\.50 0\.52 0\.54 0\.56 0\.58 0\.60 0\.62 0\.64 0\.66 0\.68 0\.70 0\.72 0\.74 0\.76 0\.78 0\.80 0\.82 0\.84 0\.86 0\.88 0\.90 0\.92 0\.94 0\.96 0\.98
for i in 0\.70 0\.75 0\.80 0\.85 0\.90 0\.95
do
  sed -i.bak "s/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 1, $last)/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 1, $i)/g" SRLooper.C
  grep "getleptonindices_BDT" SRLooper.C
  last=$i
  root -l -b -q doAll.C 2>&1 > logs/bdt1_$i.root
  mv rootfiles/SRLooper.root rootfiles/SRLooper_BDT1_$i.root
done

#sed -i.bak "s/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 1, $last)/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 2, $last)/g" SRLooper.C
#
##BDT2:
#last="0\.85"
#for i in 0\.50 0\.52 0\.54 0\.56 0\.58 0\.60 0\.62 0\.64 0\.66 0\.68 0\.70 0\.72 0\.74 0\.76 0\.78 0\.80 0\.82 0\.84 0\.86 0\.88 0\.90 0\.92 0\.94 0\.96 0\.98
#do
#  sed -i.bak "s/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 2, $last)/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 2, $i)/g" SRLooper.C
#  grep "getleptonindices_BDT" SRLooper.C
#  last=$i
#  root -l -b -q doAll.C 2>&1 > logs/bdt2_$i.root
#  mv rootfiles/SRLooper.root rootfiles/SRLooper_BDT2_$i.root
#done


#sed -i.bak "s/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 2, $last)/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 3, $last)/g" SRLooper.C
#
##BDT3:
#last="0\.85"
#for i in 0\.50 0\.52 0\.54 0\.56 0\.58 0\.60 0\.62 0\.64 0\.66 0\.68 0\.70 0\.72 0\.74 0\.76 0\.78 0\.80 0\.82 0\.84 0\.86 0\.88 0\.90 0\.92 0\.94 0\.96 0\.98
#do
#  sed -i.bak "s/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 3, $last)/getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 3, $i)/g" SRLooper.C
#  grep "getleptonindices_BDT" SRLooper.C
#  last=$i
#  root -l -b -q doAll.C 2>&1 > logs/bdt3_$i.root
#  mv rootfiles/SRLooper.root rootfiles/SRLooper_BDT3_$i.root
#done
