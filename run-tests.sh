#!/bin/sh

for directory in "TaskBy4" "TaskBy5" "TaskBy6" "TaskBy7" "TaskBy8"
do
cd $directory
bash run.sh
cd ../
done
