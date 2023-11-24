#!/bin/bash
for n in 4 8 16 1024 2048 4096 8192 16384 32768
do
  for m in true true true true false false false false
  do
       g++  proj03.cpp  -DNUMN=$n -DUSE_MUTEX=$m  -o proj03  -lm  -fopenmp
      ./proj03
  done
done

