#!/bin/bash

printf "Cleaning icons folder"
printf "\n"
rm -rf ./icons
mkdir ./icons

printf "Generating Icons"
printf "\n"
for x in 16 22 24 32 36 48 64 72 96 128 192 256 512
do
    inkscape -o icons/${x}-apps-io.github.silash35.qpdftools.png -w ${x} io.github.silash35.qpdftools.svg
done

printf "Copying scalable icon"
printf "\n"
cp ./io.github.silash35.qpdftools.svg ./icons/sc-apps-io.github.silash35.qpdftools.svg

printf "Finished"
printf "\n"
