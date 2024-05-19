#!/bin/bash

clear
rm -f core*
rm -f db.dat
rm -f a.out
gcc -g ex17.c
./a.out db.dat c 32 7
./a.out db.dat s 32 7 1 zed zed@sztu.edu.cn 11111111111
#cat db.dat
#echo "\n"
./a.out db.dat s 32 7 2 joe joe@sztu.edu.cn 22222222222
#cat db.dat
#echo "\n"
./a.out db.dat s 32 7 3 frank frank@sztu.edu.cn 33333333333
#cat db.dat
#echo "\n"
./a.out db.dat s 32 7 4 peter peter@sztu.edu.cn 44444444444
#cat db.dat
./a.out db.dat s 32 7 5 oprea oprea@sztu.edu.cn 55555555555
#echo "\n"
./a.out db.dat s 32 7 6 alien alien@sztu.edu.cn 66666666666
./a.out db.dat s 32 7 7 ezi ezi@sztu.edu.cn 77777777777
echo "action list"
./a.out db.dat l 32 7
echo "action get"
./a.out db.dat g 32 7 2 
echo "action find"
./a.out db.dat f 32 7 4 zed
echo "action delet"
./a.out db.dat d 32 7 1 
echo "action list"
./a.out db.dat l 32 7
rm -f a.out
