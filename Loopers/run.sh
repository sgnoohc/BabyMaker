#!/bin/bash

if [ -z $1 ]; then
    echo "ERROR - Must provide the path to www babies"
    exit
fi

echo "run data..."
./wwwana100 -i $(ls -m $1/* | grep Run20 | tr -d '\n') -o data.root > data.log &
sleep 10
echo "run tzq..."
./wwwana100 -i $(ls -m $1/* | grep tzq   | tr -d '\n') -o tzq.root > tzq.log &
sleep 10
echo "run non-tzq..."
./wwwana100 -i $(ls -m $1/* | grep -v Run20 | grep -v mia | grep -v tzq | grep -v "/wz_" | tr -d '\n') -o nontzq.root > nontzq.log &
sleep 10
echo "run wz..."
./wwwana100 -i $(ls -m $1/* | grep "/wz_" | tr -d '\n') -o wz.root > wz.log &
sleep 10
echo "run www..."
./wwwana100 -i $(ls -m $1/* | grep mia   | tr -d '\n') -o www_2l_mia.root > www.log &
sleep 10
echo "run vh..."
./wwwana100 -i $(ls -m $1/* | grep vh    | tr -d '\n') -o vh_nonbb.root > vh.log &

wait

hadd -f bkg.root tzq.root nontzq.root
