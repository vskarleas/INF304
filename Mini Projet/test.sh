#!/bin/bash
for i in 0 1 2 3 4 5 6 7 8 9
do
make curiosity-test$i
echo ********************************************
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17
do
./curiosity-test tests/tests_complets/$i.test
done
done