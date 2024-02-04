#!/bin/bash

printf "Cleaning icons folder"
printf "\n"
rm -rf ./icons
mkdir ./icons

printf "Generating Icons"
printf "\n"
for x in 16 22 24 32 36 48 64 72 96 128 192 256 512
do
    inkscape -o icons/${x}-apps-br.eng.silas.qpdftools.png -w ${x} br.eng.silas.qpdftools.svg
done

printf "Copying scalable icon"
printf "\n"
cp ./br.eng.silas.qpdftools.svg ./icons/sc-apps-br.eng.silas.qpdftools.svg

printf "Finished"
printf "\n"
