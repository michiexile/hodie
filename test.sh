#!/bin/bash

# Run through all the command line permutations for hodie.

# a host of valid invocations
./hodie
./hodie -h
./hodie --help
./hodie -v
./hodie -v -v
./hodie -v -v -v 
./hodie -v -v -v -v
./hodie -vv
./hodie -vv -v
./hodie --verbose
./hodie --verbose -v
./hodie -n
./hodie --numerals
./hodie -v -n
./hodie -x
./hodie --force-numerals
./hodie -n -x
./hodie -x -n
./hodie -c
./hodie --classic
./hodie --auc
./hodie --date ymd 2000-10-5
./hodie -d ymd 2000-10-5
./hodie -r 25
./hodie -Y 2000 -M 10 --day 5
./hodie -d verbose -Y 2000 -M 10 --day 5
./hodie -d dmy 5-10-2000
./hodie -d mdy 10-6-2000

# failing

./hodie -d
./hodie -d fdjs
./hodie -d ymd
./hodie -d mdy
./hodie -d dmy
./hodie -d ymd fjnds
./hodie -d mdy fbjdks
./hodie -d dmy bfnjksd
