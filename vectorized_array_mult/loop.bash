#!/bin/bash
module  load  slurm
module  load  openmpi

#SBATCH -J AutoCorr
#SBATCH -A cs475-575
#SBATCH -p classmpitest
#SBATCH -N 4 # number of nodes
#SBATCH -n 4 # number of tasks
#SBATCH --constraint=ib
#SBATCH -o autocorr.out
#SBATCH -e autocorr.err
#SBATCH --mail-type=END,FAIL
#SBATCH --mail-user=parky8@oregonstate.edu
for n in 1024 4096 16384 65536 262144 1048576 4194304 8388608
do
  g++  proj04.cpp  -DARRAYSIZE=$n  -o proj04  -lm  -fopenmp
  ./proj04
done

