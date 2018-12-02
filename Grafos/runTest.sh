#!/bin/bash

times=30
file=${1}

if [ ! -e "$file" ]; then
  echo "File: $file not Found!"
else
  echo "Compilando..."
  mkdir results
  make clean
  make
  echo "Executando Guloso..."

  #Guloso
  ./Solve -g $file >> 'results/'${file//\/}'_GULOSO.txt'

  echo "Executando Guloso Randomizado A=0.1 ..." 
  for i in `seq 0 $times`;
  do
    ./Solve -gr -a=0.1 $file >> 'results/'${file//\/}'_RANDOMIZADO_0.1.txt'
    sleep 1
  done

  echo "Executando Guloso Randomizado A=0.2 ..." 
  for i in `seq 0 $times`;
  do
    ./Solve -gr -a=0.2 $file >> 'results/'${file//\/}'_RANDOMIZADO_0.2.txt'
    sleep 1
  done

  echo "Executando Guloso Randomizado A=0.3 ..." 
  #Guloso Randomico A = 0,3
  for i in `seq 0 $times`;
  do
    ./Solve -gr -a=0.3 $file >> 'results/'${file//\/}'_RANDOMIZADO_0.3.txt'
    sleep 1
  done

  echo "Executando Guloso Randomizado Reativo ..." 
  #Guloso Randomizado Reativo
  for i in `seq 0 $times`;
  do
    ./Solve -grr -br=20 $file >> 'results/'${file//\/}'_REATIVO.txt'
    sleep 1
  done

  echo "Fim!"
fi
