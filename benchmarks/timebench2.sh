#!/bin/sh

./timebench2a -n 100 -r 1000 > /dev/null
./timebench2a -n 1000 -r 100 > /dev/null
./timebench2a -n 10000 > /dev/null
./timebench2a -n 100000 > /dev/null
./timebench2ap
