#!/bin/bash

echo "###################################################"
echo "[*] run baseline test"
echo "###################################################"
cd ./bin
echo $PWD

rm params.in
echo "delete params.in"

cd ../
cp params-test/params-baseline ./bin/params.in
echo "copy params-baseline"

cd ./bin
./macsim
cd ../
echo "###################################################"
echo "[*] baseline run finished"
echo "###################################################"

echo "/n"

echo "###################################################"
echo "[*] run offload with hashbit 0 test"
echo "###################################################"
cd ./bin
echo $PWD

rm params.in
echo "delete params.in"

cd ../
cp params-test/params-offload-hb0 ./bin/params.in
echo "copy params-baseline"

cd ./bin
./macsim
cd ../
echo "###################################################"
echo "[*] offload with hashbit 0 run finished"
echo "###################################################"

echo "\n"

echo "###################################################"
echo "[*] run offload with hashbit 1 test"
echo "###################################################"
cd ./bin
echo $PWD

rm params.in
echo "delete params.in"

cd ../
cp params-test/params-offload-hb1 ./bin/params.in
echo "copy params-baseline"

cd ./bin
./macsim
cd ../
echo "###################################################"
echo "[*] offload with hashbit 1 run finished"
echo "###################################################"
